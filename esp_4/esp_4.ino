const int verde = 15;
const int amarelo = 13; 
const int vermelho = 12; 
bool overheat = false;
bool
void setup() {
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT); 
  pinMode(vermelho, OUTPUT); 
  digitalWrite(verde, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(vermelho, LOW);
}

void loop() {
  //recebe sinais das outras esps <-------------------------------
  if (overheat){
    digitalWrite(amarelo, HIGH);
  }else{
    digitalWrite(amarelo, LOW);
  }
  if(){       //tem prioridade sobre a led verde e vermelha, confere esp2 por porta aberta + de 5s
    digitalWrite(verde, HIGH);
    digitalWrite(vermelho, HIGH);
    while (true){ // fica conferindo a porta do esp2 ate sair
      //confere porta(esp2) e overheat(esp3)   <-------------------------------------------
          if (overheat){
        digitalWrite(amarelo, HIGH);
      }else{
        digitalWrite(amarelo, LOW);
      }
      if(){//se a porta(esp2) estiver fechada, sai do loop <-------------------
        digitalWrite(verde, LOW);
        digitalWrite(vermelho, LOW);
        break;
      }
    }
  } else {    // PROBLEMA: nao responde a mais nenhum evento nessa versao, ignora overheat por 3s
    if (){   //confere ocorreu evento de envio de senha e se acertou a senha no esp1 <-----------------
    digitalWrite(verde, HIGH);
    delay(3000)
    digitalWrite(verde, LOW);
    }else{
      digitalWrite(vermelho, HIGH);
      delay(3000)
      digitalWrite(vermelho, LOW);
    }
  }
  
}
