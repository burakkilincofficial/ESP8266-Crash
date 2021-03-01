#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define L1 2

const char* ssid = "Bodesere";
const char* password =  "41611291080Br.";

const char* mqttServer = "192.168.1.113";
const int mqttPort = 1883;
const char* mqttTopicSub = "led";


WiFiClient espClient;

PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(L1, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Waiting for connected to WiFi network..");
  }
  Serial.println("Connected to a WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");

    if (client.connect("ESP8266Client")) {
      Serial.println("Connected");

    } else {
      Serial.print("state failure  ");
      Serial.print(client.state());

      delay(2000);
    }
  }

  client.subscribe(mqttTopicSub);
}

void callback(char* topic, byte* payload, unsigned int length) {

  payload[length] = '\0';
  String strMSG = String((char*)payload);
  String resultMessage;
  if (strMSG == "1") {
    resultMessage = "Lamp is open.";
  }
  else if (strMSG == "0") {
    resultMessage = "Lamp is closed.";
  }
  Serial.print("The message arrived from the topic: ");
  Serial.println(topic);
  Serial.print("message:");
  Serial.print(resultMessage);
  Serial.println("\n-----------------------");

  if (strMSG == "1") {
    digitalWrite(L1, HIGH);
  } else if (strMSG == "0") {
    digitalWrite(L1, LOW);
  }
}

void reconect() {
  while (!client.connected()) {
    Serial.print("Trying connect to MQTT broker");

    //   bool connected = strlen(mqttUser) > 0 ?
    //                    client.connect("ESP8266Client", mqttUser, mqttPassword) :
    //                    client.connect("ESP8266Client");
    bool connected  = client.connect("ESP8266Client");
    if (connected) {
      Serial.println("Connected!");
      client.subscribe(mqttTopicSub, 1);
    } else {
      Serial.println("Failed during connection. Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Retrying in 10 sec");

      delay(10000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconect();
  }
  if (digitalRead(5)) {
    Serial.println("Butona basildi");
    client.publish(mqttTopicSub, "5", true);
    delay(1000);
  }
  client.loop();
}
