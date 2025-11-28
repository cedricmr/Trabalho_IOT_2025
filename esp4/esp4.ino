#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Galaxy A33 5G4487";
const char* password = "gjdi0297";

const char* mqttUser = "cmrocha@inf.ufsm.br";
const char* mqttPassword = "gjdi0297";

const char* mqttTopic = "cmrocha@inf.ufsm.br/controle/led_estado";

const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;

const int verde = 15;
const int amarelo = 13; 
const int vermelho = 12;

String estado_payload = "";

WiFiClient espClient;
PubSubClient client(espClient);

// === RECEBE MENSAGEM ===
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++)
    msg += (char)payload[i];
  
  estado_payload = msg;
  Serial.print("Mensagem recebida: ");
  Serial.println(msg);
}

// === RECONEXÃO ===
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao Maqiatto... ");
    if (client.connect("receiverESP", mqttUser, mqttPassword)) {
      Serial.println("Conectado!");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Falhou. rc=");
      Serial.println(client.state());
      delay(1000);
    }
  }
}

void setup() {
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
  Serial.println("WiFi conectado!");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

// === LOOP NÃO BLOQUEANTE ===
void loop() {
  if (!client.connected())
    reconnect();

  client.loop();

  // TRATAMENTO DE EVENTOS EM TEMPO REAL
  if (estado_payload == "overheat") {
    digitalWrite(amarelo, HIGH);
  }

  else if (estado_payload == "cooled") {
    digitalWrite(amarelo, LOW);
  }

  else if (estado_payload == "ABERTO") {
    digitalWrite(verde, HIGH);
    digitalWrite(vermelho, HIGH);
  }

  else if (estado_payload == "fechado") {
    digitalWrite(verde, LOW);
    digitalWrite(vermelho, LOW);
  }

  else if (estado_payload == "auto") {
    digitalWrite(verde, HIGH);
    delay(3000);
    digitalWrite(verde, LOW);
  }

  else if (estado_payload == "neg") {
    digitalWrite(vermelho, HIGH);
    delay(3000);
    digitalWrite(vermelho, LOW);
  }

  estado_payload = "";
}