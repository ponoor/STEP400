// 
// 
// 

#include "utils.h"


uint8_t getMyId() {
    uint8_t _id = 0;
    for (auto i = 0; i < 8; ++i)
    {
        pinMode(dipSwPin[i], INPUT_PULLUP);
        _id |= (!digitalRead(dipSwPin[i])) << i;
    }
    return _id;
}


void turnOnRXL() {
    digitalWrite(PIN_LED_RXL, LOW); // turn on
    RXL_blinkStartTime = millis();
    rxLedEnabled = true;
}

void turnOnTXL() {
    digitalWrite(PIN_LED_TXL, LOW); // turn on
    TXL_blinkStartTime = millis();
    txLedEnabled = true;
}

void resetMotorDriver(uint8_t deviceID) {
    if (MOTOR_ID_FIRST <= deviceID && deviceID <= MOTOR_ID_LAST) {
        deviceID -= MOTOR_ID_FIRST;
        stepper[deviceID].resetDev();
        stepper[deviceID].configStepMode(microStepMode[deviceID]);
        stepper[deviceID].setMaxSpeed(maxSpeed[deviceID]);
        stepper[deviceID].setLoSpdOpt(true);
        stepper[deviceID].setMinSpeed(lowSpeedOptimize[deviceID]); // Low speed optimazation threshold
        stepper[deviceID].setFullSpeed(fullStepSpeed[deviceID]);
        stepper[deviceID].setParam(INT_SPD, intersectSpeed[deviceID]);
        stepper[deviceID].setParam(ST_SLP, startSlope[deviceID]);
        stepper[deviceID].setParam(FN_SLP_ACC, accFinalSlope[deviceID]);
        stepper[deviceID].setParam(FN_SLP_DEC, decFinalSlope[deviceID]);
        stepper[deviceID].setAcc(acc[deviceID]);
        stepper[deviceID].setDec(dec[deviceID]);
        stepper[deviceID].setSlewRate(slewRate[deviceID]);
        stepper[deviceID].setPWMFreq(PWM_DIV_1, PWM_MUL_0_75);
        uint16_t swMode = homeSwMode[deviceID] ? SW_USER : SW_HARD_STOP;
        stepper[deviceID].setSwitchMode(swMode);//
        stepper[deviceID].setVoltageComp(VS_COMP_DISABLE);
        stepper[deviceID].setOCThreshold(overCurrentThreshold[deviceID]); // 5A for 0.1ohm shunt resistor
        stepper[deviceID].setOCShutdown(OC_SD_ENABLE);
        stepper[deviceID].setOscMode(EXT_24MHZ_OSCOUT_INVERT);
        stepper[deviceID].setRunKVAL(kvalRun[deviceID]);
        stepper[deviceID].setAccKVAL(kvalAcc[deviceID]);
        stepper[deviceID].setDecKVAL(kvalDec[deviceID]);
        stepper[deviceID].setHoldKVAL(kvalHold[deviceID]);
        stepper[deviceID].setParam(STALL_TH, stallThreshold[deviceID]);
        stepper[deviceID].setParam(ALARM_EN, 0xEF); // Enable alarms except ADC UVLO
        //kvalHold[deviceID] = tvalHold[deviceID] = stepper[deviceID].getHoldKVAL();
        //kvalRun[deviceID] = tvalRun[deviceID] = stepper[deviceID].getRunKVAL();
        //kvalAcc[deviceID] = tvalAcc[deviceID] = stepper[deviceID].getAccKVAL();
        //kvalDec[deviceID] = tvalDec[deviceID] = stepper[deviceID].getDecKVAL();

        delay(1);
        stepper[deviceID].getStatus(); // clears error flags
    }
}

void sendOneInt(String address, int32_t data) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add((int32_t)data);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void sendTwoInt(String address, int32_t data1, int32_t data2) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data1).add(data2);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void sendThreeInt(String address, int32_t data1, int32_t data2, int32_t data3) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data1).add(data2).add(data3);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void sendIdFloat(String address, int32_t id, float data) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(id).add(data);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void sendOneString(String address, const char* data) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

template <class T>
T sendTwoData(String address, T data1, T data2) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes(address.c_str());
    newMes.add(data1).add(data2);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}