**Ms. Baker is a compact microcomputer built off the RP2040, specifically with model rocketry in mind.**
Occupying a footprint under 10cm&sup2;, this computer provides a unique density of many useful components, including a compact **25 pin GPIO** connector and a high accuracy **IMU**.
These features in a compact and light package is especially useful for low and medium power rockets, but may also find use in other applications where an ultra-small microcomputer may be needed.

## Feature Set

Ms. Baker is fairly feature packed for the size, and includes:

### RP2040 MCU

Powered by Raspberry Pi's RP2040 Microcontroller, Ms. Baker has the computation power of a 133MHz dual-core Arm Corted-M0+ processor in an unbelievably compact package.

### Micro SD Card Slot

Useful for logging data and loading/storing programs, Ms. Baker comes equipped with a compact MicroSD card slot for easy-to-use data storage.

### I2C IMU

No rocket computer should be complete with at least some form of telemetry, and Ms. Baker comes with the versitile LSM6DSO32 IMU, providing both gyro and acceleration data at a sample rate of up to 6.7kHz.
It has a maximum measurable acceleration range of &plusmn;32*g* and a maximum measurable angular rate of &plusmn;200dps, which should be good for most low and medium powered rockets, in theory.

### USB Programmable ROM

Thanks to the RP2040 Ms. Baker is entirely programmable via USB, meaning so long as you have a Micro USB cable and a computer you have access to **16MBytes of ROM** with no extra hardware!

### GPIO

Utilizing a Molex SlimStack connector Ms. Baker provides 25 pins of GPIO in a very compact footprint, completely up for any use the end user may desire!

### Robust Firmware

Like any other OpenApeShop project, Ms Baker's firmware is *(to be written)* in the Rust programming language, making it very robust and resistant to common bugs that may occur in other embedded firmware solutions.

## Development Status

**Currently Awaiting Parts**, Ms. Baker is on it's third prototype and has the following steps that need to be completed before it is more or less ready for use:

- [ ] Assemble a working prototype
- [ ] Program the firmware so that by default Ms. Baker acts as a telemetry logging device
- [ ] Field test Ms. Baker on a live rocket
- [ ] Reorganize PCB to fill up any unused space by
    - [ ] Spacing traces to reduce the chances of crosstalk, when possible
    - [ ] Increasing the size of traces to reduce impedence, when possible
- [ ] Document Ms. Baker so it's easy to use
- [ ] Develop a pin breakout board so prototyping is as easy as with a normal Raspberry Pi Pico

## Links

* [Website](https://openapeshop.org/hardware/msbaker)
* [Schematic](https://github.com/Gip-Gip/msbaker/raw/main/docs/Renders/schematic.png)
