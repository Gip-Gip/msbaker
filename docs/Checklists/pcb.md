---
title: "PCB Checklist"
date: 2022-08-26
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
     - [ ] Decoupling capacitors close to pins
 - [ ] Crystal Oscillator
     - [ ] Close to RP2040 to reduce parasitic capacitance
     - [ ] Capacitors and resistor close to crystal
 - [ ] Flash
     - [ ] Data lines short and close to the RP2040
 - [ ] I/O
     - [ ] USB
         - [ ] 0.8mm wide tracks spaced 0.15mm apart from R5 and R6

# LSM6DSO32 Checklist
### Derived from [iNEMO inertial module: always-on 3D Accelerometer and 3D gyroscope](https://www.st.com/resource/en/datasheet/lsm6dso32.pdf)
 - [ ] Power
     - [ ] Decoupling capacitors close to pins

# W25Q128JVSIM Checklist
### Derived from the W25Q128JV [Datasheet](https://www.winbond.com/hq/support/documentation/downloadV2022.jsp?__locale=en&xmlPath=/support/resources/.content/item/DA00-W25Q128JV.html&level=1) and [Hardware design with RP2040](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf)
 - [ ] Power
     - [ ] Decoupling capacitors close to pins

# MIC5365-3.3YC5 Checklist
### Derived from the MIC5465 [Datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/mic5365.pdf)
 - [ ] Power
     - [ ] Decoupling capacitors close to pins

# Final Checklist
 - [ ] RP2040 Checklist Complete
 - [ ] LSM6DSO32 Checklist Complete
 - [ ] W25Q128JVSIM Checklist Complete
 - [ ] MIC5365-3.3YC5 Checklist Complete
 - [ ] No unconnected pins or nets
 - [ ] DRC ran