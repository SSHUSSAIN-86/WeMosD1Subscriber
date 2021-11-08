#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

char* ssid = "";//replace this with your wifi access point name
const char* password = ""; //replace with your wifi password
const char* mqttbroker = "broker.mqttdashboard.com"; //IP address of broker
int mqttport = 1883;
char* mqttUser = "mqttusername";
char* mqttPassword = "mqttpassword";

WiFiClient espClient;
PubSubClient client(espClient);
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message received from topic: ");
  Serial.print(topic);
  Serial.print("   length is:");
  Serial.println(length);

  Serial.print("Data received from Broker:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");
  Serial.println();

}

void setup_wifi() {
    delay(50);
    // Start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void setup() {

  Serial.begin(115200);
  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
  
  client.setServer(mqttbroker, mqttport);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT.....");

    if (client.connect("ESP328266Client", mqttUser, mqttPassword ))
    {

      Serial.println("Connected to MQTT broker");

    }
    else
    {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(500);

    }
  }

  
  Serial.println("ESP8266 AS SUBSCRIBER");
  Serial.println("Subscribing to topic:");
  client.subscribe("hello world");//This is the topic name

}

void loop() {
  client.loop();
}

