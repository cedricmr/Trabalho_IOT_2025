#include <Keypad.h>

 char TECLAS_MATRIZ[4][4] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


 byte PINOS_LINHAS[4] = {22, 21, 23, 18}; // Pinos de conexao com as linhas do teclado
 byte PINOS_COLUNAS[4] = {5, 4, 19, 15}; // Pinos de conexao com as colunas do teclado

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, 4, 4); // Inicia teclado

void setup() {
  Serial.begin(9600); // Inicia porta serial
}

void loop() {

  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado

  if (leitura_teclas) { // Se alguma tecla foi pressionada
    Serial.println(leitura_teclas); // Imprime a tecla pressionada na porta serial
  }
  
}