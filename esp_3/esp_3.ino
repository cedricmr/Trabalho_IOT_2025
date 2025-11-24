#include "DHT.h"

#define DHTPIN 15       // Pino conectado ao DHT11
#define DHTTYPE DHT11  // Tipo do sensor

DHT dht(DHTPIN, DHTTYPE);

const float overheat = 26;

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
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.println(temperature, 1);
    // enviar os dados para o BD <---------
    if(temperature > overheat){
      // enviar alerta para esp4 <---------
    }
  }

  delay(1000); 
}
