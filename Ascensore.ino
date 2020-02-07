#include <Servo.h>
#define LEDV_3 6
#define LEDR_3 7
#define LEDV_2 8
#define LEDR_2 9
#define LEDV_1 10
#define LEDR_1 11
#define LEDPOS_3 12
#define LEDPOS_2 13
#define LEDPOS_1 14
#define PULC_3 15 
#define PULC_2 16
#define PULC_1 17
#define PULA_3 18 
#define PULA_2 19
#define PULA_1 20
#define MOTP_SU 21
#define MOTP_GIU 22
#define SENS_3 23
#define SENS_2 24
#define SENS_1 25
Servo MOT3;
Servo MOT2;
Servo MOT1;
int i;
int currentFloor;

void setup() {
  pinMode(MOTP_SU, OUTPUT);
  pinMode(MOTP_GIU, OUTPUT);
  MOT3.attach(3);
  MOT2.attach(4);
  MOT1.attach(5);
  for(i = 6; i < 15; i++){
    pinMode(i, OUTPUT);
  }
  for(i = 15; i < 21; i++){
    pinMode(i, INPUT);
  }
  doorMan(3, 1);
  doorMan(2, 1);
  doorMan(1, 1);
  do{
    digitalWrite(MOTP_GIU, HIGH);
    if(digitalRead(SENS_1)) currentFloor = 1;
  }while(currentFloor != 1);
  digitalWrite(MOTP_GIU, LOW);
  doorMan(currentFloor, 0);
  Serial.begin(9600);
}

void checkLeds(){
  if(currentFloor == 1){
    digitalWrite(LEDPOS_3, LOW);
    digitalWrite(LEDPOS_2, LOW);
    digitalWrite(LEDPOS_1, HIGH);
    digitalWrite(LEDV_3, LOW);
    digitalWrite(LEDR_3, HIGH);
    digitalWrite(LEDV_2, LOW);
    digitalWrite(LEDR_2, HIGH);
    digitalWrite(LEDV_1, HIGH);
    digitalWrite(LEDR_1, LOW);
  }
  if(currentFloor == 2){
    digitalWrite(LEDPOS_3, LOW);
    digitalWrite(LEDPOS_2, HIGH);
    digitalWrite(LEDPOS_1, LOW);
    digitalWrite(LEDV_3, LOW);
    digitalWrite(LEDR_3, HIGH);
    digitalWrite(LEDV_2, HIGH);
    digitalWrite(LEDR_2, LOW);
    digitalWrite(LEDV_1, LOW);
    digitalWrite(LEDR_1, HIGH);
  }
  if(currentFloor == 3){
    digitalWrite(LEDPOS_3, HIGH);
    digitalWrite(LEDPOS_2, LOW);
    digitalWrite(LEDPOS_1, LOW);
    digitalWrite(LEDV_3, HIGH);
    digitalWrite(LEDR_3, LOW);
    digitalWrite(LEDV_2, LOW);
    digitalWrite(LEDR_2, HIGH);
    digitalWrite(LEDV_1, LOW);
    digitalWrite(LEDR_1, HIGH);
  }
}

void doorMan(int porta, bool chiudere){
  if(porta = 1){
    if(chiudere){
      MOT1.write(180);
      delay(800);
    }
    else{
      MOT1.write(0);
      delay(800);
    }
  }
    if(porta = 2){
    if(chiudere){
      MOT2.write(180);
      delay(800);
    }
    else{
      MOT2.write(0);
      delay(800);
    }
  }
    if(porta = 3){
    if(chiudere){
      MOT3.write(180);
      delay(800);
    }
    else{
      MOT3.write(0);
      delay(800);
    }
  }
}

void gotoFloor(int piano){
  if(piano = 1){
    doorMan(currentFloor, 1);
    do{
      digitalWrite(MOTP_GIU, HIGH);
      if(digitalRead(SENS_1)) currentFloor = 1;
      delay(1);
    }while(currentFloor != 1);
    digitalWrite(MOTP_GIU, LOW);
    doorMan(currentFloor, 0);
  }
   if(piano = 2 && currentFloor == 1){
    doorMan(currentFloor, 1);
    do{
      digitalWrite(MOTP_SU, HIGH);
      if(digitalRead(SENS_2)) currentFloor = 2;
      delay(1);
    }while(currentFloor != 2);
    digitalWrite(MOTP_SU, LOW);
    doorMan(currentFloor, 0);
  }
    if(piano = 2 && currentFloor == 3){
    doorMan(currentFloor, 1);
    do{
      digitalWrite(MOTP_GIU, HIGH);
      if(digitalRead(SENS_2)) currentFloor = 2;
      delay(1);
    }while(currentFloor != 2);
    digitalWrite(MOTP_GIU, LOW);
    doorMan(currentFloor, 0);
  }
    if(piano = 3){
    doorMan(currentFloor, 1);
    do{
      digitalWrite(MOTP_SU, HIGH);
      if(digitalRead(SENS_3)) currentFloor = 3;
      delay(1);
    }while(currentFloor != 3);
    digitalWrite(MOTP_SU, LOW);
    doorMan(currentFloor, 0);
  }
}

void loop() {
  if(digitalRead(digitalRead(PULC_1) || digitalRead(PULA_1) && currentFloor != 1)) gotoFloor(1);
  if(digitalRead(digitalRead(PULC_2) || digitalRead(PULA_2) && currentFloor != 2)) gotoFloor(2);
  if(digitalRead(digitalRead(PULC_3) || digitalRead(PULA_3) && currentFloor != 3)) gotoFloor(3);
  checkLeds();
  delay(1);
}
