---
title: "General Specifications"
date: 2022-08-19
author:
    - Charles Thompson
tags:
    - Specifications
    - General
    - Overview
    - Hardware
    - Software
---
# General Specifications of the Ms. Baker Microcomputer
## The Need for a Compact Microcomputer in Rocketry

With modern advancements in chip design decreasing footprint and increasing computation power and effeciency, along with the shrinkage of many passive components, it is more than possible to cram fully capable flight computation units along with basic telemetry in a sub 10cm² package. The benefits for this are several, including but not limited to weight savings, dev time savings(not needing to design a custom computer for a project), and cost savings. This improvements are of both a combination of modern technology and advanced board design which is all open sourced and openly developed to help lead to future improvements in the unexplored tech. On top of that, these improvements are all fairly substantial to hobby model rocketry as every little change especially counts at the small rocket scale.

**Weight savings** is the primary benefit of the Ms. Baker microcomputer. The second iteration of the microcomputer only weighed in at **4g** in total, which is only really comparible to basic barometer altimeters and blows any proper flight computer out of the water[1]. Less weight leads to a higher acceleration under the same force, and consequentially a higher apogee aswell [2]. These weight savings are very significant as they can result in a multi-percent decrease in the total mass of a common 100-300g rocket[3]. For example, you replace a 15g flight computer on an 100g rocket(with a gross weight of 115g) with Ms. Baker which comes in at 4g(a new gross weight of 104g), you get a weight reduction of 9.6%, which is not insubstantial by any means.

**Development time** is saved by making Ms. Baker versitile and GPIO-ready. Most model rocket altimeters and flight computers are either massive and expensive, or have little to no expandable GPIO[1]. Ms. Baker aims to fill a niche by providing **I2C GPIO** to the end user so they can implement pyro controls, flight controls, and etc. themselves without having to worry about developing the complex circuitry to support a **full 32-bit microcontroller**. This also allows for **easier and more robust programming** as even simple solutions can utilize a 32-bit ARM core to speed up and improve accuracy for any need that may be. Even larger projects can utilize Ms. Baker as the brains for their custom boards as it's small footprint allows for more space for power electronics and other chips & sensors that may be needed.

**Cost Savings** *todo*

## What is Required for Ms. Baker to Meet It's Goals?

Ms. Baker has a lot of things it needs to fullfill, and each requirement brings it twords the goal of it being a fully fledged microcomputer

 * A **RP2004** MCU at the heart of the project. The RP2040 is low cost and OSH-friendly, with an open-source bootROM and good support for Rust
 * Firmware programmed in **Rust**. Rust is a powerful language that enforces good programming habits and allows the firmware to be far more robust by nature than if it were built in another language such as C or C++
 * On-board **accelerometer** and **gyroscope**, ideally in the same chip as this allows Ms. Baker to keep approximate relative location of the microcomputer
 * **10 meter** apogee accuracy when measuring apogee, under 10000 meters
 * Robust **GPIO** connectors and/or headers for expanding the use of the computer into other projects, with a minimum of one **I2C** interface
 * **USB** interface for extracting data from previous flights *and* programming the computer
 * **4MB** flash storage for plenty of room to program
 * **F-RAM** for storing non-volitile flight telemetry data
 * Total area under **10cm²**, and ideally small enough to fit into an estes gnome

## Finding Telemetric Accuracy
### Calculating Distance from Rocket Acceleration

First you need to find the initial hypothetical apogee from a hypothetical rocket's acceleration. Let's say the rocket accelerates at around 16g for 1 second, the rocket would gain $s_1$ distance and $v_1$ velocity by the time the rocket looses power
  $$
  \begin{aligned}
  &v = u + at\\
  &v = 0 + 156.9_{m/s^2}\cdot1_s\\
  \\
  &v_1 = 156.9_{m/s}
  \end{aligned}
 $$
$$
\begin{aligned}
\\
&v^2=u^2+2as\\
&2as=v^2-u^2\\
&s_1=\frac{v_1^2-u^2}{2a}\\
\\
&s_1=\frac{156.9_{m/s}^2-0_{m/s}^2}{2\cdot156.9_{m/s^2}}
\\
&s_1=78.5_m
\end{aligned}
$$
Then from there you can find the distance($s_2$) it takes the rocket to reach it's apogee
$$
\begin{aligned}
&u_2=v_1\\
\\
&s_2=\frac{v_2^2-u_2^2}{2a_2}\\
\\
&s_2=\frac{0_{m/s}^2-156.9_{m/s}^2}{2\cdot-9.8_{m/s^2}}
\\
&s_2=1256_m
\end{aligned}
$$
After that, you can find the total distance($s_t$) by adding $s_1$ and $s_2$, in this case $s_t=s_1+s_2=1334.5_m$. To condense the steps needed to get $s_t$, we can simply concatinate the above math into one equation
$$
\begin{aligned}
&s_t = s_1 + s_2\\
&s_t = \frac{v_1^2}{2a}+\frac{-v_1^2}{2\cdot-9.8_{m/s^2}}\\
\\
&s_t = \frac{(at)^2}{2a}+\frac{(at)^2}{19.6_{m/s^2}}
\end{aligned}
$$

## Part Selection

 * MPU: **RP2040**
     * Open-Source boot rom
     * Flash-able without any extra hardware via USB
     * Micro-SD card support
     * 2 i2c interfaces, 2spi interfaces
     * Up to 16mb external programmable flash
 * IMU: **LSM6DSO32TR**
     * 
 * Flash: **W25Q128JVSIM TR**
     * Reccomended flash for the RP2040
     * 16mb fast program storage
 * Voltage Regulator: **MIC5365-3.3YC5-TR**
 * Micro-USB port: **105017-0001**
 * MicroSD card connector: **104031-0811**
 * GPIO connector: **5055513420**
 * Crystal: **445I23D12M00000**

# Citations

 1. “Model Rocket Altimeters: Comparison Guide,” *Model rocket altimeters: Comparison guide*. \[Online\]. Available: [http://rocketsetc.com/altimeter-comparison/](http://rocketsetc.com/altimeter-comparison/). \[Accessed: 12-Aug-2022\].
 2. T. Benson, “Acceleration during powered flight,” *NASA*, 15-Aug-1999. \[Online\]. Available: [https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/rktapow.html](https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/rktapow.html). \[Accessed: 12-Aug-2022\].
 3. “HB:modelrockets,” *LUNAR*. \[Online\]. Available: [http://www.lunar.org/wiki/tiki-index.php?page=HB%3AModelRockets](http://www.lunar.org/wiki/tiki-index.php?page=HB%3AModelRockets). \[Accessed: 12-Aug-2022\].