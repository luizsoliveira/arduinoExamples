#include <WiFi.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include "DHT.h"

// Set consts
// WiFi Connection set

#define SSID "SSID"
#define PASSWORD "PASSWORD"

// Temperature alert configs

float max_temp = 30;
float min_temp = 10;

// MQTT Connection set 

#define MQTT_ID "luiz-ifrjesp32group-ifrjcnit"
#define MQTT_BROKER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_MILLIS_TOPIC "farias_ifrjesp32group_ifrjcnit_millis"
#define MQTT_TEMPERATURE_TOPIC "luiz_ifrjesp32group_ifrjcnit_heatsensor"
#define MQTT_TEMPERATURE_STATUS_TOPIC "luiz_ifrjesp32group_ifrjcnit_temperaturealert"
#define MQTT_LED_TOPIC "fariasys-led-power-manage"

// Set ports

#define LED_R 2
#define LED_Y 18
#define LED_G 5
#define DHTPIN 14 

// Set the type of DHT sensor

#define DHTTYPE DHT11 

// Define net client
WiFiClient espClient; 

// Define mqtt client
PubSubClient MQTT(espClient);

// Define DHT
DHT dht(DHTPIN, DHTTYPE);

// Vars
char millis_str[10] = "";


void setupWIFI(){
  if(WiFi.status() == WL_CONNECTED){
    return;
  } else {
    // Connect with WiFi

    Serial.println();
    Serial.print("Connecting to");
    Serial.println(SSID);

    WiFi.begin(SSID, PASSWORD);

    // Loop para checar a conexão

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    // Display connection info

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP Address:");
    Serial.println(WiFi.localIP());
    }
}

void setupMQTT(){
    // Config MQTT Broker connection

    MQTT.setServer(MQTT_BROKER, MQTT_PORT);
    MQTT.setCallback(mqtt_ifrj_callback); 

    // Conn exec

    while (!MQTT.connected()){
        Serial.print("- MQTT Setup: Tentando se conectar ao Broker MQTT: ");
        Serial.println(MQTT_BROKER);

        if(MQTT.connect(MQTT_ID)){
            Serial.println("- MQTT Setup: Conectado com sucesso");
             MQTT.subscribe(MQTT_LED_TOPIC);
        } else {
            Serial.println("- MQTT Setup: Falha ao se conectar, tentando novamente em 2s");
            delay(2000);
        }
    }
}

void setup(void){
    // Set baudrate of serial com
    Serial.begin(115200);

    // Pinmode
    pinMode(LED_R, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_G, OUTPUT);

    // Call setup wifi
    setupWIFI();
    // Call setup mqtt
    setupMQTT();
    // Start dht
    dht.begin();
}

void loop(void){
    sprintf(millis_str, "%d", millis()); // store printf of data (millis)

    MQTT.publish(MQTT_MILLIS_TOPIC, millis_str); // publish in topic
  
    setupWIFI();
    setupMQTT();
    MQTT.loop();
    //delay(2000);

    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    if (isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    } else {
      MQTT.publish(MQTT_TEMPERATURE_TOPIC, String(t).c_str());
      if t > max_temp{
        MQTT.publish(MQTT_TEMPERATURE_STATUS_TOPIC, "HT");
      } else if max_temp < t and t > min_temp {
        MQTT.publish(MQTT_TEMPERATURE_STATUS_TOPIC, "NT");
      } else if t < min_temp {
        MQTT.publish(MQTT_TEMPERATURE_STATUS_TOPIC, "LT")
      }
    }

}

void mqtt_ifrj_callback(char* topic, byte* payload, unsigned int length)
{
  String msg;
  Serial.print("Topic: ");
  Serial.println(topic);

  //obtem a string do payload recebido
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }

  //Controlando LED RED
  if (msg.equals("R1"))
    {
      digitalWrite(LED_R, HIGH);
      Serial.println("L recebido");
    } else if (msg.equals("R0"))
    {
      digitalWrite(LED_R, LOW);
      Serial.println("D recebido");
    }
  if (msg.equals("G1"))
    {
      digitalWrite(LED_G, HIGH);
      Serial.println("L recebido");
    } else if (msg.equals("G0"))
    {
      digitalWrite(LED_G, LOW);
      Serial.println("D recebido");
    }
  if (msg.equals("Y1"))
    {
      digitalWrite(LED_Y, HIGH);
      Serial.println("L recebido");
    } else if (msg.equals("Y0"))
    {
      digitalWrite(LED_Y, LOW);
      Serial.println("D recebido");
    }
   
  

}
