/*
  TC74_I2C.h - I2C library for TC74 temperature sensor for Arduino IDE V1.0
  
  See the info directory for more information

  Created May 2011
  By Mario H	  https://github.com/Mario-H/TC74_I2C 


  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "TC74_I2C.h"
#include <inttypes.h>
//#include "WProgram.h" 
#include "Arduino.h"	// only support for arduino IDE >= 100

#include "Wire.h"

TC74_I2C::TC74_I2C(int TC74_Addr)
{
  _Addr = TC74_Addr;
}

void TC74_I2C::Init(){
	Init_priv();
}

void TC74_I2C::Init_priv()
{
	Wire.begin();
	NoPowersave();
}

void TC74_I2C::Powersave(){
	Wire.beginTransmission(_Addr);
	Wire.write((int) SELECT_CONFIG_REGISTER);
	Wire.write((int) POWERSAVE);
	Wire.endTransmission();   
}

void TC74_I2C::NoPowersave(){
	Wire.beginTransmission(_Addr);
	Wire.write((int) SELECT_CONFIG_REGISTER);
	Wire.write((int) NOPOWERSAVE);
	Wire.endTransmission();    
	delay(250);						// Maximum ensured conversion time after Power-on Reset (POR to DATA_RDY) is 250 msec.
}

int TC74_I2C::Powersavestatus(){
	uint8_t rdata = 0xFF;					// The powersave function should return 0 for normal mode or 1 for powersave mode.
								// When there is a problem reading the status the function will return 0xFF
	Wire.beginTransmission(_Addr);
	Wire.write((int) SELECT_CONFIG_REGISTER);
	Wire.endTransmission();    

	Wire.requestFrom(_Addr, 1);
  	if (Wire.available()) rdata = Wire.read();
  	return rdata;
}

int TC74_I2C::ReadTemp(){
	int rdata = 128;					// The sensor can measure a maximum temperature of +127 degrees.
								// When there is a problem reading the temperature the function will return 128
								// this can be used in the sketch to detect invalid readings
	Wire.beginTransmission(_Addr);
	Wire.write((int) SELECT_TEMPERATURE_REGISTER);
	Wire.endTransmission();    

	Wire.requestFrom(_Addr, 1);
  	if (Wire.available()){
  		rdata = Wire.read();
		if(rdata & NEGATIVE){				// Negative temperatures have bit 7 set, and range from -1 to -65 deg Celcius , see datasheet page 8 table 4.4
			rdata = -1*((rdata ^ 0xFF )+1);		// Convert back from two's complement and multiply by -1 to make it negative again
		}
  		return rdata;
	}else{
  		return 128;
	}
  	
}

