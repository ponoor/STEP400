// utils.h

#ifndef _UTILS_h
#define _UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "globals.h"
#include <OSCMessage.h>
#include <Ethernet.h>

uint8_t getMyId();


void turnOnRXL();

void turnOnTXL();

void resetMotorDriver(uint8_t deviceID);

void sendOneInt(String address, int32_t data);

void sendTwoInt(String address, int32_t data1, int32_t data2);

void sendThreeInt(String address, int32_t data1, int32_t data2, int32_t data3);

void sendIdFloat(String address, int32_t id, float data);

void sendOneString(String address, const char* data);

template <class T>
T sendTwoData(String address, T data1, T data2);

#endif

