// building a smart distance meter 

// define the hearder file first 
#include<Arduino.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_MPU6050.h>


LiquidCrystal_I2C lcd (0x27,16,2);
Adafruit_MPU6050 mpu;


// define the echo and trig pin 
const int ECHO_PIN = 3;  //define the echo pin 
const int TRIG_PIN = 2;  //define the trig pin 

// define the buzzer 
const int BUZZER = 13 ; // buzzer pin on GPIO 13

const long ultrosonic_delay = 2000;
const long delay_two = 2000;

// DEFINE THE led 
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


unsigned long first_previoustime =0;
const long first_milli_delay = 100;


void setup(){
    Serial.begin(9600);

    // define the ultroonic sensor 
    pinMode(ECHO_PIN , INPUT);
    pinMode(TRIG_PIN , OUTPUT);
    pinMode(BUZZER , OUTPUT);
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


    // inilize the display
    lcd.init();
    lcd.backlight();

    welcome_logo(); //define the welcome logo
    welcome_buzzer(); //define the welcome buzzer 
    delay(2000); //delay for 5 second 
    lcd.clear();

    // check the ultrosonic
    check_ultrosonic();
    delay(delay_two);
    lcd.clear();
    ultrosonic_check_value();
    delay(ultrosonic_delay);
    lcd.clear();

    // mpu6050 check 
    mpu_6050_display_name();
    delay(2000) ; //delay for 2 second 
    lcd.clear();


    // define the mpu6050 sensor 
    while(!Serial)
    delay(10);
    if(!mpu.begin()){
        Serial.println("not connect mpu6050 sensor please check the sensor ");
        while(true);
    }


}

void loop(){


    // display function 
    distance_check_in_cm();
    mpu6050_angle_measure();

}

void welcome_logo(){
    lcd.setCursor(4,0);
    lcd.print("WELCOME");
    lcd.setCursor(4,1);
    lcd.print("PIE.SPACE");
}


void check_ultrosonic(){
    lcd.setCursor(0,0);
    lcd.print("ULTRASONIC CHECK");
}


void ultrosonic_check_value(){
    digitalWrite(TRIG_PIN , LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN , HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN , LOW);

//    hight the echo pin 
    float duration = pulseIn(ECHO_PIN , HIGH);
    // find the distnace 
    float distance = duration/58.2;

    lcd.setCursor(0,0);
    lcd.print("Distance:");
    lcd.print(distance);
    lcd.print("CM");
}

void distance_check_in_cm(){
    digitalWrite(TRIG_PIN , LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN , HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN , LOW);

//    hight the echo pin 
    float duration = pulseIn(ECHO_PIN , HIGH);
    // find the distnace 
    float distance = duration/58.2;

    // print on the lcd
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.print(distance);
    lcd.print("CM");

    if(distance<=10){
        digitalWrite(BUZZER , HIGH);
    }
    else{
        digitalWrite(BUZZER , LOW);
    }





}

void welcome_buzzer(){

    for (int welcome_buzzer = 0; welcome_buzzer <= 4; welcome_buzzer++)
    {
    tone(BUZZER , 120);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 220);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 320);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 420);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 520);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 120);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 220);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 320);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 420);
    delay(100);
    noTone(BUZZER);
    tone(BUZZER , 520);
    delay(100);
    noTone(BUZZER);

    }
}

void mpu6050_angle_measure(){

    unsigned long first_currenttime = millis();
    if(first_currenttime - first_previoustime >=first_milli_delay){
        first_previoustime = first_currenttime;

    
    sensors_event_t a ,g,temp;
    mpu.getEvent(&a,&g,&temp);

    float acclerationX = a.acceleration.x;
    float acclerationY = a.acceleration.y;
    float acclerationZ = a.acceleration.z;

    // define the roll
    float ROLL = atan2(acclerationY , acclerationZ)*180.0/PI;
    // define the pitch 
    float PITCH = atan(-acclerationX/sqrt(acclerationY*acclerationY+acclerationZ*acclerationZ))*180.0/PI;

    // print on the lcd
    lcd.setCursor(0,0);
    lcd.print("ANGLE:");
    lcd.print(ROLL);

    if(ROLL <= 10){
        digitalWrite(led_one , HIGH);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);

    }
    else if( ROLL <= 20){
         digitalWrite(led_one , LOW);
        digitalWrite(led_two , HIGH);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);

    }

    else if (ROLL <=30 ){
        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , HIGH);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);
        

    }
    else if(ROLL <=40){
        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , HIGH);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);

    }
    else if(ROLL <= 50){
        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , HIGH);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);


    }
    else if(ROLL <=60){
        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , HIGH);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);
    }
    else if(ROLL <= 70){
        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , HIGH);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);
    }
    else if(ROLL <= 80){
        digitalWrite(led_one , LOW);;
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , HIGH);
        digitalWrite(led_nine , LOW);
    }
    else if(ROLL <= 90){
        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , HIGH);
    }

    else{


        digitalWrite(led_one , LOW);
        digitalWrite(led_two , LOW);
        digitalWrite(led_three , LOW);
        digitalWrite(led_four , LOW);
        digitalWrite(led_five , LOW);
        digitalWrite(led_six , LOW);
        digitalWrite(led_seven , LOW);
        digitalWrite(led_eight , LOW);
        digitalWrite(led_nine , LOW);

    }

    }
    
}

void mpu_6050_display_name(){
    lcd.setCursor(0,0);
    lcd.print("CHeck mpu6050");

}

