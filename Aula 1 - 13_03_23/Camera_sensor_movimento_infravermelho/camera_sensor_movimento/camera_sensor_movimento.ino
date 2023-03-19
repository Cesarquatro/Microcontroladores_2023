/*
 * Doscente: Marilza Antunes de Lemos
 * Discente: Cesar Augusto Mendes Cordeiro da Silva
 * Aula 1 - Camera de seguranca com 3 sensores PIR
 * 13/03/2023
 */

//Importando a biblioteca do servo motor
#include <Servo.h>
 
//Definindo as porttas dos sensores
#define sensorEsquerda 8
#define sensorCentro   7
#define sensorDireita  6

//Definindo a porta do motor
#define pinServo A5 //porta analogica

//[Da biblioteca]Cria um objeto do tipo Servo com o nome 'motor' 
Servo motor;

//Angulos predefinidos e calibrados para o servo que estou usando
#define posESQUERDA 180 //180º
#define posCENTRO   92 //92º
#define posDIREITA  0 //0º

//Definindo os tempos para o movimento do servo
#define tempoMOV 1       //1ms entre cada angulo de movimento
#define tempoDETECT 3000 //3s entre cada leitura dos sensores

//Defini as variaveis de posição
int posAtual = posCENTRO; //posAtual inicializa com o valor da posCENTRO
int posMovimento;         //Variavel que será para passar o angulo para o servo

/*Definido as variaveis de tempo, uma vez que esse código utiliza a função millis()
  e não a função delay(). O principal motivo é que a função delay() trava o código
  enquanto a função millis é utilizada dentro de um if para comparar o tempo atual
  com um valor que representa o tempo salvo anteriormente. Depois de comparar e realizar
  a ação escolhida, o tempo anterior é atualizado para uma futura comparação. Tudo isso 
  acontece sem travar o void loop, tal ação poderá ser executada de tempo em tempo sem que
  outras ações sejam atrasadas.
  
  Ex: Se o tempo para o delay escolhido for 3s, o void loop funcionará normalmente, sempre
  checando se a diferença entre o tempo atual (fornecido pela função millis) com o tempo
  salvo anteriomente é maior ou igual a 3s, apenas quando for maior entrará dentro do if.
  
  Documentação da função millis(): 
  https://reference.arduino.cc/reference/en/language/functions/time/millis/

  Este vídeo explica de forma visual e muito clara, porém está em inglês:
  https://youtu.be/BYKQ9rk0FEQ
  */
unsigned long tempoAnteriorMov;
unsigned long tempoAnterior;

void setup() {
  //Define as portas dos sensores como ENTRADA
  pinMode(sensorEsquerda, INPUT);
  pinMode(sensorCentro,   INPUT);
  pinMode(sensorDireita,  INPUT);

  //[Da biblioteca]Define a portaa dos servo como SAIDA
  motor.attach(pinServo);
  
  //Coloca o servo na posição CENTRO no início o código
  motor.write(posAtual);

  //
  posMovimento = posAtual;

  //Inicia a comunicação serial para fazer debug no monitor
  Serial.begin(9600);
}

void loop() {

  //Escreve na Serial as leituras dos sensores
  Serial.print(digitalRead(sensorEsquerda));
  Serial.print(digitalRead(sensorCentro));
  Serial.print(digitalRead(sensorDireita));

  //Escreve na Serial a variavel posAtual
  Serial.print("\t");
  Serial.println(posAtual);

//LEITURA DOS SENSORES
  //Se a diferença do tempo atual [millis()] com o tempoAnterior for
  //maior que a diferença entre o tempo escolhido para o delay faça:
  if ((millis() - tempoAnterior) > tempoDETECT){
    
    //Se a leitura do sensorCentro detectar movimento
    if (digitalRead(sensorCentro)){
      
      //Se posAtual diferente da posCENTRO
      if (posAtual != posCENTRO){
        posAtual = posCENTRO;     //Atualize a posAtual para posCENTRO
        tempoAnterior = millis(); //Atualiza o tempo anterior para o tempo atual
      }//if (posAtual != posCENTRO)
    }//if (digitalRead(sensorCentro))
    
    else {
      //Se a leitura do sensorEsquerda e sensorDireita detectarem movimento
      if (digitalRead(sensorEsquerda) && digitalRead(sensorDireita)) {
        
        //Se posAtual diferente da posCENTRO
        if (posAtual != posCENTRO) {
          posAtual = posCENTRO;     //Atualize a posAtual para posCENTRO
          tempoAnterior = millis(); //Atualiza o tempo anterior para o tempo atual
        }//if (posAtual != posCENTRO)
      }//if (digitalRead(sensorEsquerda) && digitalRead(sensorDireita))
      
      else {

        //Se a leitura do sensorEsquerda detectar movimento
        if (digitalRead(sensorEsquerda)) {
          
          //Se posAtual diferente da posESQUERDA
          if (posAtual != posESQUERDA) {
            posAtual = posESQUERDA;   //Atualize a posAtual para posESQUERDA
            tempoAnterior = millis(); //Atualiza o tempo anterior para o tempo atual
          }//if (posAtual != posESQUERDA)
        }//if (digitalRead(sensorEsquerda))

        //Se a leitura do sensorDireita detectar movimento
        if (digitalRead(sensorDireita)) {

          //Se posAtual diferente da posDIREITA
          if (posAtual != posDIREITA) {
            posAtual = posDIREITA;    //Atualize a posAtual para posDIREITA
            tempoAnterior = millis(); //Atualiza o tempo anterior para o tempo atual
          }//if (posAtual != posDIREITA)
        }//if (digitalRead(sensorDireita))
      }//else
    }//else
  }//if ((millis() - tempoAnterior) > tempoDETECT)

//MOVIMENTAÇÃO
  //Se posMovimento menor que a posAtual
  if (posMovimento < posAtual) {
    
    /*Se a diferença do tempo atual [millis()] com o tempoAnteriorMov
      for maior que a diferença entre o tempo escolhido para o delay
      do movimento, faça:*/

    if ((millis() - tempoAnteriorMov) > tempoMOV) {
      /*(Além disso, essa parte do código atual com um 'for' pois é um
        if(condicional) dentro de um laço de repetição(void loop) com
        um iterador(posMovimento))
        
        Obj: fazer com que o movimento do servo seja mais suave*/
        
      posMovimento++;              //Iterador
      motor.write(posMovimento);   //Muda a posição do motor para posMovimento
      tempoAnteriorMov = millis(); //Atualiza o tempo anterior movimento para o tempo atual
    }//if ((millis() - tempoAnteriorMov) > tempoMOV)
  }//if (posMovimento < posAtual)

  //Se posMovimento menor que a posAtual
  if (posMovimento > posAtual) {

    /*Se a diferença do tempo atual [millis()] com o tempoAnteriorMov
      for maior que a diferença entre o tempo escolhido para o delay
      do movimento, faça:*/
    if ((millis() - tempoAnteriorMov) > tempoMOV) {
      
      //Mesmo da parte de cima, mas para o outro sentido
      posMovimento--;            //Iterador
      motor.write(posMovimento); //Muda a posição do motor para posMovimento
    }//if ((millis() - tempoAnteriorMov) > tempoMOV)
  }//if (posMovimento > posAtual)
}//void loop()
