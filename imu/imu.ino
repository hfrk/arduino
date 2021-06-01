#include "Sensor.h"

MPU6050 mpu;
Magnetometer mag;

void setup(){
    Serial.begin(57600);
    Wire.begin();
    Wire.setClock(400000);
    delay(100);
    mpu.initialize();
    mag.initialize();
    delay(100);
}

void loop(){
    reading_sensor();
}

void reading_sensor(){
    float fdata[3];
  
    mpu.getAccScaled(fdata);
    roll = mpu.getRoll(fdata);		// roll angle
    pitch = mpu.getPitch(fdata);	// pitch angle
      
  	mag.readMagScaled(fdata);
  	heading = mag.getHeading(fdata[0], fdata[1]);	// heading mag
  
  	Serial.println("roll angle: " + String(roll) + " deg");
  	Serial.println("pitch angle: " + String(pitch) + " deg");
  	Serial.println("heading: " + String(heading) + " deg");
    delay(100);
}
