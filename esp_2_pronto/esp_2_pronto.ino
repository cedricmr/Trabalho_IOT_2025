#include <WiFi.h>
#include <PubSubClient.h>

// ===== CONFIG WIFI =====
//const char* ssid = "FLAT1-2.4";
//const char* password = "pr123456"; 

const char* ssid = "Galaxy A33 5G4487";
const char* password = "gjdi0297";

// ===== CONFIG MAQIATTO =====
const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;

// Login criado no SITE do Maqiatto
const char* mqttUser = "cmrocha@inf.ufsm.br";
const char* mqttPassword = "gjdi0297";

// Tópico criado no Maqiatto (EXATO!)
const char* mqttTopicSub = "cmrocha@inf.ufsm.br/controle/led_estado";
const char* mqttTopicPub = "cmrocha@inf.ufsm.br/controle/led_estado";

const int RELAY_PIN = 12; 
int sensorPin = 13; 
int leituraSensor; 
bool statusPorta = false;
bool statusLed = false;
static unsigned long lastMsg = 0;

String estado_payload = "";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++)
    msg += (char)payload[i];
  
  estado_payload = msg;
  Serial.print("Mensagem recebida: ");
  Serial.println(msg);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao Maqiatto... ");
    if (client.connect("paw4vy5934", mqttUser, mqttPassword)) {
      Serial.println("Conectado!");
      client.subscribe(mqttTopicSub);
    } else {
      Serial.print("Falhou, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi conectado!");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  pinMode(sensorPin, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(estado_payload == "pullup"){
    digitalWrite(RELAY_PIN, HIGH);
  }
  if(estado_payload == "pulldown"){
    digitalWrite(RELAY_PIN, LOW);
  }
  
  leituraSensor = digitalRead(sensorPin);
  if (leituraSensor == 0 && lastMsg == 0){
    lastMsg = millis();
  } else if(leituraSensor == 1){
    if (!client.connected()) {
     reconnect();
    } 
    client.publish(mqttTopicPub, "fechado");
    Serial.println("Mensagem fechado enviada ao Maqiatto!");
    statusLed = false;
    lastMsg = 0;
    delay(1000);
  }
  if (millis() - lastMsg >= 5000 && lastMsg != 0) {
    if (!client.connected()) {
     reconnect();
    } 
    client.publish(mqttTopicPub, "ABERTO");
    Serial.println("Mensagem ABERTO enviada ao Maqiatto!");
    statusLed = true;
    lastMsg = 0;
  }
}
