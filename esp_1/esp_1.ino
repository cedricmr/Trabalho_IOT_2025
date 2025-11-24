#include <Keypad.h>

// --- Definição do Teclado ---
char TECLAS_MATRIZ[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const int pino = 21; 

byte PINOS_LINHAS[4] = {32, 33, 25, 26}; 
byte PINOS_COLUNAS[4] = {2, 15, 13, 12}; 

Keypad teclado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, 4, 4);

// --- Configurações da Senha ---
const String SENHA_EMBUTIDA = "1234"; 
const int MAX_SENHA = 4;

// --- Variáveis de Controle ---
String entrada_usuario = ""; 
int posicao_atual = 0; 
bool esperando_inicio = true; // true se esperando por '*'

void setup() {
  Serial.begin(9600);
  pinMode(pino, OUTPUT);
  Serial.println("Sistema Iniciado. Pressione '*' para comecar a digitar a senha.Pressione '#' para enviar a senha.");
}

void loop() {
  char leitura_teclas = teclado.getKey();

  if (leitura_teclas) {
    
    // --- Lógica de Controle de Início e Fim ---
    if (leitura_teclas == '*') {
      entrada_usuario = "";
      posicao_atual = 0;
      esperando_inicio = false;
      return;
    }
    
    if (leitura_teclas == '#') {
      // A tecla '#' é usada para ENVIAR/VALIDAR a senha
      esperando_inicio = true;
      Serial.println("\n ENVIADO.");
      
      // Verifica se a senha tem o comprimento correto antes de validar
      if (posicao_atual == MAX_SENHA) {
        if (entrada_usuario == SENHA_EMBUTIDA) {
          digitalWrite(pino, HIGH); 
          Serial.println("\n SENHA CORRETA!");
          // envia msg pro esp4 aqui <-----------
          // aciona o rele aqui <-----------
          delay(1000); 
          digitalWrite(pino, LOW);
          
        } else {
          digitalWrite(pino, HIGH); 
          Serial.println("\n SENHA INCORRETA!");
          // envia msg pro esp4 aqui <-----------
          delay(3000); 
          digitalWrite(pino, LOW); 
        }
      } else {
         Serial.println("\nERRO: Senha invalida. Tente novamente.");
      }
      
      // Reinicia e espera por novo início
      entrada_usuario = "";
      posicao_atual = 0;
      Serial.println("\nPressione '*' para uma nova tentativa.");
      return;
    }

    // --- Lógica de Captura da Senha ---
    if (!esperando_inicio) {
      if (posicao_atual < MAX_SENHA) {
        //Armazena a tecla digitada
        entrada_usuario += leitura_teclas;
        posicao_atual++;
        Serial.print("*"); // Exibir '*' esconde a senha.

      } else {
        // Se já atingiu o máximo, ignora a tecla e avisa
        Serial.println("\nLimite de digitos atingido. Pressione '#' para enviar.");
        // podemos adicionar lógica para validar automaticamente
      }
    } else {
        Serial.println("\nPressione '*' primeiro para reiniciar a digitacao da senha.");
    }
  }
}
