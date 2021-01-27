// loadConfig.h

#ifndef _LOADCONFIG_h
#define _LOADCONFIG_h
#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "globals.h"

void loadConfig();


#endif

