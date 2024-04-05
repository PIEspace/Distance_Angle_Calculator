// Connect the ultrasonic sensor with Arduino mega . 

#include<Arduino.h>

//define the first ultrasonic sensor 
const int trigPin_ONE = 2;  // The trig pin is connected to pin number 22.
const int echoPin_ONE = 3;  // The echo pin is connected to pin number 24.



void setup() {
  Serial.begin(9600);

  // define the first ultrasonic sensor pinMode 
  pinMode(trigPin_ONE, OUTPUT);
  pinMode(echoPin_ONE, INPUT);
  

}

void loop() {

  
  long duration_ONE, distance_ONE;
  digitalWrite(trigPin_ONE, LOW);  // Ensure the trigger pin is low
  delayMicroseconds(2);

  digitalWrite(trigPin_ONE, HIGH);  // Send a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trigPin_ONE, LOW);

  duration_ONE = pulseIn(echoPin_ONE, HIGH);  // Measure the pulse
  distance_ONE = duration_ONE * 0.034 / 2;    // Calculate distance in cm


  
  

  // print on the serial monitor 

  Serial.print("Distance_ONE : ");
  Serial.print(distance_ONE);
  Serial.print(" cm");
  Serial.print(" , ");

  
  delay(100);
}