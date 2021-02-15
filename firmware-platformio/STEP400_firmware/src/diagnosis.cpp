// 
// 
// 

#include "diagnosis.h"
#include <stdarg.h>
#include "utils.h"

// =============================================================================
// Diagnosis via USB serial
// =============================================================================


void diagnosisCommand(uint8_t inByte) {
	switch (inByte)
	{
	case 'm':
		printMenu();
		break;
	case 'p':
		printParameters();
		break;
	case 's':
		printCurrentState();
		break;
	default:
		break;
	}
}

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
}

#define p(fmt, ...)	 p_(F(fmt), ##__VA_ARGS__)

void printMenu() {
	p("s: show status\n");
	p("p: show parameters\n");
}

void printCurrentState() {
	String s;
	bool bt;
	boldHeader("Current Status");
	p("Firmware name : %s\n", FIRMWARE_NAME);
	p("Compile date : %s, %s\n", COMPILE_DATE, COMPILE_TIME);

	printHeader("DIP Switch");
	p("BIN : ");
	uint8_t t = getMyId();
	for (uint8_t i = 0; i < 8; i++) {
		SerialUSB.print(((t >> (7 - i)) & 1) == 1 ? "1" : "0");
		if (i == 3) SerialUSB.print(" ");
	}
	p("\nDEC : %d\n", t);
	printHeader("Ethernet");
	t = Ethernet.hardwareStatus();
	p("Ethernet hardware status: %d ", t);
	switch (t)
	{
	case EthernetNoHardware:
		s = F("-EthernetNoHardware");
		break;
	case EthernetW5100:
		s = F("-EthernetW5100");
		break;
	case EthernetW5200:
		s = F("-EthernetW5200");
		break;
	case EthernetW5500:
		s = F("-EthernetW5500");
		break;
	default:
		break;
	}
	SerialUSB.println(s);
	t = Ethernet.linkStatus();
	p("Ethernet link status: %d ", t);
	switch (t)
	{
	case Unknown:
		s = F("-Unknown");
		break;
	case LinkON:
		s = F("-LinkON");
		break;
	case LinkOFF:
		s = F("-LinkOff");
		break;
	default:
		break;
	}
	SerialUSB.println(s);
	printHeader("microSD");
	showBoolResult(F("SD library initialize succeeded"), sdInitializeSucceeded);
	showBoolResult(F("SD config file open succeeded"), configFileOpenSucceeded);
	showBoolResult(F("SD config JSON parse succeeded"), configFileParseSucceeded);

	printHeader("PowerSTEP01");
	uint16_t status[NUM_OF_MOTOR];
	uint32_t temp = 0;
	for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
		status[i] = stepper[i].getStatus();
		temp += status[i];
	}
	showBoolResult(F("PowerSTEP01 SPI connection established"), temp != 0);
	if (temp != 0) {
		for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
		{
			temp = 0;
			p("PowerSTEO01 ID#%d\n\tSTATUS: 0x%02X\n", i + 1, status[i]);
			bt = (status[i] & STATUS_HIZ) > 0; // HiZ, high for HiZ
			showBoolResult(F("\tHigh impedance state"), bt);
			showBoolResult(F("\tBUSY"), !(status[i] & STATUS_BUSY));
			bt = (status[i] & STATUS_DIR) > 0;
			s = (bt ? "Foward" : "Reverse");
			p("\tMotor direction : %s\n", s.c_str());
			t = (status[i] & STATUS_MOT_STATUS) >> 5;
			switch (t)
			{
			case 0:
				s = "Stopped";
				break;
			case 1:
				s = "Acceleration";
				break;
			case 2:
				s = "Deceleration";
				break;
			case 3:
				s = "Constant speed";
				break;
			default:
				break;
			}
			p("\tMotor status : %s\n", s.c_str());

			t = (status[i] & STATUS_UVLO) == 0;
			showBoolResult("\tUVLO (Undervoltage lock out)", t);

			t = (status[i] & STATUS_TH_STATUS) >> 11;
			switch (t)
			{
			case 0:
				s = "Normal";
				break;
			case 1:
				s = "Warning";
				break;
			case 2:
				s = "Bridge shutdown";
				break;
			case 3:
				s = "Device shutsown";
				break;
			default:
				break;
			}
			p("\tThermal status : %s\n", s.c_str());

			t = (status[i] & STATUS_OCD) == 0;
			showBoolResult("\tOCD (Overcurent detection)", t);

			t = (status[i] & (STATUS_STALL_A | STATUS_STALL_B)) >> 14;
			bt = (t != 3);
			showBoolResult("\tStalled", bt);

			// SW_F, low for open, high for close
			bool swF = (status[i] & STATUS_SW_F);
			p("\tSW_F: %d ", swF);
			if (swF == 1) {
				p("-HOME senser input closed.\n");
			}
			else {
				p("-HOME senser input open.\n");
			}
			// ADC
			temp = stepper[i].getParam(ADC_OUT);
			p("\tADC_OUT: %d ", temp);
			if (temp >= 28) {
				p("-LIMIT senser input open.\n");
			}
			else if (temp < 5) {
				p("-LIMIT senser input closed.\n");
			}
			else {
				p("Unexpected value.\n");
			}
		}
	}
}


#pragma region print_config
void printParameters() {
	boldHeader("Parameters");
	printHeader("Config");
	//showBoolResult(F("SD library initialize succeeded"), sdInitializeSucceeded);
	//showBoolResult(F("SD config file open succeeded"), configFileOpenSucceeded);
	//showBoolResult(F("SD config file parse succeeded"), configFileParseSucceeded);
	p("configName : %s\n", configName.c_str());

	printHeader("Network");
	showIpAddress(F("My Ip"), myIp);
	showIpAddress(F("Dest Ip"), destIp);
	showIpAddress(F("DNS"), dns);
	showIpAddress(F("Gateway"), gateway);
	showIpAddress(F("Subnet mask"), subnet);
	showBoolResult(F("isMyIpAddId"), isMyIpAddId);
	showBoolResult(F("isMacAddId"), isMacAddId);
	showBoolResult(F("bootedMsgEnable"), bootedMsgEnable);
	showBoolResult(F("isDestIpSet"), isDestIpSet);

	printHeader("Report & Alarm");
	show4Bool("reportBUSY", reportBUSY); 
	show4Bool(F("reportBUSY"), reportBUSY);
	show4Bool(F("reportFLAG"), reportFLAG);
	show4Bool(F("reportHiZ"), reportHiZ);
	show4Bool(F("reportHomeSwStatus"), reportHomeSwStatus);
	show4Bool(F("reportDir"), reportDir);
	show4Bool(F("reportMotorStatus"), reportMotorStatus);
	show4Bool(F("reportSwEvn"), reportSwEvn);
	show4Bool(F("reportCommandError"), reportCommandError);
	show4Bool(F("reportUVLO"), reportUVLO);
	show4Bool(F("reportThermalStatus"), reportThermalStatus);
	show4Bool(F("reportOCD"), reportOCD);
	show4Bool(F("reportStall"), reportStall);
	show4Bool(F("reportLimitSwStatus"), reportLimitSwStatus);
	show4Bool(F("reportOCD"), reportOCD);
	print4data("OCThreshold", overCurrentThreshold);

	printHeader("driverSettings");
	print4data("microStepMode", microStepMode);
	show4Bool(F("homeSwMode"), homeSwMode);
	show4Bool(F("limitSwMode"), limitSwMode);
	show4Bool(F("isCurrentMode"), isCurrentMode);
	print4data("slewRate", slewRateNum);
	show4Bool(F("electromagnetBrakeEnable"), electromagnetBrakeEnable);

	printHeader("speedProfile");
	print4data("acc", acc);
	print4data("dec", dec);
	print4data("maxSpeed", maxSpeed);
	print4data("fullStepSpeed", fullStepSpeed);

	printHeader("Voltage mode");
	print4data("kvalHold", kvalHold);
	print4data("kvalRun", kvalRun);
	print4data("kvalAcc", kvalAcc);
	print4data("kvalDec", kvalDec);
	print4data("intersectSpeed", intersectSpeed);
	print4data("startSlope", startSlope);
	print4data("accFinalSlope", accFinalSlope);
	print4data("decFinalSlope", decFinalSlope);
	print4data("stallThreshold", stallThreshold);
	print4data("lowSpeedOptimize", lowSpeedOptimize);

	printHeader("Current mode");
	print4data("tvalHold", tvalHold);
	print4data("tvalRun", tvalRun);
	print4data("tvalAcc", tvalAcc);
	print4data("tvalDec", tvalDec);
	print4data("fastDecaySetting", fastDecaySetting);
	print4data("minOnTime", minOnTime);
	print4data("minOffTime", minOffTime);

	printHeader("Servo mode");
	print4data("kP", kP);
	print4data("kI", kI);
	print4data("kD", kD);
}

void printTitle(String title) {
	p("%s : ", title.c_str());
}
void showBoolResult(String title, bool val) {
	String res = (val) ? "Yes" : "No";
	printTitle(title);
	SerialUSB.println(res);
}

template <class T>
T print4data(String title, T* val) {
	printTitle(title);
	for (uint8_t i = 0; i < 4; i++)
	{
		SerialUSB.print(val[i]);
		if (i < 3) SerialUSB.print(", ");
	}
	SerialUSB.println();
}


void show4Bool(String title, bool* val) {
	printTitle(title);
	SerialUSB.print(" ");
	for (uint8_t i = 0; i < 4; i++)
	{
		String res = (val[i]) ? "Yes" : "No";
		SerialUSB.print(res);
		if (i < 3) SerialUSB.print(", ");
	}
	SerialUSB.println();
}

void showIpAddress(String title, IPAddress ip) {
	p("%s : %d.%d.%d.%d\n", title.c_str(), ip[0], ip[1], ip[2], ip[3]);
}

void boldHeader(String header) {
	p("============== %s ==============\n", header.c_str());
}
void printHeader(String header) {
	p("-------------- %s --------------\n", header.c_str());
}

#pragma endregion 
