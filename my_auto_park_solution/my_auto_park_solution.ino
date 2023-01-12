const int trigPin = 33;
const int echoPin = 25;
int angle = 0;
int distance = 999;
long duration;
float distancecm;
int leftspeed, rightspeed, servoAngle;
#include <math.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04
MPU6050 mpu6050(Wire);
Encoder myEncA(3, 11);
Encoder myEncB(2, 12);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Wire.begin();   
 
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT); 

 mpu6050.begin();
 mpu6050.calcGyroOffsets(true);

 encoderCount=30000;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  leftMotor_speed = 255;
  rightMotor_speed = 255;
  servoAngle = 90;
  Transmit_to_arduino(leftspeed, rightspeed, servoAngle);
  delay(encoderCount)

  stopMotors();
  delay(1000)
  Transmit_to_arduino(leftspeed, rightspeed, servoAngle);

  leftspeed=150;
  rightspeed=50;
  servoAngle=100;
  Transmit_to_arduino(leftspeed, rightspeed, servoAngle);
   while (angle > -90) {
    angle = accelerometer();
  }

  stopMotors();
  delay(1000)
  Transmit_to_arduino(leftspeed, rightspeed, servoAngle);
   
   digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;

  goBackwards();

  if (distance_cm <= 30){
    stopMotors();
    delay(100000000000000);
    Transmit_to_arduino(leftspeed, rightspeed, servoAngle);
}

void goForwards() {
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW);
}  

void stopMotors() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, LOW);
  digitalWrite(INc, LOW);
  digitalWrite(INd, LOW);
}

void goBackwards() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, HIGH);
  digitalWrite(INc, LOW);
  digitalWrite(INd, HIGH);
}

void goClockwise() {
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, LOW);
  digitalWrite(INd, HIGH);
}

 
float accelerometer(){
  mpu6050.update();
  return (mpu6050.getAngleZ());
} 

void Transmit_to_arduino(int leftMotor_speed, int rightMotor_speed, int servoAngle){
  Wire.beginTransmission(I2C_SLAVE_ADDR); 
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));   
  Wire.write((byte)(leftMotor_speed & 0x000000FF));          
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));   
  Wire.write((byte)(rightMotor_speed & 0x000000FF));          
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));     
  Wire.write((byte)(servoAngle & 0x000000FF));
  Wire.endTransmission();   
}
}
