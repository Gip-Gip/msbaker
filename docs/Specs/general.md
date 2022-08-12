---
title: "General Specifications"
date: 2022-08-12
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
### The Need for a Compact Microcomputer in Rocketry

With modern advancements in chip design decreasing footprint and increasing computation power and effeciency, along with the shrinkage of many passive components, it is more than possible to cram fully capable flight computation units along with basic telemetry in a sub 10cm² package. The benefits for this are several, including but not limited to weight savings, dev time savings(not needing to design a custom computer for a project), cost savings, and improved calculations & accuracy. This improvements are of both a combination of modern technology and advanced board design which is all open sourced and openly developed to help lead to future improvements in the unexplored tech. On top of that, these improvements are all fairly substantial to hobby model rocketry as every little change especially counts at the small rocket scale.

**Weight savings** is the primary benefit of the Ms. Baker microcomputer. The second iteration of the microcomputer only weighed in at **4g** in total, which is only really comparible to basic barometer altimeters and blows any proper flight computer out of the water[1]. Less weight leads to a higher acceleration under the same force, and consequentially a higher apogee aswell [2]. These weight savings are very significant as they can result in a multi-percent decrease in the total mass of a common 100-300g rocket[3]. For example, you replace a 15g flight computer on an 100g rocket(with a gross weight of 115g) with Ms. Baker which comes in at 4g(a new gross weight of 104g), you get a weight reduction of 9.6%, which is not insubstantial by any means.

**Development time** is saved by making Ms. Baker versitile and GPIO-ready. Most model rocket altimeters and flight computers are either massive and expensive, or have little to no expandable GPIO[1]. Ms. Baker aims to fill a niche by providing **I2C GPIO** to the end user so they can implement pyro controls, flight controls, and etc. themselves without having to worry about developing the complex circuitry to support a **full 32-bit microcontroller**. This also allows for **easier and more robust programming** as even simple solutions can utilize a 32-bit ARM core to speed up and improve accuracy for any need that may be. Even larger projects can utilize Ms. Baker as the brains for their custom boards as it's small footprint allows for more space for power electronics and other chips & sensors that may be needed.

# Citations

 1. “Model Rocket Altimeters: Comparison Guide,” *Model rocket altimeters: Comparison guide*. \[Online\]. Available: [http://rocketsetc.com/altimeter-comparison/](http://rocketsetc.com/altimeter-comparison/). \[Accessed: 12-Aug-2022\].
 2. T. Benson, “Acceleration during powered flight,” *NASA*, 15-Aug-1999. \[Online\]. Available: [https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/rktapow.html](https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/rktapow.html). \[Accessed: 12-Aug-2022\].
 3. “HB:modelrockets,” *LUNAR*. \[Online\]. Available: [http://www.lunar.org/wiki/tiki-index.php?page=HB%3AModelRockets](http://www.lunar.org/wiki/tiki-index.php?page=HB%3AModelRockets). \[Accessed: 12-Aug-2022\].