  /*
  * Docente: Marilza Antunes de Lemos
  * Discente: Eduardo Henrique Engel
  * GitHub: https://github.com/EduardoEngel
  * Aula 2 - Conjunto de Motores DC controlado por PWM
  * 27/03/2023
  */

  //Definindo as portas dos motores 
  #define MotorEsqAnt 10
  #define MotorEsqHor 9
  #define MotorDirAnt 6
  #define MotorDirHor 5

  //Definindo as portas dos Potenciometros
  #define PotenciometroEsq A0
  #define PotenciometroDir A1

  //Definindo as variáveis de rotação do motor
  int RotacaoEsq;
  int RotacaoDir;

void setup() {
 
  //Definindo as portas dos motores como saídas
  pinMode(MotorEsqAnt, OUTPUT);		
  pinMode(MotorEsqHor, OUTPUT);	
  pinMode(MotorDirAnt, OUTPUT);	
  pinMode(MotorDirHor, OUTPUT);

  //Definindo as portas dos potenciometros como entradas
  pinMode(PotenciometroEsq, INPUT);
  pinMode(PotenciometroDir, INPUT);

 
  Serial.begin(9600);  //Inicia a comunicação serial para fazer debug no monitor
}
 

void loop() {

  RotacaoEsq = analogRead(PotenciometroEsq);      //Faz a leitura do potenciometro e o define como variável
  RotacaoEsq = map(RotacaoEsq, 0,1023,-255,255);  
  //Restabelece os limites dos valores indicados pelo potenciometro, define os pontos mínimo e máximo como -255 e 255 respectivamente, dessa forma, será mais facil para o motor identificar se a rotação deve ocorrer no sentido horário ou antihorário

  //Realiza a comunicação serial do valor de rotação no motor direito
  Serial.print("RotacaoEsq:\t");
  Serial.println(RotacaoEsq);


  RotacaoDir = analogRead(PotenciometroDir);      //Faz a leitura do potenciometro e o define como variável
  RotacaoDir = map(RotacaoDir, 0,1023,-255,255);
  //Restabelece os limites dos valores indicados pelo potenciometro, define os pontos mínimo e máximo como -255 e 255 respectivamente, dessa forma, será mais facil para o motor identificar se a rotação deve ocorrer no sentido horário ou antihorário

  //Realiza a comunicação serial do valor de rotação no motor direito
  Serial.print("RotacaoDir:\t");
  Serial.println(RotacaoDir);

  //Executa as funções RotacaoDir e RotacaoEsq
  MotorDireito(RotacaoDir);
  MotorEsquerdo(RotacaoEsq);
  
}
  void MotorDireito (int rotacao) {         //Void da Função MotorDir
  if (rotacao > 0 ) {                       //Se a variável rotação for maior que zero...
  analogWrite (MotorDirAnt, rotacao);       //O motor direito funcionará no sentido anti-horário
  digitalWrite (MotorDirHor, LOW);          //A rotação no sentido horário não ocorrerá
  }
  else if (rotacao <0){                     //Se a variável rotação for menor que zero...
  analogWrite (MotorDirHor, rotacao*-1);    //O motor direito funcionará no sentido horário
  digitalWrite (MotorDirAnt, LOW);          //A rotação no sentido anti-horário não ocorrerá
  }
  else {                                    //Se não...
  digitalWrite (MotorDirHor, LOW);          //Ele não rotará no sentido horário
  digitalWrite (MotorDirAnt, LOW);          //Ele não rotará no sentido anti-horário
  }
}

void MotorEsquerdo (int rotacao) {          //Void da Função MotorEsq
  if (rotacao > 0 ) {                       //Se a variável rotação for maior que zero...
  analogWrite (MotorEsqAnt, rotacao);       //O motor esquerdo funcionará no sentido anti-horário
  digitalWrite (MotorEsqHor, LOW);          //A rotação no sentido horário não ocorrerá
  }
  else if (rotacao <0){                     //Se a variável rotação for menor que zero...
  analogWrite (MotorEsqHor, rotacao*-1);    //O motor esquerdo funcionará no sentido horário
  digitalWrite (MotorEsqAnt, LOW);          //A rotação no sentido anti-horário não ocorrerá
  }
  else {                                    //Se não...
  digitalWrite (MotorEsqHor, LOW);          //Ele não rotará no sentido horário
  digitalWrite (MotorEsqAnt, LOW);          //Ele não rotará no sentido anti-horário
  }
}