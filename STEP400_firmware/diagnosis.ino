void diagnosis(uint8_t inByte) {
	switch (inByte)
	{
	case 'c':
		printLoadedConfig();
		break;
	case 's':
		printCurrentState();
		break;
	case 't':
		testDipSw();
		testPowerSTEP01();
		break;
	default:
		break;
	}
}
void testDipSw() {
	showHeader("DIP Switch");
	uint8_t t = getMyId();
	for (uint8_t i = 0; i < 8; i++) {
		SerialUSB.print(((t >> (7 - i)) & 1) == 1 ? "1" : "0");
		if (i == 3) SerialUSB.print(" ");
	}
	SerialUSB.println();
}
void testPowerSTEP01() {
	showHeader("Hardware test start");
	uint8_t i = 0;
	uint16_t status[NUM_OF_MOTOR];
	uint32_t temp = 0;

	//SerialUSB.println(F("PowerSTEP01 diagnosis started."));
	for (i = 0; i < NUM_OF_MOTOR; i++) {
		status[i] = stepper[i].getStatus();
		temp += status[i];
	}
	if (temp == 0) {
		// No responce
		SerialUSB.println(F("PowerSTEP01 SPI connection failure."));
	}
	else {
		SerialUSB.println(F("PowerSTEP01 SPI connection ok."));
		for ( i = 0; i < NUM_OF_MOTOR; i++)
		{
			temp = 0;
			SerialUSB.print(F("PowerSTEP01 ID#"));
			SerialUSB.println(i + 1);
			SerialUSB.print(F(" STATUS:"));
			SerialUSB.print(status[i], HEX);
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
				SerialUSB.println(F("... Ok"));
				break;
			case 1:
				// OCD detected.
				SerialUSB.println(F("OCD(Over Current) detected."));
				break;
			case 2:
				// ULVO detected.
				SerialUSB.println(F("UVLO(Under Voltage LockOut) detected. Check VCC pin connection."));
				break;
			case 3:
				// OCD+ULVO detected.
				SerialUSB.println(F("OCD+UVLO detected. Check clock pin connection."));
				break;
			default:
				break;
			}

			// SW_F, low for open, high for close
			if ((status[i] & STATUS_SW_F) == 1) {
				SerialUSB.println(F("HOME senser input closed. Check SWIN connection."));
			}
			// ADC
			temp = stepper[i].getParam(ADC_OUT);
			SerialUSB.print(F(" ADC_OUT:"));
			SerialUSB.print(temp);
			if (temp < 31) {
				SerialUSB.println(F("... Wrong value. Chech ADC_OUT pin connection."));
			}
			else {
				SerialUSB.println(F("... Ok"));
			}
		}
	}

}
void printCurrentState() {
	SerialUSB.print("Firmware name:");
	String s = COMPILE_DATE;
	s += String(" ") + String(COMPILE_TIME) + String(" ") + String(FIRMWARE_NAME);
	SerialUSB.println(s);
	showHeader("DIP Switch");
	uint8_t t = getMyId();
	for (uint8_t i = 0; i < 8; i++) {
		SerialUSB.print(((t >> (7-i)) & 1) == 1 ? "1" : "0");
		if (i == 3) SerialUSB.print(" ");
	}
	SerialUSB.println();
	showHeader("Ethernet");
	SerialUSB.print(F("Ethernet hardware status: "));
	t = Ethernet.hardwareStatus();
	SerialUSB.print(t);
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
	SerialUSB.print( F("Ethernet link status: ") );
	t = Ethernet.linkStatus();
	SerialUSB.print(t);
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
	showHeader("microSD");
	showBoolResult(F("SD library initialize succeeded"), sdInitializeSucceeded);
	showBoolResult(F("SD config file open succeeded"), configFileOpenSucceeded);
	showBoolResult(F("SD config JSON parse succeeded"), configFileParseSucceeded);
	showHeader("PowerSTEP01");
	SerialUSB.print(F("STATUS"));
	for (uint8_t i = 0; i < NUM_OF_MOTOR; i++)
	{
		SerialUSB.print(F(", "));
		SerialUSB.print(stepper[i].getStatus());
	}
	SerialUSB.println();
}


#pragma region print_config
void printLoadedConfig() {
	SerialUSB.print("configName:");
	SerialUSB.println(configName.c_str());
	showBoolResult(F("SD library initialize succeeded"), sdInitializeSucceeded);
	showBoolResult(F("SD config file open succeeded"),configFileOpenSucceeded);
	showBoolResult(F("SD config file parse succeeded"), configFileParseSucceeded);
	//
	//showBoolResult(F(""), );
	showHeader("Network");
	showIpAddress(F("My Ip"), myIp);
	showIpAddress(F("Dest Ip"), destIp);
	showIpAddress(F("DNS"), dns);
	showIpAddress(F("Gateway"), gateway);
	showIpAddress(F("Subnet mask"), subnet);
	showBoolResult(F("isMyIpAddId"), isMyIpAddId);
	showBoolResult(F("isMacAddId"), isMacAddId);
	showBoolResult(F("bootedMsgEnable"), bootedMsgEnable);
	showBoolResult(F("isDestIpSet"), isDestIpSet);

	showHeader("Report & Alarm");
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
	show4Bytes(F("OCThreshold"), overCurrentThreshold);

	showHeader("driverSettings");
	show4Bytes(F("microStepMode"), microStepMode);
	show4Bool(F("homeSwMode"), homeSwMode);
	show4Bool(F("limitSwMode"), limitSwMode);
	show4Bool(F("isCurrentMode"), isCurrentMode);
	show4Bytes(F("slewRate"), slewRateNum);
	show4Bool(F("electromagnetBrakeEnable"), electromagnetBrakeEnable);

	showHeader("speedProfile");
	show4Floats(F("acc"), acc);
	show4Floats(F("dec"), dec);
	show4Floats(F("maxSpeed"), maxSpeed);
	show4Floats(F("fullStepSpeed"), fullStepSpeed);

	showHeader("Voltage mode");
	show4Bytes(F("kvalHold"), kvalHold);
	show4Bytes(F("kvalRun"), kvalRun);
	show4Bytes(F("kvalAcc"), kvalAcc);
	show4Bytes(F("kvalDec"), kvalDec);
	show4Int16s(F("intersectSpeed"), intersectSpeed);
	show4Bytes(F("startSlope"), startSlope);
	show4Bytes(F("accFinalSlope"), accFinalSlope);
	show4Bytes(F("decFinalSlope"), decFinalSlope);
	show4Bytes(F("stallThreshold"), stallThreshold);
	show4Floats(F("lowSpeedOptimize"), lowSpeedOptimize);

	showHeader("Current mode");
	show4Bytes(F("tvalHold"), tvalHold);
	show4Bytes(F("tvalRun"), tvalRun);
	show4Bytes(F("tvalAcc"), tvalAcc);
	show4Bytes(F("tvalDec"), tvalDec);
	show4Bytes(F("fastDecaySetting"), fastDecaySetting);
	show4Bytes(F("minOnTime"), minOnTime);
	show4Bytes(F("minOffTime"), minOffTime);

	showHeader("Servo mode");
	show4Floats(F("kP"), kP);
	show4Floats(F("kI"), kI);
	show4Floats(F("kD"), kD);

	showHeader("Print config END");
}

void printTitle(String title) {
	SerialUSB.print(title);
	SerialUSB.print("\t: ");
}
void showBoolResult(String title, bool val) {
	String res = (val) ? "Yes" : "No";
	printTitle(title);
	SerialUSB.println(res);
}

void show4Bool(String title, bool* val) {
	printTitle(title);
	SerialUSB.print(" ");
	for (uint8_t i = 0; i < 4; i++)
	{
		String res = (val[i]) ? " Yes" : " No";
		SerialUSB.print(res);
		if (i < 3) SerialUSB.print(",\t");
	}
	SerialUSB.println();
}
void show4Bytes(String title, uint8_t* val) {
	printTitle(title);
	for (uint8_t i = 0; i < 4; i++)
	{
		SerialUSB.print(val[i]);
		if (i < 3) SerialUSB.print(",\t");
	}
	SerialUSB.println();
}
void show4Int16s(String title, uint16_t* val) {
	printTitle(title);
	for (uint8_t i = 0; i < 4; i++)
	{
		SerialUSB.print(val[i]);
		if (i < 3) SerialUSB.print(",\t");
	}
	SerialUSB.println();
}
void show4Floats(String title, float* val) {
	printTitle(title);
	for (uint8_t i = 0; i < 4; i++)
	{
		SerialUSB.print(val[i]);
		if (i < 3) SerialUSB.print(",\t");
	}
	SerialUSB.println();
}
void showIpAddress(String title, IPAddress ip) {
	printTitle(title);
	for (uint8_t i = 0; i < 4; i++)
	{
		SerialUSB.print(ip[i]);
		if (i < 3) SerialUSB.print(".");
	}
	SerialUSB.println();
}

void showHeader(String header) {
	String line = " -------------- ";
	SerialUSB.print(line);
	SerialUSB.print(header);
	SerialUSB.println(line);
}
#pragma endregion 
