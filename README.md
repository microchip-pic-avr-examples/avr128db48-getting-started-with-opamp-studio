<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Getting Started with Analog Signal Conditioning OPAMP on AVR DB

The Analog Signal Conditioning (OPAMP) peripheral features up to three internal operational amplifiers (op amps). The op amps can be configured to a multitude of different operations using internal multiplexers and resistor laders  

The main purpose of op amps is to condition the analog signals before acquisition in a microcontroller or to provide the necessary output drive in control applications

These examples show the following configurations of the OPAMP peripheral on the AVR DB family of microcontrollers:

* **Simple Op Amp:** 
OP0 is connected directly to the pins
* **Voltage Follower:** 
OP0 is configured as an voltage follower
* **Non-Inverting PGA:** 
OP0 is configured as a non-inverting PGA
* **Differential Amplifier:** 
OP0 and OP1 are combined to create a differential amplifier 
* **Instrumentation Amplifier:** 
OP0, OP1 and OP2 are combined to create an instrumentation amplifier


## Related Documentation

* [TB3272 - Getting Started with External High-Frequency Oscillator on AVR DB](https://microchip.com/DSxxxxxxxxxx) <!-- TODO: Update link once assigned -->
* [AVR128DB48 Curiosity Nano User Guide](https://microchip.com/DSxxxxxxxxxx) <!-- TODO: Update link once assigned -->
* [AVR128DB48 Device Page](https://www.microchip.com/wwwproducts/en/AVR128DB48)


## Software Used

* [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7) 7.0.2397 or later
* Atmel Studio AVR-Dx_DFP version 1.2.56 or later

## Hardware Used

* [AVR128DB48 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV35L43A)

## Setup

All examples can be completed using the AVR128DB48 Curiosity Nano without any extra components

## Operation

* Connect the AVR128DB48 Curiosity Nano to a computer using a USB cable
* Clone the repository or download the zip to get the source code
* Open the .atsln file with Atmel Studio
* In Solution Explorer, right-click the project you want to run and select *Set as StartUp Project*
* Press *Start Without Debugging* (CTRL+ALT+F5) to run the example


## Summary

After going through these examples you should have a better understanding of how to configure the the OPAMP peripheral to achieve different modes of operation.   
