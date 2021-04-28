// 
// 
// 

#include "diagnosis.h"
#include "utils.h"

String configVersionCompareString[5] = {
	F("CONFIG_VERSION_UNDEFINED"),
	F("CONFIG_VERSION_NOTLOADED"),
	F("CONFIG_VERSION_OLD"),
	F("CONFIG_VERSION_APPLICABLE"),
	F("CONFIG_VERSION_NEW")
};
// =============================================================================
// Diagnosis via USB serial
// =============================================================================

void diagnosisCommand(uint8_t inByte) {
	switch (inByte)
	{
	case 'm':
		printMenu();
		break;
	case 'c':
		printConfigurations();
		break;
	case 's':
		printCurrentState();
		break;
	case 't':
		testMotion();
		break;
	default:
		break;
	}
}

void printMenu() {
	boldHeader("Diagnosis menu");
	p("s: show status\n");
	p("c: show config\n");
	p("t: test motion\n");
}

void testMotion() {
	for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
		if (checkMotionStartConditions(i, dir)) {
			stepper[i].move(FWD, 25600);
		}
	}
}
void printCurrentState() {
	String s;
	bool bt;
	boldHeader("Current Status");
	printHeader("Firmware");
	p("Firmware name : %s\n", firmwareName);
	p("Firmware version : %d.%d.%d\n",firmwareVersion[0],firmwareVersion[1],firmwareVersion[2]);
	p("Compile date : %s, %s\n", COMPILE_DATE, COMPILE_TIME);
	p("Applicable config version : %d.%d\n", applicableConfigVersion[0],applicableConfigVersion[1]);
	p("Loaded config version : %d.%d [%s]\n", loadedConfigVersion[0], loadedConfigVersion[1],
		configVersionCompareString[checkConfigVersion()].c_str());
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
	showBoolResult(F("isDestIpSet"), isDestIpSet);
	showIpAddress(F("Destination Ip"), destIp);
	showIpAddress(F("Current My Ip"), myIp);
	p("Current MAC address : %02X:%02X:%02X:%02X:%02X:%02X\n",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	p("Current outPort : %d\n", outPort);

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
			s = (bt ? "Forward" : "Reverse");
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
	
	printHeader("Modes");
	show4Bool(F("Servo Mode"),isServoMode);
	show4Bool(F("Current Mode"), isCurrentMode);
	show4Bool(F("Electromagnetic Brake Enable"),electromagnetBrakeEnable);
	p("Brake status :\n");
	String bsText[4] = {"BRAKE_ENGAGED","BRAKE_DISENGAGE_WAITING","BRAKE_DISENGAGED","BRAKE_MOTORHIZ_WAITING"};
	for (uint8_t i=0; i<NUM_OF_MOTOR; i++) {
		p("#%d : %s\n",i+1,bsText[brakeStatus[i]].c_str());
	}
	print4data(F("Homing status"), homingStatus);
}


void printConfigurations() {
	boldHeader("Configurations");
	printHeader("Config file");
	//showBoolResult(F("SD library initialize succeeded"), sdInitializeSucceeded);
	showBoolResult(F("SD config file open succeeded"), configFileOpenSucceeded);
	showBoolResult(F("SD config file parse succeeded"), configFileParseSucceeded);
	p("configTargetProduct : %s\n", configTargetProduct.c_str());
	p("configName : %s\n", configName.c_str());
	p("config version : %d.%d [%s]\n", loadedConfigVersion[0], loadedConfigVersion[1],
		configVersionCompareString[checkConfigVersion()].c_str());

	printHeader("Network");
	showIpAddress(F("My Ip from Config"), myIp_from_config);
	showBoolResult(F("isMyIpAddId"), isMyIpAddId);
	showIpAddress(F("Dest Ip"), destIp);
	showIpAddress(F("DNS"), dns);
	showIpAddress(F("Gateway"), gateway);
	showIpAddress(F("Subnet mask"), subnet);
	p("MAC address from Config: %02X:%02X:%02X:%02X:%02X:%02X\n",
		mac_from_config[0], 
		mac_from_config[1], 
		mac_from_config[2], 
		mac_from_config[3], 
		mac_from_config[4], 
		mac_from_config[5]);
	showBoolResult(F("isMacAddId"), isMacAddId);
	p("inPort : %d\n", inPort);
	p("outPort from Config : %d\n", outPort_from_config);
	showBoolResult(F("isOutPortAddId"), isOutPortAddId);
	showBoolResult(F("bootedMsgEnable"), bootedMsgEnable);
	showBoolResult(F("isDestIpSet"), isDestIpSet);
	showBoolResult(F("reportErrors"), reportErrors);

	printHeader("Report & Alarm");
	show4Bool("reportBUSY", reportBUSY); 
	show4Bool(F("reportBUSY"), reportBUSY);
	show4Bool(F("reportHiZ"), reportHiZ);
	show4Bool(F("reportHomeSwStatus"), reportHomeSwStatus);
	show4Bool(F("reportLimitSwStatus"), reportLimitSwStatus);
	show4Bool(F("reportDir"), reportDir);
	show4Bool(F("reportMotorStatus"), reportMotorStatus);
	show4Bool(F("reportSwEvn"), reportSwEvn);
	show4Bool(F("reportUVLO"), reportUVLO);
	show4Bool(F("reportThermalStatus"), reportThermalStatus);
	show4Bool(F("reportOCD"), reportOCD);
	show4Bool(F("reportStall"), reportStall);
	show4Bool(F("reportOCD"), reportOCD);
	print4data("OCThreshold", overCurrentThreshold);

	printHeader("driverSettings");
	show4Bool(F("homingAtStartup"), bHomingAtStartup);
	// show4Bool(F("homingDirection(1:FWD,0:REV)"),homingDirection);
	p("homingDirection(1:FWD,0:REV) : %d, %d, %d, %d\n", homingDirection[0], homingDirection[1], homingDirection[2], homingDirection[3]);
	print4data(F("homingSpeed"), homingSpeed);
	print4data(F("homeSwMode"), homeSwMode);
	show4Bool(F("prohibitMotionOnHomeSw"),bProhibitMotionOnHomeSw);
	print4data(F("limitSwMode"), limitSwMode);
	show4Bool(F("prohibitMotionOnLimitSw"),bProhibitMotionOnLimitSw);
	print4data(F("goUntilTimeout"), goUntilTimeout);
	print4data(F("releaseSwTimeout"), releaseSwTimeout);
	print4data("microStepMode", microStepMode);
	show4Bool(F("isCurrentMode"), isCurrentMode);
	print4data("slewRate", slewRateNum);
	show4Bool(F("electromagnetBrakeEnable"), electromagnetBrakeEnable);
	print4data(F("brakeTransitionDuration"), brakeTransitionDuration);

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
