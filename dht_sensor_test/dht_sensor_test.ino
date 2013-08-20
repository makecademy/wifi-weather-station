/* 
*  Test for the DHT11 sensor
*  Part of the code is based on the work done by Adafruit for the DHT11 sensor
*  Writtent by Marco Schwartz for Open Home Automation
*/

// Include required libraries
#include <SPI.h>
#include <string.h>
#include "DHT.h"
#include<stdlib.h>

// DHT11 sensor pins
#define DHTPIN 7 
#define DHTTYPE DHT11

// DHT instance
DHT dht(DHTPIN, DHTTYPE);
char buffer[5];
                                         
void setup(void)
{
 
  // Initialize DHT sensor
  dht.begin();
  
  Serial.begin(115200);
  
}
  
void loop(void)
{
  
    // Measure the humidity & temperature
    float h = dht.readHumidity();
    float t = dht.readTemperature();
   
    // Transform to String
    String temp = floatToString(t);
    String hum = floatToString(h);
    
    Serial.println(temp);
    Serial.println(hum);
    
}

String floatToString(float number) {
  
  dtostrf(number,5,2,buffer);
  return String(buffer);
  
}
