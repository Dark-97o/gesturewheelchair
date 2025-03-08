#include <SPI.h>       
#include  "RF24.h"     
#include "Wire.h"      
#include "I2Cdev.h"    
#include  "MPU6050.h"    

MPU6050 mpu;
int16_t  ax, ay, az;
int16_t gx, gy, gz;
int data[2];

RF24 radio(9,10);
                                    
const uint64_t pipe = 0xE8E8F0F0E1LL;

void  setup(void){
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();            
  radio.begin();                 
  radio.openWritingPipe(pipe);   
}

void loop(void){
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

 
  data[0] = map(ax,  -17000, 17000, 300, 400 );
  data[1] = map(ay, -17000, 17000,  100, 200); 
  radio.write(data, sizeof(data));
}