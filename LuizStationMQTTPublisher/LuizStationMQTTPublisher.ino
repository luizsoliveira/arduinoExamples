#include <WiFi.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
 
//Net Setup
#define NET_SSID "MinhaRede"
#define NET_PASSWORD "senhaMinhaRede"

//MQTT Setup
#define MQTT_ID "luiz-esp32-0800313131"
#define MQTT_BROKER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_MILLIS_TOPIC "ifrj_cnit_luizfelipe_millis"
WiFiClient espClient; //Cliente de rede
PubSubClient MQTT(espClient); //Cliente MQTT

char millis_str[10] = "";

void setupWifi() {
  //Configura a conexão à rede sem fio

  if (WiFi.status() == WL_CONNECTED)
        return;
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(NET_SSID);
  
  WiFi.begin(NET_SSID, NET_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupMQTT() {
   MQTT.setServer(MQTT_BROKER, MQTT_PORT);   //informa qual broker e porta deve ser conectado
   //MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
   while (!MQTT.connected()) 
    {
        Serial.print("*Tentando se conectar ao Broker MQTT: ");
        Serial.println(MQTT_BROKER);
        if (MQTT.connect(MQTT_ID)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentativa de conexao em 2s");
            delay(2000);
        }
    }
}

void setup(void) {
  //Configura o baudrate da comunicação serial
  Serial.begin(115200);
 
  setupWifi();

  setupMQTT();

}
 
void loop(void) {

  sprintf(millis_str, "%d", millis());

  MQTT.publish(MQTT_MILLIS_TOPIC, millis_str);
  
  setupWifi();
  setupMQTT();
  delay(2000);
}

 
