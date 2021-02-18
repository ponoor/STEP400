/*
 Name:		STEP400_firmware.ino

 target:    Arduino Zero
 Created:   2020/12/03 10:24:41
 Author:    kanta
*/
#include <Arduino.h>
#include "wiring_private.h" // pinPeripheral() function
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <OSCMessage.h> // https://github.com/CNMAT/OSC
#include <Ponoor_PowerSTEP01Library.h>  // https://github.com/ponoor/Ponoor_PowerSTEP01_Library
#include <ArduinoJson.h> //https://arduinojson.org/
#include <Adafruit_SleepyDog.h> // https://github.com/adafruit/Adafruit_SleepyDog

#include "globals.h" // Global values and pin mappings
#include "utils.h"  // Utility functions
#include "oscListeners.h"   // OSC receive
#include "loadConfig.h" // Load the config file from SD
#include "diagnosis.h"  // USB serial diagnosis

SPIClass powerStepSPI(&sercom3, POWERSTEP_MISO, POWERSTEP_SCK, POWERSTEP_MOSI, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2);// MISO/SCK/MOSI pins

// Servo mode
constexpr auto position_tolerance = 0; // steps

// brake
boolean bTurnOnWaiting[4] = { 0,0,0,0 };

// for PlatformIO
void sendBootMsg(uint32_t _currentTime);
void resetEthernet();
void sendStatusDebug(String address, int32_t data1, int32_t data2, int32_t data3);
void checkStatus();
void checkLimitSw();
void checkLED(uint32_t _currentTimeMillis);
void checkBrake(uint32_t _currentTimeMillis);
void updateServo(uint32_t currentTimeMicros);

void setup() {

    pinMode(ledPin, OUTPUT);
    pinMode(SD_CS_PIN, OUTPUT);
    pinMode(W5500_RESET_PIN, OUTPUT);
    pinMode(SD_DETECT_PIN, INPUT_PULLUP);
    pinMode(POWERSTEP_RESET_PIN, OUTPUT);
    pinMode(POWERSTEP_CS_PIN, OUTPUT);
    pinMode(POWERSTEP_MOSI, OUTPUT);
    pinMode(POWERSTEP_MISO, INPUT);
    pinMode(POWERSTEP_SCK, OUTPUT);
    digitalWrite(POWERSTEP_RESET_PIN, HIGH);
    digitalWrite(POWERSTEP_RESET_PIN, LOW);
    delay(10);
    digitalWrite(POWERSTEP_RESET_PIN, HIGH);
    digitalWrite(POWERSTEP_CS_PIN, HIGH);
    powerStepSPI.begin();
    pinPeripheral(POWERSTEP_MOSI, PIO_SERCOM_ALT);
    pinPeripheral(POWERSTEP_SCK, PIO_SERCOM_ALT);
    pinPeripheral(POWERSTEP_MISO, PIO_SERCOM_ALT);
    powerStepSPI.setDataMode(SPI_MODE3);
    
    loadConfig();
    
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
    {
        stepper[i].SPIPortConnect(&powerStepSPI);
        resetMotorDriver(i + MOTOR_ID_FIRST);
        digitalWrite(ledPin, HIGH);
        delay(5);
        digitalWrite(ledPin, LOW);
        delay(5);

        if (electromagnetBrakeEnable[i]) {    
            pinMode(brakePin[i], OUTPUT);    
        }
    }

    // Configure W5500
    digitalWrite(W5500_RESET_PIN, HIGH);
    myId = getMyId();
    delay(1);
    resetEthernet();
    isWaitingSendBootMsg = bootedMsgEnable;

    SerialUSB.begin(9600);
    Watchdog.enable(100);
}

void sendBootMsg(uint32_t _currentTime) {
    static uint32_t linkedTime;
    if ( Ethernet.linkStatus() == LinkOFF ) {
        linkedTime = _currentTime;
        return; 
    }
    else {
        if ((uint32_t)(_currentTime - linkedTime) < BOOT_MSG_WAIT_TIME) return;
    }
    OSCMessage newMes("/booted");
    newMes.add(myId);
    Udp.beginPacket(broadcastIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
    isWaitingSendBootMsg = false;
}

void resetEthernet() {
    digitalWrite(W5500_RESET_PIN, LOW);
    digitalWrite(ledPin, HIGH);
    delay(10); // This delay is necessary to refresh the network configration.
    digitalWrite(W5500_RESET_PIN, HIGH);
    digitalWrite(ledPin, LOW);
    delay(1);
    if ( isMyIpAddId ) myIp[3] += myId;
    if ( isMacAddId ) mac[5] += myId;
    if ( isOutPortAddId ) outPort += myId;
    Ethernet.begin(mac, myIp, dns, gateway, subnet);
    Udp.begin(inPort);
}

void checkStatus() {
    uint32_t t;
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
    {
        const auto status = stepper[i].getStatus();
        // HiZ, high for HiZ
        t = (status & STATUS_HIZ) > 0;
        if (HiZ[i] != t)
        {
            HiZ[i] = t;
            if (reportHiZ[i]) sendTwoData("/HiZ", i + MOTOR_ID_FIRST, (int32_t)t);
        }
        // BUSY, low for busy
        t = (status & STATUS_BUSY) == 0;
        if (busy[i] != t)
        {
        	busy[i] = t;
        	if ( reportBUSY[i] ) sendTwoData("/busy", i + MOTOR_ID_FIRST, (int32_t)t);
        }
        // DIR
        t = (status & STATUS_DIR) > 0;
        if (dir[i] != t)
        {
            dir[i] = t;
            if (reportDir[i]) sendTwoData("/dir", i + MOTOR_ID_FIRST, (int32_t)t);
        }
        // SW_F, low for open, high for close
        t = (status & STATUS_SW_F) > 0;
        if (homeSwState[i] != t)
        {
            homeSwState[i] = t;
            if (reportHomeSwStatus[i]) getHomeSw(i + 1);
        }
        // SW_EVN, active high, latched
        t = (status & STATUS_SW_EVN) > 0;
        if (t && reportSwEvn[i]) sendOneDatum("/swEvent", i + MOTOR_ID_FIRST);
        // MOT_STATUS
        t = (status & STATUS_MOT_STATUS) >> 5;
        if (motorStatus[i] != t) {
            motorStatus[i] = t;
            if (reportMotorStatus[i]) sendTwoData("/motorStatus", i + MOTOR_ID_FIRST, motorStatus[i]);
        }
        // CMD_ERROR, active high, latched
        t = (status & STATUS_CMD_ERROR) > 0;
        if (t && reportCommandError[i]) sendOneDatum("/error/command", i + MOTOR_ID_FIRST);
        // UVLO, active low
        t = (status & STATUS_UVLO) == 0;
        if (t != uvloStatus[i])
        {
            uvloStatus[i] = !uvloStatus[i];
            if (reportUVLO[i]) sendTwoData("/uvlo", i + MOTOR_ID_FIRST, uvloStatus[i]);
        }
        // TH_STATUS
        t = (status & STATUS_TH_STATUS) >> 11;
        if (thermalStatus[i] != t) {
            thermalStatus[i] = t;
            if (reportThermalStatus[i]) sendTwoData("/thermalStatus", i + MOTOR_ID_FIRST, thermalStatus[i]);
        }
        // OCD, active low, latched
        t = (status & STATUS_OCD) == 0;
        if (t && reportOCD[i]) sendOneDatum("/overCurrent", i + 1);

        // STALL A&B, active low, latched
        t = (status & (STATUS_STALL_A | STATUS_STALL_B)) >> 14;
        if ((t != 3) && reportStall[i]) sendOneDatum("/stall", i + MOTOR_ID_FIRST);
    }
}
void checkLimitSw() {
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
    {
        bool t = (stepper[i].getParam(ADC_OUT) < 15);
        if ( limitSwState[i] != t )
        {
            limitSwState[i] = !limitSwState[i];
            if (limitSwState[i] && (limitSwMode[i] == SW_HARD_STOP))
            {
                stepper[i].hardStop();
            }
            if (reportLimitSwStatus[i])
            {
                sendThreeInt("/limitSw", i + MOTOR_ID_FIRST, limitSwState[i], dir[i]);
            }
        }
    }
}

void checkLED(uint32_t _currentTimeMillis) {
    if (rxLedEnabled)
    {
        if ((uint32_t)(_currentTimeMillis - RXL_blinkStartTime) >= RXL_TXL_BLINK_DURATION)
        {
            rxLedEnabled = false;
            digitalWrite(PIN_LED_RXL, HIGH); // turn off
        }
    }
    if (txLedEnabled)
    {
        if ((uint32_t)(_currentTimeMillis - TXL_blinkStartTime) >= RXL_TXL_BLINK_DURATION)
        {
            txLedEnabled = false;
            digitalWrite(PIN_LED_TXL, HIGH); // turn off
        }
    }
}

void checkBrake(uint32_t _currentTimeMillis) {
    //
}
void updateServo(uint32_t currentTimeMicros) {
    static uint32_t lastServoUpdateTime = 0;
    static float eZ1[NUM_OF_MOTOR] = { 0,0,0,0 },
        eZ2[NUM_OF_MOTOR] = { 0,0,0,0 },
        integral[NUM_OF_MOTOR] = { 0,0,0,0 };
    float spd = 0.0;
    if ((uint32_t)(currentTimeMicros - lastServoUpdateTime) >= 100) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (isServoMode[i]) {
                int32_t error = targetPosition[i] - stepper[i].getPos();
                integral[i] += ((error + eZ1[i]) / 2.0f);
                if (integral[i] > 1500.0) integral[i] = 1500.0;
                else if (integral[i] < -1500.0) integral[i] = -1500.0;
                if (abs(error) > position_tolerance) {
                    double diff = error - eZ1[i];

                    spd = error * kP[i] + integral[i] * kI[i] + diff * kD[i];
                }
                eZ2[i] = eZ1[i];
                eZ1[i] = error;
                float absSpd = abs(spd);
                //if (absSpd < 1.) {
                //    spd = 0.0;
                //}
                stepper[i].run((spd > 0), absSpd);
            }
        }
        lastServoUpdateTime = currentTimeMicros;
    }
}

void loop() {
    uint32_t 
        currentTimeMillis = millis(),
        currentTimeMicros = micros();
    static uint32_t lastPollTime = 0;

    if ((uint32_t)(currentTimeMillis - lastPollTime) >= STATUS_POLL_PERIOD)
    {
        checkStatus();
        checkLimitSw();
        checkLED(currentTimeMillis);
        uint8_t t = getMyId();
        if (myId != t) {
            myId = t;
            resetEthernet();
        }
        Watchdog.reset();
        lastPollTime = currentTimeMillis;
    }

    if (SerialUSB.available() > 0)
    {
        diagnosisCommand(SerialUSB.read());
    }
    if (isWaitingSendBootMsg) { sendBootMsg(currentTimeMillis); }
    OSCMsgReceive();
    updateServo(currentTimeMicros);
}