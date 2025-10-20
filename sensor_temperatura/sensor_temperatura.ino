#include "DHT.h"

#define DHTPIN 5       // Pino conectado ao DHT11
#define DHTTYPE DHT11  // Tipo do sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("Status\tHumidity (%)\tTemperature (C)");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro ao ler o sensor DHT11!");
  } else {
    Serial.print("OK\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.println(temperature, 1);
  }

  delay(2000); // aguarda 2 segundos antes da próxima leitura
}
