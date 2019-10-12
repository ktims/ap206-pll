
# ap206-pll

This is a "modern" (ie. using available parts) replacement for the AP3601 PLL board found in the Akai AP-306 turntable. It can be added to an Akai AP-206 turntable to add Quartz Lock functionality.

## Design notes

The original Akai design used a 4.42368MHz crystal divided down by a flip-flop and programmable counter to 20Hz or 27Hz depending on selected speed. This is then compared with the conditioned feedback signal from the motor driver by PLL IC. See the Service Manual and schematic for more details.

This design uses an AVR ATtiny to divide down the clock in one step rather than using discrete logic. The programmable divider in the original design is no longer available, and a suitable replacement is not present in the 74xx or 4000 series of devices, and in addition the oddball crystal frequency is no longer available. Rather than using a bunch of extra logic, the ATtiny was used. The frequencies generated are 20Hz (33-1/3) and 27Hz (45) by dividing the 11.0592MHz clock by 552960 or 409600 using the PWM hardware. Likewise the PLL IC used is no longer available and was replaced with a 'modern' 4046. The circuit is otherwise basically identical to the original design.

**Note: 74xx variants *cannot* be used in any position. Original 4000 series CMOS variants must be used due to the 7.5V supply voltage and input signals from the motor.**

## Installation

It has been tested and works well, but installation requires some understanding of the design and will not be supported beyond the below notes. 

* Consult the (included) service manual to determine pin numbers on the DD PCB for where to attach to the new PCB
* Some existing connections must be broken and replaced with the new circuits. Most significantly, the AP-206 has two speed pots, while the AP-306 has one. You must disconnect one of them and rewire per the AP-306 (see the wiring diagram on p. 22 of the service manual which shows both models). Note that SW903 which was a discrete switch on the AP-306 is on the PCB here, so those connections go to the PCB as below.

### Connections
 
 ap206-pll label | connection 
 --------------- | ---------- 
 7.5Vin          | DD Board Pin 20
 GNDin           | DD Board Pin 21
 FGin            | DD Board Pin 16
 SW-1            | Speed Switch 33 position (unused side)
 SW-COM          | Speed Switch Common (unused side)
 SW-2            | Speed Switch 45 position (unused side)
| | |
 13              | DD Board Pin 13
 12              | DD Board Pin 12
 SVR             | Common of the 'speed' pot (keep only one)
 SSW             | Common of the speed switch (prepopulated side)
 19              | DD Board Pin 19

## Adjustment
You will need to adjust the two speed pots on the DD board (VR2, VR3) for a reasonably close speed after installation, or the PLL will not be able to lock. Once speeds are adjusted correctly, adjust RV1 until lock is achieved. No lock indicator is included, but should be obvious. For verification, pins 3 & 14 of U7 can be scoped; they should be stable in relative phase when lock is achieved.
