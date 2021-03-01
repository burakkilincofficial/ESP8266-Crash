#ifndef WIFICONFIG_H
#define WIFICONFIG_H

class WifiConfig
{
  private:
    char* ssid;
    char* pswd;
    char* mqtt_server;
    char* topic;
  public:
    WifiConfig(char* ssid, char* pswd, char* mqtt_server, char* topic);
    void setUpWifi();
    char* getMqttServer();
    char* getTopic();
};

#endif
