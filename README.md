# Ms. Baker

**Authored and Developed by Charles "Gip-Gip" Thompson**

## A General-Purpose Bluetooth Telemetry Board

*Current Revision:* **2.3.1**

*Current Revision Status:* **Testing**

*Website:* **[https://gip-gip.github.io/msbaker/](https://gip-gip.github.io/msbaker/)**

## What is Ms Baker?

Ms. Baker is a small-form-factor accelerometer/gyro logging board that utilizes BTLE to upload and download data wirelessly. Being based off of the ESP-32 chip it has
plenty of computational power, and enough GPIO for any sort of project you have in mind.

The board is named after the space pioneer Miss Baker, one of the first monkeys to go to space and safely return

## Goal

Ms. Baker is being designed to provide a robust, rocket-grade ESP32 platform complete with compact GPIO and full programmability. Being open source in every aspect,
Ms. Baker is intended to be used in an array of rocketry projects from simple small apogee logging to fully fledged multi-staged LPR

## Features

 * Fully programmable 32-bit ESP32 MCU with 4MB onboard flash
 * Small form factor board designed to fit within a rocket as small as an Estes Gnome
 * 10 GPIO pins free for use in other projects
 * +-32g accelerometer and +-4000 °/sec gyroscope
 * 8 kB FeRAM for quick nonvolitile storage incase of battery disconnect
 * Designed to utilize BTLE for short-range wireless communication, be it for arming, data download or etc.
 * Powered by a 3.7v LiPo battery
 * Completely Open Source, including the hardware!

## To-Dos

 * Tune bluetooth antenna
 * Program ROM
 * Program app
 * Create PCB edge programming adapter

## Directory Layout

 * docs -  Documents pretaining to Ms. Baker, such as renders, specifications, checklists, and BOMs
 * mbaker - Ms. Baker KiCad projec
 * rom - ROM Eclipse(C/C++) project
   * bin - flashable binaries
   * include - header files
   * obj -  pre-linker object files
   * src - C source files

## Contributing

Contact me at the email chmithbiz@gmail.com and see what I need help with, or alternatively if you're more of an introvert just comb through the repository and see
what can be done/what you want to see. If you contribute I will add you to the "Authored and Developed by..." section and you will recieve my unending gratitude.

## Legal

Every file in this repository, unless stated otherwise, is under the BSD 3-Clause License. See LICENSE for more details
