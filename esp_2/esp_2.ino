const int RELAY_PIN = 12; 
int sensorPin = 13; 
int leituraSensor; 
int contagem = 0; 
bool statusPorta = false;
bool statusLED = false;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  
  statusPorta = getStatus(); // retorna true se a senha for correta no esp1 <-------------
  if (statusPorta){
    digitalWrite(RELAY_PIN, HIGH);
  }else{
    digitalWrite(RELAY_PIN, LOW);
  }
  leituraSensor = digitalRead(sensorPin);
  if ( leituraSensor == 1) { // possivelmente mudar a forma de contabilizar tempo<--------
    contagem++;
    if(contagem == 20){
      //envia comando que acende led verde e vermelho <-------------------
      statusLED = true
    }
    delay(250); 
  }else{
    contagem = 0;
    if (statusLED){
      //envia comando que apaga led verde e vermelho <-------------------
      statusLED = false;
    }
  }
}
