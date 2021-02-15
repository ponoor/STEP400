// 
// 
// 

#include "oscListeners.h"
#include "utils.h"

void OSCMsgReceive() {
    bool bMsgHasError = false, bMsgRouted = false;
    OSCMessage msgIN;
    int size;
    if ((size = Udp.parsePacket()) > 0) {
        while (size--)
            msgIN.fill(Udp.read());

        bMsgHasError = msgIN.hasError();
        if (!bMsgHasError) {
            // some possible frequent messages
            bMsgRouted |= msgIN.route("/setTargetPosition", setTargetPosition);
            bMsgRouted |= msgIN.route("/setTargetPositionList", setTargetPositionList);
            bMsgRouted |= msgIN.route("/getPosition", getPosition);
            bMsgRouted |= msgIN.route("/getSpeed", getSpeed);
            bMsgRouted |= msgIN.route("/run", run);
            bMsgRouted |= msgIN.route("/runRaw", runRaw);

            // motion
            bMsgRouted |= msgIN.route("/move", move);
            bMsgRouted |= msgIN.route("/goTo", goTo);
            bMsgRouted |= msgIN.route("/goToDir", goToDir);
            bMsgRouted |= msgIN.route("/goUntil", goUntil);
            bMsgRouted |= msgIN.route("/goUntilRaw", goUntilRaw);
            bMsgRouted |= msgIN.route("/releaseSw", releaseSw);
            bMsgRouted |= msgIN.route("/goHome", goHome);
            bMsgRouted |= msgIN.route("/goMark", goMark);
            bMsgRouted |= msgIN.route("/setMark", setMark);
            bMsgRouted |= msgIN.route("/getMark", getMark);
            bMsgRouted |= msgIN.route("/setPosition", setPosition);
            bMsgRouted |= msgIN.route("/resetPos", resetPos);
            bMsgRouted |= msgIN.route("/resetDev", resetDev);
            bMsgRouted |= msgIN.route("/softStop", softStop);
            bMsgRouted |= msgIN.route("/hardStop", hardStop);
            bMsgRouted |= msgIN.route("/softHiZ", softHiZ);
            bMsgRouted |= msgIN.route("/hardHiZ", hardHiZ);
            bMsgRouted |= msgIN.route("/excitation", excitation);

            // servo mode
            bMsgRouted |= msgIN.route("/enableServoMode", enableServoMode);
            bMsgRouted |= msgIN.route("/setServoParam", setServoParam);
            bMsgRouted |= msgIN.route("/getServoParam", getServoParam);

            // speed
            bMsgRouted |= msgIN.route("/setSpeedProfile", setSpeedProfile);
            bMsgRouted |= msgIN.route("/setMaxSpeed", setMaxSpeed);
            bMsgRouted |= msgIN.route("/setFullstepSpeed", setFullstepSpeed);
            bMsgRouted |= msgIN.route("/getFullstepSpeed", getFullstepSpeed);
            bMsgRouted |= msgIN.route("/setAcc", setAcc);
            bMsgRouted |= msgIN.route("/setDec", setDec);
            bMsgRouted |= msgIN.route("/getSpeedProfile", getSpeedProfile);

            // Kval
            bMsgRouted |= msgIN.route("/setKval", setKval);
            bMsgRouted |= msgIN.route("/setAccKval", setAccKval);
            bMsgRouted |= msgIN.route("/setDecKval", setDecKval);
            bMsgRouted |= msgIN.route("/setRunKval", setRunKval);
            bMsgRouted |= msgIN.route("/setHoldKval", setHoldKval);
            bMsgRouted |= msgIN.route("/getKval", getKval);

            //TVAL
            bMsgRouted |= msgIN.route("/setTval", setTval);
            bMsgRouted |= msgIN.route("/setAccTval", setAccTval);
            bMsgRouted |= msgIN.route("/setDecTval", setDecTval);
            bMsgRouted |= msgIN.route("/setRunTval", setRunTval);
            bMsgRouted |= msgIN.route("/setHoldTval", setHoldTval);
            bMsgRouted |= msgIN.route("/getTval", getTval);
            bMsgRouted |= msgIN.route("/getTval_mA", getTval_mA);

            // config
            bMsgRouted |= msgIN.route("/setDestIp", setDestIp);
            bMsgRouted |= msgIN.route("/getVersion", getVersion);
            bMsgRouted |= msgIN.route("/getConfigName", getConfigName);
            bMsgRouted |= msgIN.route("/getConfigRegister", getConfigRegister);
            bMsgRouted |= msgIN.route("/getStatus", getStatus);
            bMsgRouted |= msgIN.route("/getStatusList", getStatusList);
            bMsgRouted |= msgIN.route("/getHomeSw", getHomeSw);
            bMsgRouted |= msgIN.route("/getBusy", getBusy);
            bMsgRouted |= msgIN.route("/getUvlo", getUvlo);
            bMsgRouted |= msgIN.route("/getMotorStatus", getMotorStatus);
            bMsgRouted |= msgIN.route("/getThermalStatus", getThermalStatus);
            bMsgRouted |= msgIN.route("/resetMotorDriver", resetMotorDriver);
            //bMsgRouted |= msgIN.route("/enableFlagReport", enableFlagReport);
            bMsgRouted |= msgIN.route("/enableBusyReport", enableBusyReport);
            bMsgRouted |= msgIN.route("/enableHizReport", enableHizReport);
            bMsgRouted |= msgIN.route("/enableHomeSwReport", enableHomeSwReport);
            bMsgRouted |= msgIN.route("/enableDirReport", enableDirReport);
            bMsgRouted |= msgIN.route("/enableMotorStatusReport", enableMotorStatusReport);
            bMsgRouted |= msgIN.route("/enableSwEventReport", enableSwEventReport);
            bMsgRouted |= msgIN.route("/enableCommandErrorReport", enableCommandErrorReport);
            bMsgRouted |= msgIN.route("/enableUvloReport", enableUvloReport);
            bMsgRouted |= msgIN.route("/enableThermalStatusReport", enableThermalStatusReport);
            bMsgRouted |= msgIN.route("/enableOverCurrentReport", enableOverCurrentReport);
            bMsgRouted |= msgIN.route("/enableStallReport", enableStallReport);
            //bMsgRouted |= msgIN.route("/getDir", getDir);
            bMsgRouted |= msgIN.route("/getLimitSw", getLimitSw);
            bMsgRouted |= msgIN.route("/getLimitSwMode", getLimitSwMode);
            bMsgRouted |= msgIN.route("/setLimitSwMode", setLimitSwMode);
            bMsgRouted |= msgIN.route("/enableLimitSwReport", enableLimitSwReport);
            bMsgRouted |= msgIN.route("/enableElectromagnetBrake", enableElectromagnetBrake);

            bMsgRouted |= msgIN.route("/setMicrostepMode", setMicrostepMode);
            bMsgRouted |= msgIN.route("/getMicrostepMode", getMicrostepMode);
            bMsgRouted |= msgIN.route("/getHomeSwMode", getHomeSwMode);
            bMsgRouted |= msgIN.route("/setHomeSwMode", setHomeSwMode);
            bMsgRouted |= msgIN.route("/setStallThreshold", setStallThreshold);
            bMsgRouted |= msgIN.route("/getStallThreshold", getStallThreshold);
            bMsgRouted |= msgIN.route("/setOverCurrentThreshold", setOverCurrentThreshold);
            bMsgRouted |= msgIN.route("/getOverCurrentThreshold", getOverCurrentThreshold);
            bMsgRouted |= msgIN.route("/setLowSpeedOptimizeThreshold", setLowSpeedOptimizeThreshold);
            bMsgRouted |= msgIN.route("/getLowSpeedOptimizeThreshold", getLowSpeedOptimizeThreshold);


            bMsgRouted |= msgIN.route("/setSpeedProfileRaw", setSpeedProfileRaw);
            bMsgRouted |= msgIN.route("/setMaxSpeedRaw", setMaxSpeedRaw);
            bMsgRouted |= msgIN.route("/setMinSpeedRaw", setMinSpeedRaw);
            bMsgRouted |= msgIN.route("/setFullstepSpeedRaw", setFullstepSpeedRaw);
            bMsgRouted |= msgIN.route("/setAccRaw", setAccRaw);
            bMsgRouted |= msgIN.route("/setDecRaw", setDecRaw);
            bMsgRouted |= msgIN.route("/getSpeedProfileRaw", getSpeedProfileRaw);

            bMsgRouted |= msgIN.route("/setVoltageMode", setVoltageMode);
            bMsgRouted |= msgIN.route("/setCurrentMode", setCurrentMode);
            bMsgRouted |= msgIN.route("/setBemfParam", setBemfParam);
            bMsgRouted |= msgIN.route("/getBemfParam", getBemfParam);
            bMsgRouted |= msgIN.route("/setDecayModeParam", setDecayModeParam);
            bMsgRouted |= msgIN.route("/getDecayModeParam", getDecayModeParam);
            bMsgRouted |= msgIN.route("/getAdcVal", getAdcVal);
            bMsgRouted |= msgIN.route("/setBrakeOut", setBrakeOut);
            turnOnRXL();
            //digitalWrite(ledPin, bMsgRouted);
            if (!bMsgRouted) {
                sendOneDatum("/error/osc", "MessageNotMatch");
                
            }
        }
        else {
            sendOneDatum("/error/osc", "OscSyntaxError");
        }
    }
}

bool isCorrectMotorId(uint8_t motorID) {
    return (MOTOR_ID_FIRST <= motorID) && (motorID <= MOTOR_ID_LAST);
}

#pragma region config_commands_osc_listener
void setDestIp(OSCMessage& msg, int addrOffset) {
    bool bIpUpdated = false;
    OSCMessage newMes("/destIp");
    for (auto i = 0; i < 4; i++)
    {
        bIpUpdated |= (destIp[i] != Udp.remoteIP()[i]);
        newMes.add(Udp.remoteIP()[i]);
    }
    destIp = Udp.remoteIP();
    newMes.add(bIpUpdated);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    isDestIpSet = true;
    turnOnTXL();
}

void getVersion(OSCMessage& msg, int addrOffset) {
    String version = COMPILE_DATE;
    version += String(" ") + String(COMPILE_TIME) + String(" ") + String(FIRMWARE_NAME);
    sendOneDatum("/version", version.c_str());
}

void getConfigName(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/configName");
    newMes.add(configName.c_str()).add(sdInitializeSucceeded).add(configFileOpenSucceeded).add(configFileParseSucceeded);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getConfigRegister(uint8_t deviceID) {
    sendTwoData("/configRegister", deviceID, stepper[deviceID - MOTOR_ID_FIRST].getParam(CONFIG));
}
void getConfigRegister(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getConfigRegister(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getConfigRegister(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

// reset the motor driver chip and setup it
void resetMotorDriver(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        resetMotorDriver(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            resetMotorDriver(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getAdcVal(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/adcVal", motorID, stepper[motorID - MOTOR_ID_FIRST].getParam(ADC_OUT));
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/adcVal", i + MOTOR_ID_FIRST, stepper[i].getParam(ADC_OUT));
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setBrakeOut(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        digitalWrite(brakePin[motorID - MOTOR_ID_FIRST], (getInt(msg, 1) > 0));
    }
}

// simply send reset command to the driverchip via SPI
void resetDev(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].resetDev();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].resetDev();
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void enableBusyReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportBUSY[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportBUSY[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void enableHizReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportHiZ[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportHiZ[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableHomeSwReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportHomeSwStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportHomeSwStatus[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableLimitSwReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportLimitSwStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportLimitSwStatus[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableDirReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportDir[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportDir[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableMotorStatusReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportMotorStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportMotorStatus[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableSwEventReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportSwEvn[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportSwEvn[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableCommandErrorReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportCommandError[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportCommandError[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableUvloReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportUVLO[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportUVLO[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableThermalStatusReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportThermalStatus[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportThermalStatus[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableOverCurrentReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportOCD[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportOCD[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void enableStallReport(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        reportStall[motorID - MOTOR_ID_FIRST] = bEnable;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            reportStall[i] = bEnable;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getHomeSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getHomeSw(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getHomeSw(i + 1);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getHomeSw(uint8_t motorID) {
    sendThreeInt("/homeSw", motorID, homeSwState[motorID - MOTOR_ID_FIRST], dir[motorID - MOTOR_ID_FIRST]);
}
void getLimitSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getLimitSw(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getLimitSw(i + 1);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getLimitSw(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/limitSw");
    newMes.add(motorID).add(limitSwState[motorID - MOTOR_ID_FIRST]).add(dir[motorID - MOTOR_ID_FIRST]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getBusy(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/busy", motorID, busy[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/busy", i + MOTOR_ID_FIRST, busy[i]);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getUvlo(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/uvlo", motorID, uvloStatus[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/uvlo", i + 1, uvloStatus[i]);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getMotorStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/motorStatus", motorID, motorStatus[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/motorStatus", i + 1, motorStatus[i]);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getThermalStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/thermalStatus", motorID, thermalStatus[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/thermalStatus", i + 1, thermalStatus[i]);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getStatus(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/status", motorID, stepper[motorID - MOTOR_ID_FIRST].getStatus());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/status", i + MOTOR_ID_FIRST, stepper[i].getStatus());
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getStatusList(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/statusList");
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
        newMes.add((int32_t)stepper[i].getStatus());
    }

    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void setMicrostepMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t value = getInt(msg, 1);
    value = constrain(value, STEP_FS, STEP_FS_128); // 0-7
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].configStepMode(value);
        microStepMode[motorID - MOTOR_ID_FIRST] = value;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].configStepMode(value);
            microStepMode[i] = value;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getMicrostepMode(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/microstepMode", motorID, stepper[motorID - MOTOR_ID_FIRST].getStepMode());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/microstepMode", i + MOTOR_ID_FIRST, stepper[i].getStepMode());
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getHomeSwMode(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/homeSwMode", motorID, stepper[motorID - MOTOR_ID_FIRST].getSwitchMode() > 0);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/homeSwMode", i + MOTOR_ID_FIRST, stepper[i].getSwitchMode() > 0);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setHomeSwMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t value = (getBool(msg, 1)) ? SW_USER : SW_HARD_STOP;
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setSwitchMode(value);
        homeSwMode[motorID - MOTOR_ID_FIRST] = (value > 0);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setSwitchMode(value);
            homeSwMode[i] = (value > 0);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getLimitSwMode(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/limitSwMode", motorID, limitSwMode[motorID - MOTOR_ID_FIRST]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/limitSwMode", i + MOTOR_ID_FIRST, limitSwMode[i] > 0);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setLimitSwMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t switchMode = (getBool(msg, 1)) ? SW_USER : SW_HARD_STOP;
    if(isCorrectMotorId(motorID)) {
        limitSwMode[motorID - MOTOR_ID_FIRST] = switchMode > 0;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            limitSwMode[i] = switchMode > 0;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
// STALL_TH register is 5bit in PowerSTEP01, 7bit in L6470
void setStallThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t threshold = getInt(msg, 1) & 0x1F; // 5bit
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setParam(STALL_TH, threshold);
        getStallThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setParam(STALL_TH, threshold);
            getStallThreshold(i + 1);
        }
    } else {
        sendMotorIdError(motorID);
    }

}
void getStallThreshold(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    uint8_t stall_th_raw = stepper[motorId - MOTOR_ID_FIRST].getParam(STALL_TH) & 0x1F;
    float threshold = (stall_th_raw + 1) * 312.5;
    sendTwoData("/stallThreshold", motorId, threshold);
}
void getStallThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getStallThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getStallThreshold(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
// OCD_TH register is 5bit in PowerSTEP01, 4bit in L6470
void setOverCurrentThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t threshold = getInt(msg, 1) & 0x1F; // 5bit
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setParam(OCD_TH, threshold);
        getOverCurrentThreshold(motorID);
        overCurrentThreshold[motorID - MOTOR_ID_FIRST] = threshold;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setParam(OCD_TH, threshold);
            overCurrentThreshold[i] = threshold;
            getOverCurrentThreshold(i + 1);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getOverCurrentThreshold(uint8_t motorId) {
    if (!isDestIpSet) { return; }
    uint8_t ocd_th_raw = stepper[motorId - MOTOR_ID_FIRST].getParam(OCD_TH) & 0x1F;
    float threshold = (ocd_th_raw + 1) * 312.5;
    sendTwoData("/overCurrentThreshold", motorId, threshold);
}
void getOverCurrentThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getOverCurrentThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getOverCurrentThreshold(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setLowSpeedOptimizeThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _minSpeed = getFloat(msg,1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setMinSpeed(_minSpeed);
        lowSpeedOptimize[motorID] = _minSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMinSpeed(_minSpeed);
            lowSpeedOptimize[i] = _minSpeed;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getLowSpeedOptimizeThreshold(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getLowSpeedOptimizeThreshold(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getLowSpeedOptimizeThreshold(i + 1);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getLowSpeedOptimizeThreshold(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    bool optimizationEnabled = (stepper[motorID - MOTOR_ID_FIRST].getParam(MIN_SPEED) & (1 << 12)) > 0;
    OSCMessage newMes("/lowSpeedOptimizeThreshold");
    newMes.add((int32_t)motorID);
    newMes.add(stepper[motorID - MOTOR_ID_FIRST].getMinSpeed());
    newMes.add(optimizationEnabled);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void setBemfParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t intSpeed = constrain(getInt(msg, 1), 0, 0x3FFF);
    uint8_t
        stSlp = constrain(getInt(msg, 2), 0, 255),
        fnSlpAcc = constrain(getInt(msg, 3), 0, 255),
        fnSlpDec = constrain(getInt(msg, 4), 0, 255);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        intersectSpeed[motorID] = intSpeed;
        startSlope[motorID] = stSlp;
        accFinalSlope[motorID] = fnSlpAcc;
        decFinalSlope[motorID] = fnSlpDec;
        stepper[motorID].setParam(INT_SPD, intersectSpeed[motorID]);
        stepper[motorID].setParam(ST_SLP, startSlope[motorID]);
        stepper[motorID].setParam(FN_SLP_ACC, accFinalSlope[motorID]);
        stepper[motorID].setParam(FN_SLP_DEC, decFinalSlope[motorID]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            intersectSpeed[i] = intSpeed;
            startSlope[i] = stSlp;
            accFinalSlope[i] = fnSlpAcc;
            decFinalSlope[i] = fnSlpDec;
            stepper[i].setParam(INT_SPD, intersectSpeed[i]);
            stepper[i].setParam(ST_SLP, startSlope[i]);
            stepper[i].setParam(FN_SLP_ACC, accFinalSlope[i]);
            stepper[i].setParam(FN_SLP_DEC, decFinalSlope[i]);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getBemfParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getBemfParam(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getBemfParam(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getBemfParam(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/bemfParam");
    newMes.add((int32_t)motorID);
    motorID -= MOTOR_ID_FIRST;
    newMes.add(intersectSpeed[motorID]).add(startSlope[motorID]).add(accFinalSlope[motorID]).add(decFinalSlope[motorID]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void setDecayModeParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t
        tFast = constrain(getInt(msg, 1), 0, 255),
        tOnMin = constrain(getInt(msg, 2), 0, 255),
        tOffMin = constrain(getInt(msg, 3), 0, 255);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        fastDecaySetting[motorID] = tFast;
        minOnTime[motorID] = tOnMin;
        minOffTime[motorID] = tOffMin;
        stepper[motorID].setParam(T_FAST, fastDecaySetting[motorID]);
        stepper[motorID].setParam(TON_MIN, minOnTime[motorID]);
        stepper[motorID].setParam(TOFF_MIN, minOffTime[motorID]);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            fastDecaySetting[i] = tFast;
            minOnTime[i] = tOnMin;
            minOffTime[i] = tOffMin;
            stepper[i].setParam(T_FAST, fastDecaySetting[i]);
            stepper[i].setParam(TON_MIN, minOnTime[i]);
            stepper[i].setParam(TOFF_MIN, minOffTime[i]);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getDecayModeParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getDecayModeParam(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getDecayModeParam(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getDecayModeParam(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/decayModeParam");
    newMes.add((int32_t)motorID);
    motorID -= MOTOR_ID_FIRST;
    newMes.add(fastDecaySetting[motorID]).add(minOnTime[motorID]).add(minOffTime[motorID]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void enableElectromagnetBrake(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        electromagnetBrakeEnable[motorID] = bEnable;
        if (bEnable) pinMode(brakePin[motorID], OUTPUT)
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            electromagnetBrakeEnable[i] = bEnable;
            if (bEnable) pinMode(brakePin[i], OUTPUT)
        }
    } else {
        sendMotorIdError(motorID);
    }
}
#pragma endregion config_commands_osc_listener

#pragma region kval_commands_osc_listener

void setKval(uint8_t motorID, uint8_t hold, uint8_t run, uint8_t acc, uint8_t dec) {            motorID -= MOTOR_ID_FIRST;
    if (!isCurrentMode[motorID]) {
        stepper[motorID].setHoldKVAL(hold);
        stepper[motorID].setRunKVAL(run);
        stepper[motorID].setAccKVAL(acc);
        stepper[motorID].setDecKVAL(dec);
    }
    kvalHold[motorID] = hold;
    kvalRun[motorID] = run;
    kvalAcc[motorID] = acc;
    kvalDec[motorID] = dec;
}

void setKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int hold = constrain(getInt(msg, 1), 0, 255);
    int run = constrain(getInt(msg, 2), 0, 255);
    int acc = constrain(getInt(msg, 3), 0, 255);
    int dec = constrain(getInt(msg, 4), 0, 255);
    if (isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        setKval(motorID, hold, run, acc, dec);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            setKval(i, hold, run, acc, dec);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setHoldKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);
    if(isCorrectMotorId(motorID)) {
        if (!isCurrentMode[motorID]) {
            stepper[motorID - MOTOR_ID_FIRST].setHoldKVAL(kvalInput);
        }
        kvalHold[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (!isCurrentMode[i]) {
                stepper[i].setHoldKVAL(kvalInput);
            }
            kvalHold[i] = kvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setRunKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);

    if(isCorrectMotorId(motorID)) {
        if (!isCurrentMode[motorID]) {
            stepper[motorID - MOTOR_ID_FIRST].setRunKVAL(kvalInput);
        }
        kvalRun[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (!isCurrentMode[i]) {
                stepper[i].setRunKVAL(kvalInput);
            }
            kvalRun[i] = kvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setAccKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);
    if(isCorrectMotorId(motorID)) {
        if (!isCurrentMode[motorID]) {
            stepper[motorID - MOTOR_ID_FIRST].setAccKVAL(kvalInput);
        }
        kvalAcc[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (!isCurrentMode[i]) {
                stepper[i].setAccKVAL(kvalInput);
            }
            kvalAcc[i] = kvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setDecKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t kvalInput = constrain(getInt(msg, 1), 0, 255);
    if(isCorrectMotorId(motorID)) {
        if (!isCurrentMode[motorID]) {
            stepper[motorID - MOTOR_ID_FIRST].setDecKVAL(kvalInput);
        }
        kvalDec[motorID - MOTOR_ID_FIRST] = kvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (!isCurrentMode[i]) {
                stepper[i].setDecKVAL(kvalInput);
            }
            kvalDec[i] = kvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getKval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getKval(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getKval(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getKval(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/kval");
    newMes.add((int32_t)motorID);
    motorID -= MOTOR_ID_FIRST;
    newMes.add(kvalHold[motorID]).add(kvalRun[motorID]).add(kvalAcc[motorID]).add(kvalDec[motorID]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
#pragma endregion kval_commands_osc_listener

#pragma region tval_commands_osc_listener
void setTval(uint8_t motorID, uint8_t hold, uint8_t run, uint8_t acc, uint8_t dec) {            motorID -= MOTOR_ID_FIRST;
    if (!isCurrentMode[motorID]) {
        stepper[motorID].setHoldTVAL(hold);
        stepper[motorID].setRunTVAL(run);
        stepper[motorID].setAccTVAL(acc);
        stepper[motorID].setDecTVAL(dec);
    }
    tvalHold[motorID] = hold;
    tvalRun[motorID] = run;
    tvalAcc[motorID] = acc;
    tvalDec[motorID] = dec;
}
void setTval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int hold = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
    int run = constrain(getInt(msg, 2), 0, TVAL_LIMIT_VAL);
    int acc = constrain(getInt(msg, 3), 0, TVAL_LIMIT_VAL);
    int dec = constrain(getInt(msg, 4), 0, TVAL_LIMIT_VAL);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        setTval(motorID, hold, run, acc, dec);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            setTval(i, hold, run, acc, dec);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setHoldTval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (isCurrentMode[motorID]) {
            stepper[motorID].setHoldTVAL(tvalInput);
        }
        tvalHold[motorID] = tvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (isCurrentMode[i]) {
                stepper[i].setHoldTVAL(tvalInput);
            }
            tvalHold[i] = tvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setRunTval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);

    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (isCurrentMode[motorID]) {
            stepper[motorID].setRunTVAL(tvalInput);
        }
        tvalRun[motorID] = tvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (isCurrentMode[i]) {
                stepper[i].setRunTVAL(tvalInput);
            }
            tvalRun[i] = tvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setAccTval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (isCurrentMode[motorID]) {
            stepper[motorID].setAccTVAL(tvalInput);
        }
        tvalAcc[motorID] = tvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (isCurrentMode[i]) {
                stepper[i].setAccTVAL(tvalInput);
            }
            tvalAcc[i] = tvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setDecTval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t tvalInput = constrain(getInt(msg, 1), 0, TVAL_LIMIT_VAL);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (isCurrentMode[motorID]) {
            stepper[motorID].setDecTVAL(tvalInput);
        }
        tvalDec[motorID] = tvalInput;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            if (isCurrentMode[i]) {
                stepper[i].setDecTVAL(tvalInput);
            }
            tvalDec[i] = tvalInput;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getTval(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getTval(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getTval(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getTval(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/tval");
    newMes.add((int32_t)motorID);
    motorID -= MOTOR_ID_FIRST;
    //newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getHoldTVAL());
    //newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getRunTVAL());
    //newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getAccTVAL());
    //newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getDecTVAL());
    newMes.add(tvalHold[motorID]).add(tvalRun[motorID]).add(tvalAcc[motorID]).add(tvalDec[motorID]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
float TvalToCurrent(uint8_t tval) {
    return (tval + 1) * 78.125f;
}
void getTval_mA(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/tval_mA");
    newMes.add((int32_t)motorID);
    motorID -= MOTOR_ID_FIRST;
    newMes.add(TvalToCurrent(tvalHold[motorID]));
    newMes.add(TvalToCurrent(tvalRun[motorID]));
    newMes.add(TvalToCurrent(tvalAcc[motorID]));
    newMes.add(TvalToCurrent(tvalDec[motorID]));
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
void getTval_mA(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getTval_mA(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getTval_mA(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
#pragma endregion tval_commands_osc_listener

#pragma region speed_commands_osc_listener

void setSpeedProfile(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _acc = getFloat(msg, 1);
    float _dec = getFloat(msg, 2);
    float _maxSpeed = getFloat(msg, 3);

    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setAcc(_acc);
        stepper[motorID].setDec(_dec);
        stepper[motorID].setMaxSpeed(_maxSpeed);
        acc[motorID] = _acc;
        dec[motorID] = _dec;
        maxSpeed[motorID] = _maxSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAcc(_acc);
            stepper[i].setDec(_dec);
            stepper[i].setMaxSpeed(_maxSpeed);
            acc[i] = _acc;
            dec[i] = _dec;
            maxSpeed[i] = _maxSpeed;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setMaxSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _maxSpeed = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setMaxSpeed(_maxSpeed);
        maxSpeed[motorID] = _maxSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMaxSpeed(_maxSpeed);
            maxSpeed[i] = _maxSpeed;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
// MIN_SPEED register is set by setLowSpeedOptimizeThreshold function.

void setFullstepSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _fullStepSpeed = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setFullSpeed(_fullStepSpeed);
        fullStepSpeed[motorID] = _fullStepSpeed;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setFullSpeed(_fullStepSpeed);
            fullStepSpeed[i] = _fullStepSpeed;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getFullstepSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _fullStepSpeed;
    if(isCorrectMotorId(motorID)) {
        _fullStepSpeed = stepper[motorID - MOTOR_ID_FIRST].getFullSpeed();
        sendTwoData("/fullstepSpeed", motorID, _fullStepSpeed);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            _fullStepSpeed = stepper[i].getFullSpeed();
            sendTwoData("/fullstepSpeed", i + 1, _fullStepSpeed);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setAcc(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _acc = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setAcc(_acc);
        acc[motorID] = _acc;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAcc(_acc);
            acc[i] = _acc;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setDec(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float _dec = getFloat(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        stepper[motorID].setDec(_dec);
        dec[motorID] = _dec;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setDec(_dec);
            dec[i] = _dec;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setSpeedProfileRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t _accRaw = getInt(msg, 1);
    uint16_t _decRaw = getInt(msg, 2);
    uint16_t _maxSpeedRaw = getInt(msg, 3);

    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setAccRaw(_accRaw);
        stepper[motorID - MOTOR_ID_FIRST].setDecRaw(_decRaw);
        stepper[motorID - MOTOR_ID_FIRST].setMaxSpeedRaw(_maxSpeedRaw);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAccRaw(_accRaw);
            stepper[i].setDecRaw(_decRaw);
            stepper[i].setMaxSpeedRaw(_maxSpeedRaw);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setMaxSpeedRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setMaxSpeedRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMaxSpeedRaw(t);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setMinSpeedRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setMinSpeedRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMinSpeedRaw(t);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setFullstepSpeedRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setFullSpeedRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setFullSpeedRaw(t);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setAccRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setAccRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setAccRaw(t);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setDecRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint16_t t = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setDecRaw(t);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setDecRaw(t);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getSpeed(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float s;
    if(isCorrectMotorId(motorID)) {
        s = stepper[motorID - MOTOR_ID_FIRST].getSpeed();
        if (dir[motorID - MOTOR_ID_FIRST] == REV) { s *= -1.0; }
        sendTwoData("/speed", motorID, s);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            s = stepper[i].getSpeed();
            if (dir[i] == REV) { s *= -1.0; }
            sendTwoData("/speed", i + MOTOR_ID_FIRST, s);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getSpeedProfile(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getSpeedProfile(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getSpeedProfile(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getSpeedProfile(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/speedProfile");
    newMes.add((int32_t)motorID);
    newMes.add((float)stepper[motorID - MOTOR_ID_FIRST].getAcc());
    newMes.add((float)stepper[motorID - MOTOR_ID_FIRST].getDec());
    newMes.add((float)stepper[motorID - MOTOR_ID_FIRST].getMaxSpeed());
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getSpeedProfileRaw(OSCMessage& msg, int addrOffset) {
    if (!isDestIpSet) { return; }
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getSpeedProfileRaw(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getSpeedProfileRaw(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getSpeedProfileRaw(uint8_t motorID) {
    OSCMessage newMes("/speedProfileRaw");
    newMes.add((int32_t)motorID);
    newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getAccRaw());
    newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getDecRaw());
    newMes.add((int32_t)stepper[motorID - MOTOR_ID_FIRST].getMaxSpeedRaw());
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}
#pragma endregion speed_commands_osc_listener

#pragma region operational_commands_osc_listener

void getPosition(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/position", motorID, stepper[motorID - MOTOR_ID_FIRST].getPos());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/position", i + MOTOR_ID_FIRST, stepper[i].getPos());
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void getMark(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        sendTwoData("/mark", motorID, stepper[motorID - MOTOR_ID_FIRST].getMark());
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            sendTwoData("/mark", i + MOTOR_ID_FIRST, stepper[i].getMark());
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void run(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float stepsPerSec = getFloat(msg, 1);
    float absSpeed = fabsf(stepsPerSec);
    boolean dir = stepsPerSec > 0;
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].run(dir, absSpeed);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].run(dir, absSpeed);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void runRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t speed = getInt(msg, 1);
    boolean dir = speed > 0;
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].runRaw(dir, abs(speed));
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].runRaw(dir, abs(speed));
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void move(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t steps = getInt(msg, 1);
    boolean dir = steps > 0;
    steps = abs(steps);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].move(dir, steps);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].move(dir, steps);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void goTo(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t pos = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].goTo(pos);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].goTo(pos);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void goToDir(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    boolean dir = getBool(msg, 1);
    int32_t pos = getInt(msg, 2);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].goToDir(dir, pos);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].goToDir(dir, pos);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void goUntil(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool action = getBool(msg, 1);
    float stepsPerSec = getFloat(msg, 2);
    bool dir = stepsPerSec > 0;
    stepsPerSec = fabsf(stepsPerSec);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].goUntil(action, dir, stepsPerSec);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].goUntil(action, dir, stepsPerSec);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void goUntilRaw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool action = getBool(msg, 1);
    int32_t speed = getInt(msg, 2);
    bool dir = speed > 0;
    speed = abs(speed);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].goUntilRaw(action, dir, speed);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].goUntilRaw(action, dir, speed);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void releaseSw(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    uint8_t action = getInt(msg, 1);
    bool dir = getBool(msg, 2);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].releaseSw(action, dir);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].releaseSw(action, dir);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void goHome(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].goHome();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].goHome();
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void goMark(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].goMark();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].goMark();
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setMark(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t newMark = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setMark(newMark);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setMark(newMark);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void setPosition(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t newPos = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].setPos(newPos);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].setPos(newPos);
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void resetPos(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        stepper[motorID - MOTOR_ID_FIRST].resetPos();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            stepper[i].resetPos();
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void softStop(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        isServoMode[motorID - MOTOR_ID_FIRST] = false;
        stepper[motorID - MOTOR_ID_FIRST].softStop();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            stepper[i].softStop();
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void hardStop(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        isServoMode[motorID - MOTOR_ID_FIRST] = false;
        stepper[motorID - MOTOR_ID_FIRST].hardStop();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            stepper[i].hardStop();
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void softHiZ(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        isServoMode[motorID - MOTOR_ID_FIRST] = false;
        stepper[motorID - MOTOR_ID_FIRST].softHiZ();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            stepper[i].softHiZ();
        }
    } else {
        sendMotorIdError(motorID);
    }
}
void hardHiZ(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        isServoMode[motorID - MOTOR_ID_FIRST] = false;
        stepper[motorID - MOTOR_ID_FIRST].hardHiZ();
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            isServoMode[i] = false;
            stepper[i].hardHiZ();
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void excitation(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool state = getBool(msg,1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        if (electromagnetBrakeEnable[motorID]) {
            if (!isCurrentMode[motorID]) {
                uint8_t t = kvalRun[motorID]>>1;
                if (kvalHold[motorID]< t) {
                    stepper[motorID].setHoldKVAL(t);
                }
            }
        }
        kvalHold[motorID] = kvalInput;
        }
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            electromagnetBrakeEnable[i] = state;
        }
    } else {
        sendMotorIdError(motorID);
    }
}
#pragma endregion operational_commands_osc_listener

#pragma region servo_commands_osc_listener

void setTargetPosition(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    int32_t position = getInt(msg, 1);
    if(isCorrectMotorId(motorID)) {
        targetPosition[motorID - MOTOR_ID_FIRST] = position;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            targetPosition[i] = position;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setTargetPositionList(OSCMessage& msg, int addrOffset) {
    for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
        targetPosition[i] = getInt(msg, i);
    }
}

void enableServoMode(uint8_t motorID, bool enable) {
    if (enable) {
        targetPosition[motorID] = stepper[motorID].getPos();
        reportBUSY[motorID] = false;
        reportMotorStatus[motorID] = false;
        reportDir[motorID] = false;
        stepper[motorID].hardStop();
    }
    else {
        stepper[motorID].softStop();
    }
    isServoMode[motorID] = enable;
}
void enableServoMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    bool bEnable = getBool(msg, 1);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        enableServoMode(motorID, bEnable);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            enableServoMode(i, bEnable);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setServoParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    float 
        _kp = getFloat(msg, 1), 
        _ki = getFloat(msg, 2), 
        _kd = getFloat(msg, 3);
    if (_kp <= 0.0) _kp = 0;
    if (_ki <= 0.0) _ki = 0;
    if (_kd <= 0.0) _kd = 0;
    if(isCorrectMotorId(motorID)) {
        kP[motorID - MOTOR_ID_FIRST] = _kp;
        kI[motorID - MOTOR_ID_FIRST] = _ki;
        kD[motorID - MOTOR_ID_FIRST] = _kd;
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            kP[i] = _kp;
            kI[i] = _ki;
            kD[i] = _kd;
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void getServoParam(uint8_t motorID) {
    if (!isDestIpSet) { return; }
    OSCMessage newMes("/servoParam");
    newMes.add(motorID);
    motorID -= MOTOR_ID_FIRST;
    newMes.add(kP[motorID]).add(kI[motorID]).add(kD[motorID]);
    Udp.beginPacket(destIp, outPort);
    newMes.send(Udp);
    Udp.endPacket();
    newMes.empty();
    turnOnTXL();
}

void getServoParam(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        getServoParam(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            getServoParam(i + MOTOR_ID_FIRST);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

#pragma endregion servo_commands_osc_listener


#pragma region PowerSTEP01_config_osc_listener

void setVoltageMode(uint8_t motorID) {
    stepper[motorID].hardHiZ();
    stepper[motorID].setPWMFreq(PWM_DIV_1, PWM_MUL_0_75);
    stepper[motorID].setHoldKVAL(kvalHold[motorID]);
    stepper[motorID].setRunKVAL(kvalRun[motorID]);
    stepper[motorID].setAccKVAL(kvalAcc[motorID]);
    stepper[motorID].setDecKVAL(kvalDec[motorID]);
    stepper[motorID].setParam(ST_SLP, startSlope[motorID]);
    stepper[motorID].setParam(FN_SLP_ACC, accFinalSlope[motorID]);
    stepper[motorID].setParam(FN_SLP_DEC, decFinalSlope[motorID]);
    stepper[motorID].setVoltageMode();
    isCurrentMode[motorID] = false;
}
void setVoltageMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        setVoltageMode(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            setVoltageMode(i);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

void setCurrentMode(uint8_t motorID) {
    stepper[motorID].hardHiZ();
    stepper[motorID].setPredictiveControl(CONFIG_PRED_ENABLE);
    stepper[motorID].setSwitchingPeriod(5);
    if (stepper[motorID].getStepMode() > STEP_SEL_1_16)
    {
        stepper[motorID].configStepMode(STEP_SEL_1_16);
        microStepMode[motorID] = STEP_SEL_1_16;
    }
    stepper[motorID].setHoldTVAL(tvalHold[motorID]);
    stepper[motorID].setRunTVAL(tvalRun[motorID]);
    stepper[motorID].setAccTVAL(tvalAcc[motorID]);
    stepper[motorID].setDecTVAL(tvalDec[motorID]);
    stepper[motorID].setParam(T_FAST, fastDecaySetting[motorID]);
    stepper[motorID].setParam(TON_MIN, minOnTime[motorID]);
    stepper[motorID].setParam(TOFF_MIN, minOffTime[motorID]);
    stepper[motorID].setCurrentMode();
    isCurrentMode[motorID] = true;
}
void setCurrentMode(OSCMessage& msg, int addrOffset) {
    uint8_t motorID = getInt(msg, 0);
    if(isCorrectMotorId(motorID)) {
        motorID -= MOTOR_ID_FIRST;
        setCurrentMode(motorID);
    }
    else if (motorID == MOTOR_ID_ALL) {
        for (uint8_t i = 0; i < NUM_OF_MOTOR; i++) {
            setCurrentMode(i);
        }
    } else {
        sendMotorIdError(motorID);
    }
}

#pragma endregion PowerSTEP01_config_osc_listener

void sendErrorMsg(uint8_t motorID, uint8_t errorNum) {
    String errorText;
    switch (errorNum)
    {
    case OscSyntaxError:
        errorText = F("OscSyntaxError");
        break;
    case MessageNotMatch:
        errorText = F("MessageNotMatch");
        break;
    case WrongDataType:
        errorText = F("WrongDataType");
        break;
    case MotorIdNotMatch:
        errorText = F("MotorIdNotMatch");
        break;
    case OutOfRange:
        errorText = F("OutOfRange");
        break;
    default:
        break;
    }
    sendTwoData(F("/error/osc"), motorID, errorText);

}