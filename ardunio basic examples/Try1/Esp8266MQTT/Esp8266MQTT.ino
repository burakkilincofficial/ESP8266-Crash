#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bodesere";
const char* pswd = "41611291080Br.";
const char* mqtt_server =  "192.168.1.113";
const char* topic = "led";

#define LED_PIN 2
#define BUTTON_PIN 13

WiFiClient espClient;
PubSubClient client(espClient);

int status = WL_IDLE_STATUS;

void callback(char* topic, byte* payload, unsigned int length) {
  while ((char)payload[0] != '0') {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Lamba acik");
  }
  digitalWrite(LED_PIN, LOW);
  Serial.println("Lamba kapali");
}


void setup() {
  pinMode(LED_PIN, OUTPUT);
  delay(5000);
  String clientId = "I am Esp8266.";
  Serial.begin(115200);
  Serial.println("Started");
  WiFi.begin(ssid, pswd);
  delay(5000);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  client.connect(clientId.c_str());
  client.subscribe(topic);
  client.publish(topic, clientId.c_str(), true);
}


void loop() {
  delay(1000);
  String payload = "0";
  Serial.println(client.connected());
  if (!client.connected()) {
    payload = "1";
    client.publish(topic, payload.c_str(), true );
  } else {
    client.publish(topic, payload.c_str(), true );
  }
  client.loop();
}
