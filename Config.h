#include <SPIFFS.h>


class Config{
    public:
        char ssid[32];
        char password[32];
        char hostname[32];

        void LoadConfig(){
            if (SPIFFS.exists("/config.json")){
                
            }
            else{
                
            }
        };
};