// diagnosis.h

#ifndef _DIAGNOSIS_h
#define _DIAGNOSIS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "globals.h"
#include "loadConfig.h"

void diagnosisCommand(uint8_t inByte);
void printMenu();
void testMotion();
void printCurrentState();
void printConfigulations();
void printTitle(String title);
void showBoolResult(String title, bool val);
template <class T>
T print4data(String title, T* val);

void show4Bool(String title, bool* val);
void showIpAddress(String title, IPAddress ip);
void boldHeader(String header);
void printHeader(String header);

#endif

