// building a smart distance meter 

// define the header file first 
#include<Arduino.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<MPU6050.h>
#include<SimpleKalmanFilter.h>


// define the lcd display 
LiquidCrystal_I2C lcd (0x27,16,2);

// define the echo and trig pin 
const int ECHO_PIN = 3;  //define the echo pin 
const int TRIG_PIN = 2;  //define the trig pin 

// define the buzzer 
const int BUZZER = 13 ; // buzzer pin on 13

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

MPU6050 mpu;

int16_t ax, ay, az; // Accelerometer raw data
int16_t gx, gy, gz; // Gyroscope raw data

float AccX, AccY, AccZ;    // Accelerometer scaled data
float GyroX, GyroY, GyroZ; // Gyroscope scaled data

float roll, pitch, yaw; // Calculated roll and pitch angles

// Define Kalman filter parameters
SimpleKalmanFilter kalmanPitch(2, 2, 0.15); // Q, R, initial estimate
SimpleKalmanFilter kalmanRoll(2, 2, 0.15);  // Q, R, initial estimate
SimpleKalmanFilter kalmanYaw(2, 2, 0.15);   // Q , R , initial estimate

void buzzer_tone(){
    int frequency[] = {200,400,600,800,1000,1200,1400,1600,1800,2000};
    for(int a = 0 ; a<= 10 ; a++){
        tone(BUZZER , frequency[a] , 100);
        delay(100);
    }
    noTone(BUZZER);


    int frequency_two[] = {300,600,900,1200,1500,1800,2100,2400,2700,3000};
    for(int b = 0 ; b<= 10 ; b++){
        tone(BUZZER , frequency_two[b] , 100);
        delay(100);
    }
    noTone(BUZZER);

    for(int c = 0 ; c<= 2 ; c++){
        tone(BUZZER , 300);
        delay(300);
        noTone(BUZZER);

        tone(BUZZER , 1200);
        delay(300);
        noTone(BUZZER);

        tone(BUZZER , 1800);
        delay(300);
        noTone(BUZZER);


    }

    


}




void setup(){
    Serial.begin(9600);

    // define the ultrasonic  sensor 
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


    Wire.begin();
    mpu.initialize();
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);  // Set accelerometer range to +/- 2g
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000); // Set gyroscope range to +/- 2000 degrees/sec

    // define the lcd 
    lcd.init();
    lcd.backlight();
    buzzer_tone();
    lcd.println("PIE.SPACE");
    delay(1000);

}


    


void loop(){

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // Get raw sensor data

    // Convert raw accelerometer data to G's
    AccX = (float)ax / 16384.0;
    AccY = (float)ay / 16384.0;
    AccZ = (float)az / 16384.0;

    // Check if AccY and AccZ are both non-zero to avoid division by zero

    // Convert raw gyroscope data to degrees/second
    GyroX = (float)gx / 131.0;
    GyroY = (float)gy / 131.0;
    GyroZ = (float)gz / 131.0;

    // Calculate roll, pitch, and yaw angles
    // convert the radian to degree = 180/pi
    roll = atan2(AccY, AccZ) * 180.0 / M_PI;
    pitch = atan(-AccX / sqrt(AccY * AccY + AccZ * AccZ)) * 180.0 / M_PI;
    yaw = atan2(-GyroX, sqrt(GyroY * GyroY + GyroZ * GyroZ)) * 180.0 / M_PI;

    // Apply Kalman filter to smooth pitch and roll angles
    pitch = kalmanPitch.updateEstimate(pitch);
    roll = kalmanRoll.updateEstimate(roll);
    yaw = kalmanYaw.updateEstimate(yaw);

    // Print
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" , ");

    Serial.print(" degrees, Pitch: ");
    Serial.print(pitch);
    Serial.print(" , ");

    Serial.print(" yaw : ");
    Serial.println(yaw);


    // define the led 
    if(roll >= 10){
        digitalWrite(led_one , 1);

        if(roll >= 20){
            digitalWrite(led_two , 1);

            if(roll >= 30){
                digitalWrite(led_three , 1);

                if(roll >= 40){
                    digitalWrite(led_four , 1);

                    if(roll >= 50){
                        digitalWrite(led_five , 1);

                        if(roll >= 60){
                            digitalWrite(led_six , 1);

                            if(roll >= 70){
                                digitalWrite(led_seven , 1);

                                if(roll >= 80){
                                    digitalWrite(led_eight , 1);

                                    if(roll >= 90){
                                        digitalWrite(led_nine , 1);
                                    }

                                    else{
                                        digitalWrite(led_nine , 0);
                                    }
                                }

                                else{
                                    digitalWrite(led_eight , 0);
                                }
                            }

                            else{
                                digitalWrite(led_seven , 0);
                            }
                        }

                        else{
                            digitalWrite(led_six , 0);
                        }
                    }

                    else{
                        digitalWrite(led_five , 0);
                    }
                }

                else{
                    digitalWrite(led_four , 0);
                }
            }

            else{
                digitalWrite(led_three , 0);
            }
        }

        else{
            digitalWrite(led_two , 0);
        }


    }
    else{
        digitalWrite(led_one , 0 );
    }

    long duration_ONE, distance_ONE;
  digitalWrite(TRIG_PIN, LOW);  // Ensure the trigger pin is low
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);  // Send a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_ONE = pulseIn(ECHO_PIN, HIGH);  // Measure the pulse
  distance_ONE = duration_ONE * 0.034 / 2;    




    // Serial.println(yaw);
    // print on the display 
    lcd.clear();
    lcd.print("ROLL =");
    lcd.print(roll);
    lcd.println("DEGREE");

    lcd.setCursor(0,1);
    lcd.print("DISTANCE = ");
    lcd.print(distance_ONE);
    lcd.println("CM");

    delay(20);

}

