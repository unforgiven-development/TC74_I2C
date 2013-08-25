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

#ifndef TC74_I2C_h
#define TC74_I2C_h

#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>

// Commands
#define SELECT_CONFIG_REGISTER		0x01
#define SELECT_TEMPERATURE_REGISTER	0x00
#define POWERSAVE 			0x80
#define NOPOWERSAVE 			0x00
#define NEGATIVE			0x80

// Address constants
#define TC74_A0	0x48
#define TC74_A1	0x49
#define TC74_A2	0x4A
#define TC74_A3	0x4B
#define TC74_A4	0x4C
#define TC74_A5	0x4D // This is the default address
#define TC74_A6	0x4E
#define TC74_A7	0x4F
 
class TC74_I2C {
	
public:
  TC74_I2C(int TC74_Addr);

  void Init();
  int  ReadTemp();
  void Powersave();
  void NoPowersave();
  int  Powersavestatus();
  

private:
  void Init_priv();
  int _Addr;
};

#endif
