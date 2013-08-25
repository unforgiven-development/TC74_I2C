/*
SerialTemp.ino

Example for Microchip TC74 temperature sensor using the TC74_I2C library

The sketch reads the TC74 sensor via I2C at a 2 second interval and outputs the data to the serial port
See the info directory for more information

Created May 2011
By Mario H		https://github.com/Mario-H/TC74_I2C
*/


#include <Wire.h> 
#include <TC74_I2C.h>

TC74_I2C TC74(TC74_A5);  			// set the TC74 address to TC74_A5 (= 0x4D defined in TC74_I2C.h)

int temperature;                                // Define variable to hold the temperature

byte usepowersave = 0;                          // set to 1 to use powersave during the delay at the end of the loop
                                                // In powersave mode the TC74 draws a current of 5 µA instead of 200 µA when in normal mode


void setup(){
   Serial.begin(9600);				// Initialize the serial port
   TC74.Init();					// Initialize the TC74 sensor in normal mode
 }


void loop(){

  if(usepowersave){
    TC74.NoPowersave();                         // Make sure the sensor is not in powersave mode
  }
  
  temperature = TC74.ReadTemp();                // Get temperature from sensor

  Serial.print ("Temperature= ");	
  if(temperature != 128){                       // default the library returns a temperature of 128 degrees
                                                // Since the max temperature the TC74 can measure is 127 degrees this way 
                                                // we can check if we got valid data from the sensor
    Serial.println(temperature);                // Write temperature to serial port
  }else{                                        // We received an invalid reading of 128 degrees indicating an error
    Serial.println("No data received");         // Write Error message to output
  }

  if(usepowersave){
    TC74.Powersave();                           // If configured: put the sensor in powersave mode
  }	
    
  delay(2000);					// Wait 2 seconds
}