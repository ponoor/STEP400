# Diagram
```mermaid
flowchart LR
	MCU ---|SPI/SERCOM4| W5500 --- Ethernet
	MCU --- |SPI/SERCOM3|PowerSTEP01 --> Motor
	HomeSw -->|SW| PowerSTEP01
	LimitSw -->|ADCIN| PowerSTEP01
	DIPSW --> MCU
	MCU --> Brake
  ```
  
  Check the [document](https://ponoor.com/en/docs/step-series/technical-information/hardware-step400/) for details.
  
