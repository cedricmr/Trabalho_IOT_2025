#include <WiFi.h>
#include <PubSubClient.h>

// ===== CONFIG WIFI =====
//const char* ssid = "FLAT1-2.4";
//const char* password = "pr123456"; 

const char* ssid = "iot2022";
const char* password = "S3nhab0@";

// ===== CONFIG MAQIATTO =====
const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;

// Login criado no SITE do Maqiatto
const char* mqttUser = "cmrocha@inf.ufsm.br";
const char* mqttPassword = "gjdi0297";

// Tópico criado no Maqiatto (EXATO!)
const char* mqttTopic = "cmrocha@inf.ufsm.br/esp1";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao Maqiatto... ");
    if (client.connect("paw4vy5934", mqttUser, mqttPassword)) {
      Serial.println("Conectado!");
      client.subscribe(mqttTopic);
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
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 2000) {
    lastMsg = millis();
    client.publish(mqttTopic, "Mensagem do ESP32!");
    Serial.println("Mensagem enviada ao Maqiatto!");
  }
}