// loadConfig.h

#ifndef _LOADCONFIG_h
#define _LOADCONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void loadConfig();


#endif

