
#define xPin 34 
#define yPin 33  
#define swPin 19 

void setup() {
  pinMode(swPin, INPUT_PULLUP);


  Serial.begin(9600);
}

void loop() {
  analogico();  
}

void analogico(){
  Serial.print("X: ");
  Serial.print(analogRead(xPin)); 
  Serial.print("|Y: ");
  Serial.print(analogRead(yPin)); 
  Serial.print("|Z: ");
  Serial.println(digitalRead(swPin)); 
  delay(500);

}




