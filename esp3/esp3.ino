#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 15 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);
const float overheat = 29;

// ===== CONFIG WIFI =====
//const char* ssid = "FLAT1-2.4";
//const char* password = "pr123456"; 

//const char* ssid = "iot2022";
//const char* password = "S3nhab0@";

//const char* ssid = "TP-Link_05AC";
//const char* password = "67542253";

const char* ssid = "Galaxy A33 5G4487";
const char* password = "gjdi0297";

// ===== CONFIG MAQIATTO =====
const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;

// Login criado no SITE do Maqiatto
const char* mqttUser = "cmrocha@inf.ufsm.br";
const char* mqttPassword = "gjdi0297";

// Tópico criado no Maqiatto (EXATO!)
const char* mqttTopicBD = "cmrocha@inf.ufsm.br/laboratorio/ambiente/dados";
const char* mqttTopicLED = "cmrocha@inf.ufsm.br/controle/led_estado";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao Maqiatto... ");
    if (client.connect("paw4vy5934", mqttUser, mqttPassword)) {
      Serial.println("Conectado!");
      //client.subscribe(mqttTopic);
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
  dht.begin();

  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWiFi conectado!");

  client.setServer(mqttServer, mqttPort);
}
float humidity;
float temperature;
void loop() {
  static unsigned long lastMeasure = 0;

  if (millis() - lastMeasure > 1000) {
    lastMeasure = millis();

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Erro ao ler o sensor DHT11!");
    } else {
      Serial.print("\t");
      Serial.print(humidity, 1);
      Serial.print("\t\t");
      Serial.println(temperature, 1);
      // enviar os dados para o BD <---------
      //char buffer[50];
      //sprintf(buffer, "{\"umidade\":\"%.2f\", \"temperatura\": "%.2f"}",humidity, temperature);
      //client.publish(mqttTopicBD, buffer);
      if(temperature > overheat){
        // enviar alerta para esp4 <---------
        client.publish(mqttTopicLED, "overheat");
        Serial.println("Overheat!");
      }
      else{
        client.publish(mqttTopicLED, "cooled");
        Serial.println("Cooled!");
      }
    }
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //static unsigned long lastMsg = 0;
  //if (millis() - lastMsg > 2000) {
  //  lastMsg = millis();
  //  client.publish(mqttTopic, "ESP3 - Sensor DHT11");
  //  Serial.println("Mensagem enviada ao Maqiatto!");
  //}
}