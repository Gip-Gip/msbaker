---
title: "Schematic Checklist"
date: 2022-08-19
author:
    - Charles Thompson
tags:
    - Checklist
    - General
    - Hardware
---
# RP2040 Checklist
### Derived from [Hardware design with RP2040](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf) and the RP2040 [Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
 - [ ] Power
     - [ ] 3.3v LDO Voltage Regulator
     - [ ] Decoupling capacitors
         - [ ] 100n capacitors on pins 49, 42, 33, 22, 10, 1, 48 and 43
         - [ ] 100n capacitors on pins 50 and 23
         - [ ] 1u capacitors on pins 45 and 44
 - [ ] Flash Storage
     - [ ] Boot select header connected to QSPI_SS
         - [ ] 1k resistor between header and QSPI_SS
     - [ ] W25Q128JVS flash chip
 - [ ] Crystal Oscillator
     - [ ] 33p capacitor connected to each pin on the crystal
     - [ ] 1k resister in series between the crystal and XOUT
     - [ ] Crystal with ESR of 50ohms and 18p load capacitance
 - [ ] I/O
     - [ ] USB
         - [ ] 27.4ohm resistor in series with USB_D+ and USB_D-
     - [ ] GPIO
         - [ ] All GPIO pins availible to the GPIO header, excluding GPIOs used for the SD card
         - [ ] Run, SWD, and SWCLK also availible to the GPIO header
     - [ ] I2C
         - [ ] Pullup resistors correct value
         - [ ] All ICs connected to I2C0 on pins 8 and 9
     - [ ] SD Card
         - [ ] 10u decoupling capacitor between VDD and ground
         - [ ] All data lines contiguous and in order
     - [ ] Green Status LED
         - [ ] 120 ohm current limiting resistor

# LSM6DSO32 Checklist
### Derived from [iNEMO inertial module: always-on 3D Accelerometer and 3D gyroscope](https://www.st.com/resource/en/datasheet/lsm6dso32.pdf)
 - [ ] Power
     - [ ] 3.3v supply connected to pins 8 and 5
     - [ ] 100n capacitors connected to pins 8 and 5
 - [ ] I2C
     - [ ] SA0(pin 1) connected to ground to set the I2C lsbit to zero
     - [ ] SDx and SCx connected to ground
     - [ ] INT1 not connected
     - [ ] INT2 not connected
     - [ ] CS connected to 3.3v
     - [ ] SCL connected to I2C0_SCL
     - [ ] SDA connected to I2C0_SDA

# W25Q128JVSIM Checklist
### Derived from the W25Q128JV [Datasheet](https://www.winbond.com/hq/support/documentation/downloadV2022.jsp?__locale=en&xmlPath=/support/resources/.content/item/DA00-W25Q128JV.html&level=1) and [Hardware design with RP2040](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf)
 - [ ] Power
     - [ ] 3.3v supply connected to pin 8
     - [ ] 100n capacitor connected to pin 8

# MIC5365-3.3YC5 Checklist
### Derived from the MIC5465 [Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/mic5365.pdf)
 - [ ] Power
     - [ ] 1u capacitor connected to both pins 1 and 5
     - [ ] VIN connected to +5v rail
     - [ ] VOUT connected to +3.3v rail
 - [ ] EN pin connected to +5v

# Final Checklist
 - [ ] RP2040 Checklist Complete
 - [ ] LSM6DSO32 Checklist Complete
 - [ ] W25Q128JVSIM Checklist Complete
 - [ ] MIC5365-3.3YC5 Checklist Complete
 - [ ] No unconnected pins
 - [ ] Schematic organized
 - [ ] BOM generated
 - [ ] Footprints set
 - [ ] MPNs set