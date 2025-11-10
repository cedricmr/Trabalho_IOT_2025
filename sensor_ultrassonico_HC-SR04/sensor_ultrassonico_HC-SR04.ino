float duracao, distancia;

#define trig 23
#define echo 22

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  leitura();
  Serial.print(distancia);
  Serial.print(" cm\n");
  delay(500);
}

void leitura(){
  digitalWrite(trig, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW); 
  duracao= pulseIn(echo,HIGH);
  distancia = (duracao*.0343)/2; 
}