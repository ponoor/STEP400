# STEP400

![STEP400](https://ponoor.com/cms/wp-content/uploads/2021/03/step400-product-version-edited.png)

STEP400 is a 4-axis stepper motor driver board with an Ethernet interface, designed for art installations, stage productions and exhibition machinery. It puts everything a typical motion setup needs onto one board:

- An Arduino Zero–compatible MCU (Microchip ATSAMD21G18A)
- Ethernet (WIZnet W5500)
- Four [STMicroelectronics powerSTEP01](https://www.st.com/en/motor-drivers/powerstep01.html) stepper drivers, supporting both voltage mode and current mode
- HOME and LIMIT sensor inputs for each axis
- A microSD card slot for loading the configuration file

The board is controlled with [Open Sound Control](https://opensoundcontrol.stanford.edu/) (OSC) over Ethernet, which works natively in Max, TouchDesigner, Processing, openFrameworks, Unity and other creative coding environments.

| | |
|---|---|
| Motor type | Bipolar stepper |
| Supply voltage | 12–72 V (absolute max. 80 V) |
| Max. phase current | 5 A |
| Microstepping | Up to 1/128 |
| PCB size | 120 × 84 mm |

STEP400 is part of the STEP series. Its sibling, [STEP800](https://github.com/ponoor/STEP800), drives eight smaller motors with L6470 drivers and shares the same firmware and OSC commands.

Friend of STEP400 : [STEP800](https://github.com/ponoor/STEP800)

## Store
https://ponoor.com/en/shop/

## Documentation
https://ponoor.com/en/docs/step-series/

Forum: https://github.com/ponoor/step-series-support/discussions

- **[STEP400/STEP800 documentation](https://ponoor.com/en/docs/step-series/)** ([日本語](https://ponoor.com/docs/step-series/))
  - [Tutorial](https://ponoor.com/en/docs/step-series/tutorial/)
  - [OSC command reference](https://ponoor.com/en/docs/step-series/osc-command-reference/)
  - [Hardware details](https://ponoor.com/en/docs/step-series/technical-information/hardware-step400/)
- [Electromagnetic brake board for STEP400](https://ponoor.com/en/docs/emb-step400/)
- Questions and support: [STEP series support forum](https://github.com/ponoor/step-series-support/discussions)

## Firmware

The firmware is maintained in a separate repository, shared with STEP800:

**[ponoor/step-series-universal-firmware](https://github.com/ponoor/step-series-universal-firmware)**

This repository used to contain the STEP400 firmware as well. Those directories have been removed, and the old releases here are no longer maintained. See [Firmware update](https://ponoor.com/en/docs/step-series/technical-information/firmware-update/) in the documentation for how to update a board.

## Repository contents

### `hardware/`

Design files for the current hardware revision (r1).

| File | Description |
|---|---|
| `step400_r1.sch`, `step400_r1.brd` | STEP400 r1 schematic and board (Autodesk EAGLE). These are the reference design files for r1. |
| `step400_r1_schematics.pdf` | STEP400 r1 schematic |
| `step400_r1_dimension.pdf` | Board dimensions and mounting holes |
| `step400_r1.0.1_BOM.csv` | Bill of materials for r1.0.1 (current) |
| `step400_r1.0.0_BOM.csv` | Bill of materials for r1.0.0 |
| `brakeBoard.sch`, `brakeBoard.brd` | Electromagnetic brake board (Autodesk EAGLE) |
| `brakeBoard_schematic.pdf`, `brakeBoard_BOM.csv` | Brake board schematic and bill of materials |
| `step400_r1/` | KiCad project imported from the EAGLE r1 files (see below) |

#### KiCad migration (work in progress)

We are moving the hardware design from EAGLE to KiCad for the next revision. `hardware/step400_r1/` holds the r1 design imported into KiCad 10, along with a footprint library (`step400_r1.pretty`) exported from the board.

The connectivity and footprints of this KiCad project have been checked against the EAGLE files. However, it is kept as a **reference for future work**, not as manufacturing data. The PCB still carries leftovers from the import (an unconsolidated layer stack, missing keepout areas, default design rules), so use the EAGLE files or the PDFs above if you need the exact r1 design.

### `configTool/`

Source of the web-based configuration tool, which creates the JSON configuration file that the board loads from its microSD card. A hosted version is available at [ponoor.com/tools/step400-config/](https://ponoor.com/tools/step400-config/). For usage, see [Setup with a microSD card](https://ponoor.com/en/docs/step-series/settings/setup-with-a-microsd-card/).

### `step400_hardware_tests/`

A PlatformIO project for the hardware inspection firmware, used to test assembled boards.

## Examples and libraries

| Environment | Repository |
|---|---|
| Max | [ponoor/step-series-example-Max](https://github.com/ponoor/step-series-example-Max) |
| TouchDesigner | [ponoor/step-series-example-TouchDesigner](https://github.com/ponoor/step-series-example-TouchDesigner) (by [@loveandsheep](https://github.com/loveandsheep)) |
| openFrameworks | [ponoor/step-series-example-openFrameworks](https://github.com/ponoor/step-series-example-openFrameworks) (by [@niimi](https://github.com/niimi)) |
| Unity | [ponoor/step-series-example-Unity](https://github.com/ponoor/step-series-example-Unity) (by [@niimi](https://github.com/niimi)) |
| Processing | [yuskegoto/STEP400_Processing](https://github.com/yuskegoto/STEP400_Processing) (by [@yuskegoto](https://github.com/yuskegoto)) |
| Node-RED | [yuskegoto/STEP400_Node-RED](https://github.com/yuskegoto/STEP400_Node-RED) (by [@yuskegoto](https://github.com/yuskegoto)) |
| Python | [ponoor/python-step-series](https://github.com/ponoor/python-step-series) |

## License

[MIT License](LICENSE) © Ponoor Experiments Inc.
