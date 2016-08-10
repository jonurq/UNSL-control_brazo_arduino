#include <Servo.h> 

byte mensaje[6];

Servo servoA1; //servo A ; esta instrucción crea un objeto servo para controlar el servomotor;
Servo servoA2; //servo A
Servo servoB; //servo B
Servo servoC;  //servo C
Servo servoD;  //servo D
Servo servoE;  //servo E
Servo servoF;  //servo F
Servo servoG;  //servo G (Pinza)


  byte posA_ant;
  byte posB_ant;
  byte posC_ant;
  byte posD_ant;
  byte posE_ant;
  byte posF_ant;
  byte posG_ant;


void setup() {
  Serial.begin(9600);
  Serial3.begin(38400);   // El modulo bluetooth fue configurado para trabajar a 38400 baudios
  
  // Asignamos los servos a sus respectivos pines
  servoA1.attach(9);
  servoA2.attach(8);  
  servoB.attach(7);  
  servoC.attach(6);   
  servoD.attach(5);   
  servoE.attach(4);
  servoF.attach(3);  
  servoG.attach(2);   



  servoA1.write(180); //90-180 Defecto 180
  servoA2.write(0); //0-90 Defecto 0
  servoB.write(95); // 55 - 95 Defecto 95
  servoC.write(130); // 35 - 130 Defecto 130
  servoD.write(80); //20-140 Defecto 80
  servoE.write(75); // 5-145 Defecto 75
  servoF.write(85); //5- 165 Defecto 85
  servoG.write(70); //0-75 Abierto - Cerrado Def 70


  //variables para almacenar la posicion anterior
  posA_ant =90;
  posB_ant = 95;
  posC_ant = 130;
  posD_ant=80;
  posE_ant=75;
  posF_ant=85;
  posG_ant=70;
  delay(2000);
}

//Funcion que decodifica el mensaje recibido mediante bluetooth y mueve los servos
void MoverServo(byte mensaje[]){
  byte posA=mensaje[0];
  byte posB=mensaje[1];
  byte posD=mensaje[2];
  byte posE=mensaje[3];
  byte posF=mensaje[4];
  byte posG=mensaje[5];

  
//Si es distinta la posicion actual a la anterior, escribo la nueva posicion
    if(posA!=posA_ant){
      if(posA<=90){
              servoA1.write(posA + 90); //90-180 Def 180
              servoA2.write(0); //0-90 Def 0
            }
            else{
              servoA1.write(180); //90-180 Def 180
              servoA2.write(posA-90); //0-90 Def 0
            }
       posA_ant=posA;//Guardo la poscion actual como anterior
    }
    if(posB_ant!=posB){
      if(posB>=95){
              servoB.write(posB-40); 
              servoC.write(130); 
            }
            else{
              servoB.write(55); 
              servoC.write(posB+40); 
            }
      posB_ant=posB;
    }
    
    if(posD_ant!=posD){
      servoD.write(posD);
      posD_ant=posD;
    } 
    if(posE_ant!=posE){
      servoE.write(posE); 
      posE_ant=posE;
      }
    if(posF_ant!=posF){
      servoF.write(posF); 
      posF_ant=posF;
    }
    if(posG_ant!=posG){
      servoG.write(posG); 
      posG_ant=posG;
    }

}

void loop() {


if (Serial3.available()) {//Si hay datos en el puerto serie3 (Bluetooth)
  Serial3.readBytes(mensaje,6);
    
    MoverServo(mensaje); //Mando el mensaje a la función mover servo
    
  }

}
