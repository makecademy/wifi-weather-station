/* 
*  Simple WiFi weather station with Arduino, the DHT11 sensor & the CC3000 chip
*  Part of the code is based on the work done by Adafruit on the CC3000 chip & the DHT11 sensor
*  Writtent by Marco Schwartz for Open Home Automation
*/

// Include required libraries
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include "DHT.h"
#include<stdlib.h>

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// Buffer for float to String conversion
char buffer[5];

// WiFi network (change with your settings !)
#define WLAN_SSID       "yourNetwork"
#define WLAN_PASS       "yourPassword"
#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

// DHT11 sensor pins
#define DHTPIN 7 
#define DHTTYPE DHT11

// Create CC3000 & DHT instances
DHT dht(DHTPIN, DHTTYPE);
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);
                                         
// Local server IP, port, and repository (change with your settings !)
uint32_t ip = cc3000.IP2U32(192,168,1,179);
int port = 8888;
String repository = "/wifi-weather-station/";
                                         
void setup(void)
{
 
  // Initialize DHT sensor
  dht.begin();
  
  Serial.begin(115200);
  
  // Initialise the CC3000 module
  if (!cc3000.begin())
  {
    while(1);
  }

  // Connect to  WiFi network
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println("Connected to WiFi network!");
    
  // Check DHCP
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }  
  
}

void loop(void)
{
  
    // Measure the humidity & temperature
    float h = dht.readHumidity();
    float t = dht.readTemperature();
     
    // Transform to String
    String temperature = floatToString(t);
    String humidity = floatToString(h);
    
    // Print data
    Serial.println(temperature);
    Serial.println(humidity);
    
    // Send request
    Serial.println("GET "+ repository + "sensor.php?temp=" + temperature + "&hum=" + humidity + " HTTP/1.0");
    String request = "GET "+ repository + "sensor.php?temp=" + temperature + "&hum=" + humidity + " HTTP/1.0";
    send_request(request);
    
    // Update every 10 sec
    delay(10000);
}

// Function to send a TCP request and get the result as a string
void send_request (String request) {
     
    // Transform to char
    char requestBuf[request.length()];
    request.toCharArray(requestBuf,request.length()); 
  
    // Connect    
    Serial.println("Starting connection to server...");
    Adafruit_CC3000_Client www = cc3000.connectTCP(ip, port);
    
    // Send request
    if (www.connected()) {
      www.fastrprintln(requestBuf);      
      www.fastrprintln(F(""));
    } 
    else {
      Serial.println(F("Connection failed"));    
    }

    while (www.connected()) {
      while (www.available()) {

      // Read answer
      char c = www.read();
      }
    }
    www.close();
    
    free(requestBuf);
}

// Float to String conversion
String floatToString(float number) {
  
  dtostrf(number,5,2,buffer);
  return String(buffer);
  
}
