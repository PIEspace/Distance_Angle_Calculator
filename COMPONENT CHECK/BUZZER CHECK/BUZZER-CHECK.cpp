// check the buzzer 

#include<Arduino.h>

// define the buzzer 
const int buzzer = 13;

void setup(){
    // define the bud rate 
    Serial.begin(9600);

    // define the pinMode
    pinMode(buzzer , OUTPUT);
}

void loop(){

    digitalWrite(buzzer , 1);
    delay(1000);

    digitalWrite(buzzer , 0);
    delay(1000);

}