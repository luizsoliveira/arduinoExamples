#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
 
//Configura o nome da rede sem fio que se deseja conectar
const char *ssid = "MinhaRede";
 
//Configura a senha rede sem fio que se deseja conectar
const char *password = "senhaMinhaRede";

bool red, yellow, green = LOW;

#define LED_RED 17
#define LED_YELLOW 25
#define LED_GREEN 26

 
WebServer server(80);
 
void setup(void) {
  delay(5000);
  //Configura o baudrate da comunicação serial
  Serial.begin(115200);
  delay(5000);
  //Configura a conexão à rede sem fio
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  
  server.on("/red", handleRed);
  server.on("/yellow", handleYellow);
  server.on("/green", handleGreen);
  
    
  /*server.on("/inline", []() {
   server.send(200, "text/plain", "this works as well");
  });*/
  
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
 server.handleClient();
 delay(2);//allow the cpu to switch to other tasks
}

void handleRoot() {
 String html = "";
 html+= "<style>a {font-size:40px; background-color:#CCCCCC;}</style>";
 html+= "<meta charset='UTF-8'>";
 html += "<h1>Exemplo ESP32Station IFRJ campus Niterói</h1>";
 html += "Clique <a href=\"/red\">aqui</a> para ligar/desligar o LED Vermelho.<br><br><br>";
 html += "Clique <a href=\"/yellow\">aqui</a> para ligar/desligar o LED Vermelho.<br><br><br>";
 html += "Clique <a href=\"/green\">aqui</a> para ligar/desligar o LED Vermelho.<br><br><br>";
 
 html += "<h3>Autor: Luiz Oliveira</h3>";
 server.send(200, "text/html", html);
}
 
void handleRed() {
 red = !red;
 digitalWrite(LED_RED, red);
 Serial.print("Definindo pino ");
 Serial.print(LED_RED);
 Serial.print(" como ");
 Serial.print(red);
 handleRoot();
}

void handleYellow() {
 yellow = !yellow;
 digitalWrite(LED_YELLOW, yellow);
 handleRoot();
}

void handleGreen() {
 yellow = !green;
 digitalWrite(LED_GREEN, green);
 handleRoot();
}
 
 
void handleNotFound() {
 String message = "File Not Found\n\n";
 message += "URI: ";
 message += server.uri();
 message += "\nMethod: ";
 message += (server.method() == HTTP_GET) ? "GET" : "POST";
 message += "\nArguments: ";
 message += server.args();
 message += "\n";
 for (uint8_t i = 0; i < server.args(); i++) {
   message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
 }
 server.send(404, "text/plain", message);
}
 
