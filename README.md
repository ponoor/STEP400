## STEP400
![STEP400](https://ponoor.com/cms/wp-content/uploads/2021/03/step400-product-version-edited.png)

STEP400 is a 4-axis stepper motor driver designed for art or design projects. STEP400 combines the following elements into one single board:

- [Arduino Zero](https://www.arduino.cc/en/Guide/ArduinoZero)
- Ethernet shield
- Four stepper motor drivers
- Sensor inputs for homing and limiting

The current firmware is focused on working with [Open Sound Control](http://opensoundcontrol.org/) (OSC) via Ethernet, which is a common protocol for creative coding environments, like openFrameworks, Processing, Max, Unity, or Touch Designer.

Stepper driver chips are STMicroelectronics's [powerSTEP01](https://www.st.com/en/motor-drivers/powerstep01.html) which provide most of functionalities as a stepper driver.

## Documentation
https://ponoor.com/en/docs/step400/

## Repository Contents
### Firmware
These 2 folders contain same codes.
- [/STEP400_firmware](https://github.com/ponoor/STEP400/tree/master/STEP400_firmware) : Arduino Sketch folder
- [/firmware-platformio/STEP400_firmware](https://github.com/ponoor/STEP400/tree/master/firmware-platformio/STEP400_firmware) : PlatformIO folder

Note: We are working on the "[Universal Firmware](https://github.com/ponoor/step-series-universal-firmware)" which covers all STEP series board. A development of each firmware (above) will be terminated soon.

### Hardware
[/hardware](https://github.com/ponoor/STEP400/tree/master/hardware) : Eagle design files, BOM lists, and schematics PDFs

### Others
[/configTool](https://github.com/ponoor/STEP400/tree/master/configTool) : The configuration tool consists of a html and JavaScritpts.

## Firmware dependency
- **[OSC Library](https://github.com/CNMAT/OSC)** from CNMAT
- **[Ponoor PowerSTEP01 Library](https://github.com/ponoor/Ponoor_PowerSTEP01_Library)**
- **[ArduinoJSON Library](https://arduinojson.org/)**
- **[Adafruit SleepyDog Arduino Library](https://github.com/adafruit/Adafruit_SleepyDog)**

## Examples
### Max
https://github.com/kanta/STEP400_prototype/blob/master/rev4/STEP400_proto_r4.maxpat

### Processing
https://github.com/yuskegoto/STEP400_Processing

Contribution of [@yuskegoto](https://github.com/yuskegoto)

### openFrameworks
https://github.com/ponoor/step-series-example-openFrameworks

Contribution of [@niimi](https://github.com/niimi)

### Unity
https://github.com/ponoor/step-series-example-Unity

Contribution of [@niimi](https://github.com/niimi)

### Touch Designer
https://github.com/ponoor/step-series-example-TouchDesigner

Contribution of [@loveandsheep](https://github.com/loveandsheep)


