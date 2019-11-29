#include <RH_ASK.h>
#include <SPI.h>
#define HOME 12
#define GROUND 11
RH_ASK driver;

void setup()
{
    pinMode(HOME, OUTPUT);
    pinMode(GROUND, OUTPUT);
    Serial.begin(9600);  
    if (!driver.init())
         Serial.println("init failed");
}

void loop(){
    uint8_t buf[6];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) 
    {
      int i;  
      if((char*)buf == "HOME"){
          digitalWrite(HOME, HIGH);
          delay(500);
          digitalWrite(HOME, LOW);
        }
      if((char*)buf == "GROUND"){
          digitalWrite(GROUND, HIGH);
          delay(500);
          digitalWrite(GROUND, LOW);
        }         
    }
}
