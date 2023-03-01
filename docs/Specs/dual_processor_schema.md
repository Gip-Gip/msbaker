---
title: "Dual Processor Schema"
date: 2023-03-01
author:
    - Charles Thompson
tags:
    - Specifications
    - Software
---
In embedded systems it is important that everything run efficiently as possible, and since the RP2040 is a dual core processor it would be a waste to not utilize both cores to their full potential. Therefore it is important to outline what responsibilities each core does so that programming for the processor is straightforward and well defined.

## Processor Responsibilities
Ms. Baker is to use a In-Out dual processor schema, in that one processor gathers input data and the other writes output data. The individual responsibilities are as follows:

### Core 0(In):
1. Initialize everything
2. Keep track of time
3. Read sensors on a consistent basis(be on time)
4. Handle aborts
5. Send data to core 0 to be processed, with high and low priority

### Core 1(Out):
1. Perform tasks assigned by core 0, high priority first, pertaining to
    * Computing and storing telemetry of the computer
    * Adjusting flight path and moving actuators when hooked up to external gear
    * Writing telemetry to the SD card