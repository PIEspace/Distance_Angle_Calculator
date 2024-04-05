// CHECK THE LED 

#include<Arduino.h>

// digital pin connect 4 to 12
const int led_one = 4;  
const int led_two = 5;
const int led_three = 6;
const int led_four = 7;
const int led_five = 8;
const int led_six = 9;
const int led_seven = 10;
const int led_eight = 11;
const int led_nine = 12;



void setup(){

    
    // define the led output pin 
    pinMode(led_one , OUTPUT);
    pinMode(led_two , OUTPUT);
    pinMode(led_three , OUTPUT);
    pinMode(led_four , OUTPUT);
    pinMode(led_five , OUTPUT);
    pinMode(led_six , OUTPUT);
    pinMode(led_seven , OUTPUT);
    pinMode(led_eight , OUTPUT);
    pinMode(led_nine , OUTPUT);

}

void loop(){

    digitalWrite(led_one , 1);
    digitalWrite(led_two , 1);
    digitalWrite(led_three , 1);
    digitalWrite(led_four , 1);
    digitalWrite(led_five , 1);
    digitalWrite(led_six , 1);
    digitalWrite(led_seven , 1);
    digitalWrite(led_eight , 1);
    digitalWrite(led_nine , 1);

    delay(1000);


    digitalWrite(led_one , 0);
    digitalWrite(led_two , 0);
    digitalWrite(led_three , 0);
    digitalWrite(led_four , 0);
    digitalWrite(led_five , 0);
    digitalWrite(led_six , 0);
    digitalWrite(led_seven , 0);
    digitalWrite(led_eight , 0);
    digitalWrite(led_nine , 0);

    delay(1000);



}