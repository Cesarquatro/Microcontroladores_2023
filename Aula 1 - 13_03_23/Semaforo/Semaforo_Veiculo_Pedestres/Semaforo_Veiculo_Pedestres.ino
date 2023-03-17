/*
 * Doscente: Marilza Antunes de Lemos
 * Discente: Cesar Augusto Mendes Cordeiro da Silva
 * Aula 1 - Semaforo
 * 13/03/2023
 */

//Definindo as postas dos led do semaforo de veiculos 
#define VVermelho 8 //Led Vermelho Semaforo veiculos
#define VAmarelo 9  //Led Amarelo Semaforo veiculos
#define VVerde 10   //Led Verde Semaforo veiculos

//Definindo as postas dos led do semaforo de pedestres 
#define PVermelho 11 //Led Vermelho Semaforo pedestres
#define PVerde 12    //Led Verde Semaforo pedestres

//Este codigo e dividido em 2 atos (estados)
bool veiculos = false;  //Estado onde o semaforo de veiculos funciona
bool pedestres = false; //Estado onde o semaforo de pedestres funciona
  
void setup(){

  //definindo as portas do arduino como saida
  pinMode(VVermelho, OUTPUT);
  pinMode(VAmarelo, OUTPUT);
  pinMode(VVerde, OUTPUT);
  
  pinMode(PVermelho, OUTPUT);
  pinMode(PVerde, OUTPUT);

  //iniciando a comunicacao serial para utilizar o monitor serial como debug
  Serial.begin(9600);

  //o primeiro ato a funcionar e o dos veiculos, depois eles alternam
  veiculos = true;
}

void loop(){

  //ato dos veiculos
  if(veiculos = true){

    //reset dos leds vermelhos 
    digitalWrite(PVermelho, 1); //Vermelho pedestres ligado
    digitalWrite(VVermelho, 0); //Vermelho veiculos desligado

    //Verde veiculos
    Serial.println("Veiculos\tVerde"); //Print no monitor serial
    digitalWrite(VVerde, 1); //led ligado
    delay(6000);             //delay de 6s
    digitalWrite(VVerde, 0); //led desligado

    //Amarelo veiculos
    Serial.println("Veiculos\tAmarelo"); //Print no monitor serial
    digitalWrite(VAmarelo, 1); //led ligado
    delay(2000);               //delay de 2s
    digitalWrite(VAmarelo, 0); //led desligado

    //Vermelho veiculos
    Serial.println("Veiculos\tVermelho"); //Print no monitor serial
    digitalWrite(VVermelho, 1); //led ligado

    //troca de atos (estados)
    pedestres = true; //Ato pedestres ligado
    veiculos = false; //Ato veiculos desligado
  }

  //ato dos pedestres
  if (pedestres = true){
    //Vermelho pedestres
    digitalWrite(PVermelho, 0); //led desligado

    //Verde pedestres
    Serial.println("Pedestres\tVerde"); //Print no monitor serial
    digitalWrite(PVerde, 1); //led ligado
    delay(5000);             //delay de 5s
    digitalWrite(PVerde, 0); //led desligado

    //Vermelho piscante pedestres
    Serial.println("Pedestres\tVermelho Piscante"); //Print no monitor serial
    //for para o led piscar 10x
    for(int i=0; i<10; i++){
      digitalWrite(PVermelho, 1); //led ligado
      delay(100);                 //delay de 0,1s
      digitalWrite(PVermelho, 0); //led desligado
      delay(100);                 //delay de 0,1s
    }
    //Vermelho pedestres
    Serial.println("Pedestres\tVermelho"); //Print no monitor serial

    //troca de atos (estados)
    pedestres = false; //Ato pedestres desligado
    veiculos = true;   //Ato veiculos ligado
  }
}
