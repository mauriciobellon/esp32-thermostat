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

Config config;

OneWire oneWire(0); // GPIO where the DS18B20 is connected
DallasTemperature sensors(&oneWire);

const int relayPin = 5;
const int ledPin = 4;

bool hasConfigFile() {
    return SPIFFS.exists("/config.json");
}

void pinSetup() {
    pinMode(relayPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

void wifiStart() {
    WiFi.begin(config.ssid, config.password);
}

void wifiConnect() {
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

bool isWifiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void logging(const char *event) {
    // log latest 1000 events
}

void factoryReset() {
    SPIFFS.remove("/config.json");
    ESP.restart();
}

void setupFactory() {
    pinSetup();
    WiFi.softAP("ESP32_Setup");
    // Serve setup page and wait for POST configs
    // Save config file and reboot
}

void setupOperation() {
    pinSetup();
    sensors.begin();
    config.LoadConfig();
    wifiStart();
    // Serve operation page
    // Display wifi status, temp status, config
}

void loopOperation() {
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);

    if (!isWifiConnected()) {
        wifiConnect();
    }

    // Add your temperature threshold logic here
    if (temperature > 25.0) { // Example threshold
        digitalWrite(relayPin, HIGH); // Start cooling
    } else {
        digitalWrite(relayPin, LOW); // Stop cooling
    }

    // Update display
    // Log info
}

void setup() {
    Serial.begin(115200);
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    if (hasConfigFile()) {
        setupOperation();
    } else {
        setupFactory();
    }
}

void loop() {
    // if factory reset button is high triggers factoryReset()
    if (digitalRead(2) == HIGH) { // Example factory reset button GPIO
        factoryReset();
    }

    // if hasConfigFile triggers loopOperation()
    if (hasConfigFile()) {
        loopOperation();
    }

    delay(1000);
}
