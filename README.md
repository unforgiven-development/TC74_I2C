# TC74_I2C - An Arduino library for the TC74 temperature sensor #

This library is intended to provide a simple interface to the [Microchip][1a] [TC74][1b] temperature sensor.

The [TC74][1b] is a simple device, availlable in a 5-pin **TO-220** package, and communicates with the host via the I²C
serial interface.


## Library Features ##

The core features _(obviously)_ include the ability to read the temperature of the device.

In addition to this, the [TC74][1b] supports a _standby mode_, in which the **A/D converter** is halted, and the various
data registers are _"frozen"_, reducing the current consumption of the device from **200 μA** to just **5 μA** -- which
is a _relatively_ significant power savings.





[1a]:	<https://www.microchip.com>
[1b]:	<https://www.microchip.com/wwwproducts/en/TC74>
