#include <Keyboard.h>

int botoes[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
int tamanhoBotoes = sizeof(botoes) / sizeof(int);
int clickCount = -1;
unsigned long ultimaLeitura = 0;
unsigned long debounceDelay = 3000;

void setup() {
  //Keyboard.begin();
  Serial.begin(9600);
  for (int i = 0; i < tamanhoBotoes; i++) {
    pinMode(botoes[i], INPUT_PULLUP); 
  }
}

void loop() {
  for (int i = 0; i < tamanhoBotoes; i++) {
    exibeFrase(botoes[i], i);
  }
}


void exibeFrase(int botao, int indice) {
  if (digitalRead(botao) == LOW) {

    // algumas teclas do celular são responsáveis pro 4 caracteres, enquanto outras por 3
    int letrasPorBotao = indice == 5 || indice == 7 ? 4 : 3;
    
    // como a tecla de indice 5 tem 4 caracteres as próximas tem que ser deslocadas em 1
    int deslocamento = indice > 5 ? 1 : 0;

    ultimaLeitura = millis();
    //Serial.println(ultimaLeitura);
    while ((millis() - ultimaLeitura) < debounceDelay)
    {
      if (digitalRead(botao) == LOW) {
        clickCount++;
        //ultimaLeitura = millis();
        delay(350);
      }
      //Serial.println(clickCount);

      // 65 é o código ASCII para o caracter A maiúsculo
      char c = (char)65 + (clickCount % letrasPorBotao) + (indice * 3) + deslocamento;
      Serial.println(c);
    }
    
    //Serial.print(clickCount);
    //Serial.print(" ");
    clickCount = -1;
  }
}