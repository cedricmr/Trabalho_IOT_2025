#include <Keypad.h>

 char TECLAS_MATRIZ[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


 byte PINOS_LINHAS[4] = {22, 21, 23, 18}; 
 byte PINOS_COLUNAS[4] = {5, 4, 19, 15}; 

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, 4, 4); 

void setup() {
  Serial.begin(9600); 
}

void loop() {

  char leitura_teclas = teclado_personalizado.getKey(); 

  if (leitura_teclas) { 
    Serial.println(leitura_teclas); 
  }
  
}