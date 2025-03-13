#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include  <RF24_config.h>
#include <SPI.h>   
#include "RF24.h"   
#include <servo.h> 

#define TRIG_PIN 9   // Trigger pin of ultrasonic sensor
#define ECHO_PIN 10  // Echo pin of ultrasonic sensor
#define SAFE_DISTANCE 20  // Distance in cm to trigger brakes

Servo l_brake;
Servo r_brake;
Servo seat;

const  int enbA = 3;
const int enbB = 5;

const int IN1 = 2;   
const int IN2 = 4;   
const int IN3 = 7;    
const int IN4 = 6;   

int RightSpd = 130;
int  LeftSpd = 130;

int data[2];


RF24 radio(9,10);

const uint64_t  pipe = 0xE8E8F0F0E1LL;

void setup(){
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  l_brake.attach(8);
  r_brake.attach(9);
  seat.attach(10);
  releaseBrakes();

  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  radio.begin();                               
  radio.openReadingPipe(1, pipe);
  radio.startListening();             
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;  // Convert time to distance (cm)
  return distance;
}

void loop(){
  if (radio.available()){
    radio.read(data, sizeof(data));

    if(data[0] > 380){           
      analogWrite(enbA,  RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4,  LOW);
    }
    
    if(data[0] < 310){         
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1,  LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4,  HIGH);
    }
     
    if(data[1] > 180){
      analogWrite(enbA,  RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4,  HIGH);
    }

    if(data[1] < 110){
      analogWrite(enbA,  RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4,  LOW);
    }

    if(data[0] > 330 && data[0] < 360 && data[1] > 130 &&  data[1] < 160){
      analogWrite(enbA, 0);
      analogWrite(enbB,  0);
    }
  }

  while(Serial.available() > 0){
    char val = Serial.read();
    if(val == 'a'){
      applyBrakes();
      delay(200);
    }
    if(val == 's'){
      seat_up();
      delay(200);
    }
    if(val == 'r'){
      releaseBrakes();
      delay(200);
    }
    if(val == 'b'){
      brakes();
      delay(200);
    }
  }

}

void brakes(){
  long distance = getDistance();
  if(distance < SAFE_DISTANCE){
    applyBrakes();
  } else {
    releaseBrakes();
  }
}

void applyBrakes() {
  l_brake.write(90);   
  r_brake.write(90);  
}

void releaseBrakes() {
  l_brake.write(0);  
  r_brake.write(0);

void seat_up(){
  seat.write(180);
  delay(1000);
  seat.write(90);
}