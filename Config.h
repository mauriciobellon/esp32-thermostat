#include <SPIFFS.h>
#include <ArduinoJson.h>

class Config {
public:
    char ssid[32];
    char password[32];
    char hostname[32];

    void LoadConfig() {
        if (SPIFFS.exists("/config.json")) {
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
                size_t size = configFile.size();
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonDocument doc(1024);
                deserializeJson(doc, buf.get());

                strcpy(ssid, doc["ssid"]);
                strcpy(password, doc["password"]);
                strcpy(hostname, doc["hostname"]);

                configFile.close();
            }
        } else {
            strcpy(ssid, "default_ssid");
            strcpy(password, "default_password");
            strcpy(hostname, "esp32_thermostat");
        }
    }

    void SaveConfig() {
        DynamicJsonDocument doc(1024);
        doc["ssid"] = ssid;
        doc["password"] = password;
        doc["hostname"] = hostname;

        File configFile = SPIFFS.open("/config.json", "w");
        serializeJson(doc, configFile);
        configFile.close();
    }
};
