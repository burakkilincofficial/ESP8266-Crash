#include <ESP8266WiFi.h>

class WifiConfig {
  private:
    char* ssid;
    char* pswd;
    char* mqtt_server;
    char* topic;
  public:
    WifiConfig(char* ssid, char* pswd, char* mqtt_server, char* topic)
    {
      setConfigurations(ssid, pswd, mqtt_server, topic);
    }

    void setConfigurations(char* ssid_, char* pswd_, char* mqtt_server_, char* topic_)
    {
      ssid = ssid_;
      pswd = pswd_;
      mqtt_server = mqtt_server_;
      topic = topic_;

    }

    void setUpWifi() {
      WiFi.begin(ssid, pswd);
    }

    char* getMqttServer(){
      return mqtt_server;
    }

    char* getTopic(){
      return topic;
    }
};
