/*********
  ESP32 Thermostat
  by Mauricio Faria Bellon
  http://github.com/mauriciobellon/esp32-thermostat
  
  
  This is a simple refrigerator thermostat for ESP32
  It uses a temperature sensor and a relay to control the compressor
  It has a web interface to configure the temperature and the wifi connection
  
  This code is in the public domain.
**********/


#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Config.h>


void LoadConfig(){
    if (SPIFFS.exists("/config.json")){
    }
    else{
        // set default variables
    }
};


void pinSetup(){};

void wifiStart(){};

void wifiConnect(){};

void isWifiConnected(){};

void logging(char *event){
    // log lattest 1000 events
};

void factoryReset(){
    // Erases config file
    // Reboot
};

void setupFactory(){
    // pinSetup()
    // start Wifi AP
    // serves setup page
    // wait POST configs
    // save config file
    // reboot
};

void setupOperation(){
    // pinSetup()
    // start Display
    // start Thermostat
    // read Config File
    // start Wifi Client
    // serves operation page
    //  wifi status
    //  temp status
    //  config
};

void loopOperation(){
    // read temp
    // check wifi if disconnect try to connect
    // compare temp
    // start or stop cooling
    // update display
    // log info
};

void setup()
{
  Serial.begin(115200);
  if (hasConfigFile())
  {
    setupOperation()
  }
  else
  {
    setupFactory()
  }
}

void loop()
{
  // if factory reset button is high triggers factoryReset()
  // if hasConfigFile triggers loopOperation()

  delay(1000)
}