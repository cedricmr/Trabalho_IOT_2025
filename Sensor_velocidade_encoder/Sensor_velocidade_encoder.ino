int sensorPin = 19; 
int leituraSensor; 
int contagem = 0; 
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  leituraSensor = digitalRead(sensorPin);
  if ( leituraSensor == 1) {
    contagem++; 
    Serial.print("Numero de deteccoes: ");
    Serial.println(contagem); 
    delay(250); 
  }
}