#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Ponoor_PowerSTEP01Library.h>
#include <SD.h>
#include <FlashStorage.h>
#include "wiring_private.h" // pinPeripheral() function

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__
constexpr auto FIRMWARE_NAME = "STEP400_r1_hardware_test_r1.0.0";

String results;
FlashStorage(storage, String);

#define ledPin  13u
const uint8_t dipSwPin[8] = { 7u,30u,A5,31u,2u,9u,3u,0u };
const uint8_t brakePin[4] = { A1,8u,5u,1u };
const uint8_t auxPin[3] = { SCL,SDA,38u };
#define SD_CS_PIN 4u
#define SD_DETECT_PIN   A4
#define W5500_RESET_PIN A3

#define NUM_OF_MOTOR   (4)
#define POWERSTEP_MISO  6u  // D6 /SERCOM3/PAD[2] miso
#define POWERSTEP_MOSI  11u // D11/SERCOM3/PAD[0] mosi
#define POWERSTEP_SCK 12u // D12/SERCOM3/PAD[3] sck
SPIClass powerStepSPI(&sercom3, POWERSTEP_MISO, POWERSTEP_SCK, POWERSTEP_MOSI, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2);// MISO/SCK/MOSI pins

#define POWERSTEP_CS_PIN A0
#define POWERSTEP_RESET_PIN A2
powerSTEP stepper[] = {
    powerSTEP(3, POWERSTEP_CS_PIN, POWERSTEP_RESET_PIN),
    powerSTEP(2, POWERSTEP_CS_PIN, POWERSTEP_RESET_PIN),
    powerSTEP(1, POWERSTEP_CS_PIN, POWERSTEP_RESET_PIN),
    powerSTEP(0, POWERSTEP_CS_PIN, POWERSTEP_RESET_PIN)
};

// Network
byte mac[] = { 0x60, 0x95, 0xCE, 0x10, 0x02, 0x90 };
IPAddress 
    myIp(10, 0, 0, 100),
    destIp(10, 0, 0, 10),
    dns(10, 0, 0, 1),
    gateway(10, 0, 0, 1),
    subnet(255, 255, 255, 0);
EthernetUDP Udp;

// Serial Monitor out utilities
#define p(fmt, ...)  p_(F(fmt), ##__VA_ARGS__)
void p_(const __FlashStringHelper* fmt, ...)
{
    char buf[128]; // resulting string limited to 128 chars
    va_list args;
    va_start(args, fmt);
#ifdef __AVR__
    vsnprintf_P(buf, sizeof(buf), (const char*)fmt, args); // progmem for AVR
#else
    vsnprintf(buf, sizeof(buf), (const char*)fmt, args); // for the rest of the world
#endif
    va_end(args);
    SerialUSB.print(buf);
    results += String(buf);
}

void showHeader(String header) {
  p("-------------- %s --------------\n", header.c_str());
  // SerialUSB.println();
  // SerialUSB.print(line);
  // SerialUSB.print(header);
  // SerialUSB.println(line);
}

void showBoolResult(bool t) {
  if (t) { p("Ok\n"); }
  else { p("Failed\n");}
}
void showTestResult(bool t) {
  String res = (t) ? "Passed" : "Failed";
  p("\nTest result: %s\n\n", res.c_str());
}


// Title
void showTestTitle() {
  showHeader("STEP400 hardware test");
  p("Firmware revision: %s\n",FIRMWARE_NAME);
  p("Compiled at %s %s\n", COMPILE_DATE, COMPILE_TIME);
}
// SD card
bool sdTest() {
  bool t, result = false;
  showHeader("SD card");
  pinMode(SD_CS_PIN, OUTPUT);
  pinMode(SD_DETECT_PIN, INPUT_PULLUP);
  p("SD card initialize: ");
  t = SD.begin(SD_CHIP_SELECT_PIN);
  showBoolResult(t);
  if (t)
  {
    SD.end();
    result = !digitalRead(SD_DETECT_PIN);
    p("SD_DETECT_PIN: %d ", !result);
    showBoolResult(result);
    
  } else {
    if (digitalRead(SD_DETECT_PIN) == LOW) {
      p("The SD card and/or SD slot connection is broken.");
    } else {
      p("SD card is not inserted.");
    }
  }
  pinMode(SD_CS_PIN, INPUT);
  showTestResult(result);
  return result;
}

// Electromagnetic Brake Control Pins
bool brakePinTest() {
  showHeader("Electromagnetic Brake Pins");
  p("brakePin connection state: ");
  bool t = true;
  for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
  {
    for (uint8_t j = 0; j < NUM_OF_MOTOR; j++) {
      pinMode(brakePin[j], OUTPUT);
      digitalWrite(brakePin[j], LOW);
    }
    pinMode(brakePin[i], INPUT_PULLUP);
    t &= digitalRead(brakePin[i]); // the pin has to be HIGH
    if (!t) {
      p("\nbrakePin#%d connection problem found.\n", i+1);
    }
    pinMode(brakePin[i],INPUT);
  }
  showBoolResult(t);
  showTestResult(t);
  return t;
}

// Auxiliary Pins
bool auxPinTest() {
  showHeader("Auxiliary Pins");
  p("Auxiliary Pins connection state: ");
  bool t = true;
  for (uint8_t i = 0; i < 3; i++)
  {
    for (uint8_t j = 0; j < 3; j++) {
      pinMode(auxPin[j], OUTPUT);
      digitalWrite(auxPin[j], LOW);
    }
    pinMode(auxPin[i], INPUT_PULLUP);
    t &= digitalRead(auxPin[i]); // the pin has to be HIGH
    if (!t) {
      p("\nauxPin#%d connection problem found.\n", i+1);
    }
    pinMode(auxPin[i],INPUT);
  }
  showBoolResult(t);
  showTestResult(t);
  return t;
}

// Ethernet
void resetW5500() {
  pinMode(W5500_RESET_PIN, OUTPUT);
  digitalWrite(W5500_RESET_PIN, HIGH);
  delay(1);
  digitalWrite(W5500_RESET_PIN, LOW);
  delay(10);
  digitalWrite(W5500_RESET_PIN, HIGH);
  delay(10);
  //Ethernet.init(10);
  Ethernet.begin(mac, myIp);
  Udp.begin(50000);
}

bool ethernetTest() {
  uint8_t t;
  String s;
  bool result = false;
  showHeader("Ethernet");
  digitalWrite(ledPin, HIGH);
  resetW5500();
  delay(100);
  digitalWrite(ledPin, LOW);
  t = Ethernet.hardwareStatus();
  p("Ethernet hardware status: %d, ",t);
  switch (t)
  {
  case EthernetNoHardware:
    p("-EthernetNoHardware\nW5500 connection failed.\n");
    break;
  case EthernetW5100:
    p("-EthernetW5100\nWrong hardware detected.\n");
    break;
  case EthernetW5200:
    p("-EthernetW5200\nWrong hardware detected.\n");
    break;
  case EthernetW5500:
    p("-EthernetW5500 Ok\n");
    result = true;
    break;
  default:
    break;
  }
  bool linked = true;
  if (result) {
    uint8_t counter = 0;
    t = Ethernet.linkStatus();
    p("Ethernet link status: %d ", t);
    while ( Ethernet.linkStatus() != LinkON ) {
      delay(500);
      counter++;
      p(".");
      if (counter>=8) {
        p(" timeout\n");
        linked = false;
        break;
      }
    }
    if (linked) p("Ok\n");
  }
  result &= linked;
  pinMode(W5500_RESET_PIN, INPUT);
  //SPI.end();
  showTestResult(result);
  return result;
}

// PowerSTEP01
bool powerSTEP01Test() {
  bool result = true;
  showHeader("PowerSTEP01");
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

  for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
  {
      stepper[i].SPIPortConnect(&powerStepSPI);
      // resetMotorDriver(i + MOTOR_ID_FIRST);
      digitalWrite(ledPin, HIGH);
      delay(5);
      digitalWrite(ledPin, LOW);
      delay(5);
  }

  uint8_t i = 0;
  uint16_t status[NUM_OF_MOTOR];
  uint32_t temp = 0;

  p("PowerSTEP01 SPI connection: ");
  for (i = 0; i < NUM_OF_MOTOR; i++) {
    stepper[i].resetDev();
    stepper[i].setOscMode(EXT_24MHZ_OSCOUT_INVERT); // 16MHz for the production version
    stepper[i].setVoltageComp(VS_COMP_DISABLE);
    stepper[i].setParam(ALARM_EN, 0xEF); // Enable alarms except ADC UVLO
    status[i] = stepper[i].getStatus(); // Clear Startup Flags
    status[i] = stepper[i].getStatus();
    temp += status[i];
  }
  showBoolResult(temp!=0);

  if (temp != 0) {
    for ( i = 0; i < NUM_OF_MOTOR; i++)
    {
      temp = 0;
      p("PowerSTEO01 ID#%d\n STATUS: 0x%02X ",i+1, status[i]);
      // OCD, active low, latched
      if ((status[i] & STATUS_OCD) == 0) {
        temp = 0x01;
      }
      // UVLO, active low
      if ((status[i] & STATUS_UVLO) == 0) {
        temp |= 0x02;
      }
      switch (temp)
      {
      case 0:
        p(" Ok\n");
        break;
      case 1:
        // OCD detected.
        p("OCD(Over Current) detected.\n");
        result = false;
        break;
      case 2:
        // ULVO detected.
        p("UVLO(Under Voltage LockOut) detected.\n");
        result = false;
        break;
      case 3:
        // OCD+ULVO detected.
        p("OCD+UVLO detected.\n");
        result = false;
        break;
      default:
        break;
      }

      // SW_F, low for open, high for close
      bool swF = (status[i] & STATUS_SW_F);
      p(" SW_F: %d ", swF);
      showBoolResult(!swF);
      if (swF == 1) {
        p("HOME senser input closed. Check HOME connection.\n");
        result = false;
      }
      // ADC
      temp = stepper[i].getParam(ADC_OUT);
      p(" ADC_OUT: %d ", temp);
      if (temp < 25) {
        p("Unexpected value. Chech ADC_OUT pin connection.\n");
        result = false;
      }
      else {
        p("Ok\n");
      }
    }
  } else {
    result = false;
  }
  powerStepSPI.end();
  showTestResult(result);
  return result;
}

// DIP switch
bool dipSwTest() {
  showHeader("DIP Switch");
  bool result = false, bChanged = false;
  bool digitState[8], bTested[8] = {0,0,0,0,0,0,0,0};

  for (auto i = 0; i < 8; ++i)
  {
    pinMode(dipSwPin[i], INPUT_PULLUP);
    digitState[i] = digitalRead(dipSwPin[i]);
  }
  p("Move all digits of the switch\n(Type `b` to cancel the test.)\n");
  while ( !result )
  {
    result = true;
    for (auto i=0; i<8; i++) {
      if (digitState[i] != digitalRead(dipSwPin[i])) {
        digitState[i] = !digitState[i];
        bTested[i] = true;
        bChanged = true;

      }
      result &= bTested[i];
    }
    if ( bChanged ) {
      //SerialUSB.print("\t");
      for (auto i=0; i<8; i++) {
        if (bTested[i]) { p("Ok ");}
        else { p("-- ");}
      }
      p("\n");
      bChanged = false;
    }
    if (SerialUSB.available()>0) {
      if (SerialUSB.read() == 'b') {
        result = false;
        p("Cancelled.\n");
        break;
      }
    }
    delay(30);
  }

  showTestResult(result);
  return result;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  SerialUSB.begin(9600);
  
}

void hardwareTest() {
  bool testResult[6];
  bool t = true;
  results = "";
  showTestTitle();
  t &= (testResult[0] = sdTest());
  t &= (testResult[1] = brakePinTest());
  t &= (testResult[2] = auxPinTest());
  t &= (testResult[3] = ethernetTest());
  t &= (testResult[4] = powerSTEP01Test());
  t &= (testResult[5] = dipSwTest());
  showHeader("Result of Hardware Test");
  p("SD Card: ");
  showBoolResult(testResult[0]);
  p("Brake Pins: ");
  showBoolResult(testResult[1]);
  p("Auxiliary Pins: ");
  showBoolResult(testResult[2]);
  p("Ethernet: ");
  showBoolResult(testResult[3]);
  p("PowerSTEP01: ");
  showBoolResult(testResult[4]);
  p("DIP switch: ");
  showBoolResult(testResult[5]);
  showTestResult(t);
  storage.write(results);
}
void loadResults() {
  SerialUSB.println(F("================ Stored results ================"));
  results = storage.read();
  SerialUSB.println(results);
}
void loop() {
  if (SerialUSB.available()>0) {
    switch( SerialUSB.read() ) {
      case 't':
        hardwareTest();
        break;
      case 's':
        sdTest();
        break;
      case 'l':
        loadResults();
        break;
    }
  }
}
