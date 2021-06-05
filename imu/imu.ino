#include "Sensor.h"

MPU6050 mpu;
Magnetometer mag;
TENDOF dof10;

void setup(){
  Serial.begin(57600);
  Wire.begin();
  Wire.setClock(400000);
  delay(100);
  mpu.initialize();
  mag.initialize();
  dof10.initialize();
  delay(100);
}

void loop(){
  reading_sensor();
}

void reading_sensor(){
  float fdata[3];   // temporary data holder

  mpu.getAccScaled(fdata);
  Serial.println("MPU6050 reading:");
  Serial.println("roll angle: " + String(mpu.getRoll(fdata)) + " deg");
  Serial.println("pitch angle: " + String(mpu.getPitch(fdata)) + " deg");

  mag.readMagScaled(fdata);
  Serial.println("Magnetometer reading:");
  Serial.println("heading: " + String(mag.getHeading(fdata[0], fdata[1])) + " deg");

  dof10.getAccScaled(fdata);
  Serial.println("10-DOF reading:");
  Serial.println("roll angle: " + String(dof10.getRoll(fdata)) + " deg");
  Serial.println("pitch angle: " + String(dof10.getPitch(fdata)) + " deg");

  delay(100);
}
