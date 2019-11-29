#include <RH_ASK.h>
#include <SPI.h>
#define TRIG 6
#define ECHO 5
#define BUZZER 13
#define MOTOR 10
#define BUTHOME 9
#define BUTGROUND 8
long durata;
long dist;
long distanza;
long newdistanza;
int i;
RH_ASK driver;

void setup() {
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  Serial.begin(9600);
  if (!driver.init()) Serial.println("init failed");
}

long checkDistanza(){
  digitalWrite(TRIG, LOW);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  durata = pulseIn(ECHO, HIGH);
  dist = 0.034 * durata / 2;
  return dist;
}

void sendHome(){
    const char *msgH = "GOHOME";
    driver.send((uint8_t *)msgH, strlen(msgH));
    driver.waitPacketSent();
    
}

void sendGround(){
    const char *msgG = "GROUND";
    driver.send((uint8_t *)msgG, strlen(msgG));
    driver.waitPacketSent();
    
}

void loop() {
  distanza = checkDistanza();
  Serial.println(distanza);
  for(i = 0; i < distanza; i++){
    newdistanza = checkDistanza();
    if((newdistanza - 3) > distanza || (newdistanza + 3) < distanza) break;
    if(distanza < 40 ) digitalWrite(MOTOR, HIGH);
    else digitalWrite(MOTOR, LOW);
    if(digitalRead(BUTHOME)) sendHome();
    if(digitalRead(BUTGROUND)) sendGround();
    delay(1);
  }
  tone(BUZZER, 500, 70);
  delay(70);
  noTone(BUZZER);
}
