/******************************************************************************
  This is a library for Inertial Measuring Unit

  Project     :   IMU 9 DOF (Acc, Gyro, Magneto)
  Version     :   1
  Date        :   April 16, 2018
  Author      :   Muhammad Adhang
  Email       :   AdhangMuntaha@gmail.com
  Company     :   ELINS UGM
  Comments    :

  Development environment with Arduino IDE 1.8.5

  All text above must be included in any redistribution.
******************************************************************************/
#ifndef _IMU_SENSOR_H_
#define _IMU_SENSOR_H_

#include "I2C.h"

//device address
//#define mpuAddr 0x68        //AD0 (HIGH) = 0x69
#define mpuAddr 0x69
#define tendofAddr 0x68      //jika pake mpu + 10dof, ats_v3, mpu + hmc5883L, ats_v2
#define magAddr 0x1E

//MPU6050 setting
#define gyroRange 0         //gyro range  (0...3 -> +-250, +-500, +-1000, +-2000)
#define accRange 0          //acc range   (0...3 -> +-2g, +-4g, +-8g, +-16g)
#define mpuDLPF 3
#define mpuDHPF 1

//Magneto setting
#define magAveraging 0x03   //averaging 8 (0...3 -> 1,2,4,8)
#define magRate 0x05        //rate 15Mhz  (0...7 -> 0.75, 1.5, 3, 7.5, 15, 30, 75, reserved)
#define magBias 0x00        //normal mode (0...3 -> normal, positive bias, negative bias, reserved
#define magGain 0x06       //gain        (0...7 -> see datasheet) 
#define magMode 0x00        //mode        (0...3 -> continuous, single, idle, idle)

int gyroRaw[3];
int accRaw[3];
int accRawten[3];
int magRaw[3];

float gyroScaled[3];
float accScaled[3];
float accScaledten[3];
float magScaled[3];

//float gyro_scale;
//float acc_scale;
//float mag_scale;

//int gyroOffset[3] = {63, -56, -46};
//int accOffset[3] = { -1828, -1865, 969};

//offset mpu6050 warso
//int gyroOffset[3] = {80, 63, 80};
//int accOffset[3] = { -1803, -1844, 875};

//offset mpu6050 cits
//int gyroOffset[3] = {89, 2, 22};
//int accOffset[3] = { -198, -381, 894};

//offset mpu6050 cits
//int gyroOffset[3] = {90, 2, 23};
//int accOffset[3] = { -23, -406, 881};

//offset mpu6050 cits 2
//int gyroOffset[3] = {96, -44, -5};
//int accOffset[3] = { -519, 2801, 885};

//offset mpu6050 cits nov 29 2018 (imu ATS yang dipake)nilai nya aga jelek, kalibrasi lagi
//int gyroOffset[3] = {-9, 146, 4};
//int accOffset[3] = { -844, 2754, 1614};

//offset mpu6050 kosan mei 15 2019 (imu ATS cadangan) nilai nya halus banget
//int gyroOffset[3] = {102, -41, -18};
//int accOffset[3] = { -249, 2634, 827};

//offset mpu6050 kosan mei 15 2019
//int gyroOffset[3] = {-12, 134, 3};
//int accOffset[3] = { -575, 2823, 1623};

//offset mpu6050 N47 july 21 2019 mpu6050 6dof UTAMA
int gyroOffsetmpu[3] = { -156, -18, -2};
int accOffsetmpu[3] = { -2668, -1388, 1549};
//int magOffset[3] = {0, 0, 0}; yang HMC5883l


//offset 10DOF
int gyroOffset10dof[3] = {60, -43, -16};
int accOffset10dof[3] = { -4372, 8, 1393};

//untuk AHRS nomor 1
float mag_offset[3]            = {29,-157,-5}; //-5.68, -64.30, -35.88
float mag_softiron_matrix[3][3] = {{1.017, 0.000, -0.148},
                                   {0.000, 1.111, 0.011},
                                   {-0.148, 0.011, 0.907}};
float mag_field_strength        = 54.70;

////untuk AHRS nomor 2
//float mag_offset[3]            = {-16.90, -61.58, -30.64};
//float mag_softiron_matrix[3][3] = {{0.940, 0.009, -0.085},
//                                  {0.009, 0.999, -0.007},
//                                  {-0.085, -0.007, 1.072}};
//float mag_field_strength        = 51.07;
//
////untuk AHRS nomor 3
//float mag_offset[3]            = {-23.15, -69.22, -37.49};
//float mag_softiron_matrix[3][3] = {{0.997, -0.033, -0.146},
//                                  {-0.033, 1.160, 0.001},
//                                  {-0.146, 0.001, 0.887}};
//float mag_field_strength        = 53.53;

float declinationAngle = 0.8833333 * DEG_TO_RAD; //home
float heading;
float hheading;
float roll, pitch, yaw;

unsigned long timeGyro = 0;
double kalAngleX, kalAngleY, Vangle;

class MPU6050
{
  private:
    byte buffer[6];
    float gyro_scale;
    float acc_scale;
    int rawAcc[3];
    int rawGyro[3];

  public:
    void initialize() {
      writeBit(mpuAddr, 0x6B, 6, 0);              //disable sleep mode (wake up)
      writeByte(mpuAddr, 0x19, 4);                //set SMPLRT_DIV = 4 (sample rate = 200Hz)
      writeBits(mpuAddr, 0x1B, 4, 2, gyroRange);  //set full scale gyro range
      writeBits(mpuAddr, 0x1C, 4, 2, accRange);   //set full scale acc range
      writeBits(mpuAddr, 0x1A, 2, 3, mpuDLPF);
      writeBits(mpuAddr, 0x1C, 2, 3, mpuDHPF);

      setOffsetAcc(accOffsetmpu);
      setOffsetGyro(gyroOffsetmpu);

      switch (gyroRange)
      {
        case 0: gyro_scale = 131.0; break;
        case 1: gyro_scale = 65.5; break;
        case 2: gyro_scale = 32.8; break;
        case 3: gyro_scale = 16.4; break;
        default: gyro_scale = 131.0; writeBits(mpuAddr, 0x1B, 4, 2, 0); break;//gyroRange = 0;
      }

      switch (accRange)
      {
        case 0: acc_scale = 16384.0; break;
        case 1: acc_scale = 8192.0; break;
        case 2: acc_scale = 4096.0; break;
        case 3: acc_scale = 2048.0; break;
        default: acc_scale = 16384.0; writeBits(mpuAddr, 0x1C, 4, 2, 0); break;//accRange = 0;
      }
      delay(100);
    }

    void setOffsetAcc(int data[])
    {
      setOffsetAX(data[0]);
      setOffsetAY(data[1]);
      setOffsetAZ(data[2]);
      //      writeByte(mpuAddr, 0x06, data[0] >> 8);
      //      writeByte(mpuAddr, 0x07, data[0]);
      //      writeByte(mpuAddr, 0x08, data[1] >> 8);
      //      writeByte(mpuAddr, 0x09, data[1]);
      //      writeByte(mpuAddr, 0x0A, data[2] >> 8);
      //      writeByte(mpuAddr, 0x0B, data[2]);
    }

    void setOffsetGyro(int data[])
    {
      setOffsetGX(data[0]);
      setOffsetGY(data[1]);
      setOffsetGZ(data[2]);
      //      writeByte(mpuAddr, 0x13, data[0] >> 8);
      //      writeByte(mpuAddr, 0x14, data[0]);
      //      writeByte(mpuAddr, 0x15, data[1] >> 8);
      //      writeByte(mpuAddr, 0x16, data[1]);
      //      writeByte(mpuAddr, 0x17, data[2] >> 8);
      //      writeByte(mpuAddr, 0x18, data[2]);
    }

    void setOffsetAX(int data) {
      writeByte(mpuAddr, 0x06, data >> 8);
      writeByte(mpuAddr, 0x07, data);
    }

    void setOffsetAY(int data) {
      writeByte(mpuAddr, 0x08, data >> 8);
      writeByte(mpuAddr, 0x09, data);
    }

    void setOffsetAZ(int data) {
      writeByte(mpuAddr, 0x0A, data >> 8);
      writeByte(mpuAddr, 0x0B, data);
    }

    void setOffsetGX(int data) {
      writeByte(mpuAddr, 0x13, data >> 8);
      writeByte(mpuAddr, 0x14, data);
    }

    void setOffsetGY(int data) {
      writeByte(mpuAddr, 0x15, data >> 8);
      writeByte(mpuAddr, 0x16, data);
    }

    void setOffsetGZ(int data) {
      writeByte(mpuAddr, 0x17, data >> 8);
      writeByte(mpuAddr, 0x18, data);
    }

    void getAccRaw(int data[]) {
      readBytes(mpuAddr, 0x3B, 6, buffer);
      data[0] = (int16_t)(buffer[0] << 8) | buffer[1];
      data[1] = (int16_t)(buffer[2] << 8) | buffer[3];
      data[2] = (int16_t)(buffer[4] << 8) | buffer[5];
      delay(1);
    }

    void getGyroRaw(int data[]) {
      readBytes(mpuAddr, 0x43, 6, buffer);
      data[0] = (int16_t)(buffer[0] << 8) | buffer[1];
      data[1] = (int16_t)(buffer[2] << 8) | buffer[3];
      data[2] = (int16_t)(buffer[4] << 8) | buffer[5];
      delay(1);
    }

    void getAccScaled(float data[]) {
      int temp[3];
      getAccRaw(temp);
      data[0] = (float)(temp[0] - accOffsetmpu[0]) / acc_scale;
      data[1] = (float)(temp[1] - accOffsetmpu[1]) / acc_scale;
      data[2] = (float)(temp[2] - accOffsetmpu[2]) / acc_scale;
    }

    void getGyroScaled(float data[]) {
      int temp[3];
      getGyroRaw(temp);
      data[0] = (float)(temp[0] - gyroOffsetmpu[0]) / gyro_scale;
      data[1] = (float)(temp[1] - gyroOffsetmpu[1]) / gyro_scale;
      data[2] = (float)(temp[2] - gyroOffsetmpu[2]) / gyro_scale;
    }

    int getOffsetAcc(int data[]) {
      readBytes(mpuAddr, 0x06, 6, buffer);
      data[0] = (buffer[0] << 8) | buffer[1];
      data[1] = (buffer[2] << 8) | buffer[3];
      data[2] = (buffer[4] << 8) | buffer[5];
    }

    int getOffsetGyro(int data[]) {
      readBytes(mpuAddr, 0x13, 6, buffer);
      data[0] = (buffer[0] << 8) | buffer[1];
      data[1] = (buffer[2] << 8) | buffer[3];
      data[2] = (buffer[4] << 8) | buffer[5];
    }

    float getPitch(int data[]) {
      return atan2((float) -data[0], sqrt(((float)data[2] * data[2]) + ((float)data[1] * data[1]))) * RAD_TO_DEG;
    }

    float getRoll(int data[]) {
      return atan2((float)data[1], sqrt(((float)data[2] * data[2]) + ((float)data[0] * data[0]))) * RAD_TO_DEG;
    }

    float getPitch(float data[]) {
      return atan2(-data[0], sqrt((data[2] * data[2]) + (data[1] * data[1]))) * RAD_TO_DEG;
    }

    float getRoll(float data[]) {
      return atan2(data[1], sqrt((data[2] * data[2]) + (data[0] * data[0]))) * RAD_TO_DEG;
    }
};

class Magnetometer
{
  private:
    byte buffer[6];
    float mag_scale;
  public:
    void initialize() {
      //khusus untuk yang 6DOF++ (acc, gyro, mag), tapi gak masalah sekalian ditulis
      writeBit(tendofAddr, 0x6A, 5, false);   //setI2CMasterModeEnabled(false);
      writeBit(tendofAddr, 0x37, 1, true);    //setI2CBypassEnabled(true);
      writeBit(tendofAddr, 0x6B, 6, false);   //setSleepEnabled(false);

      writeByte(magAddr, 0x00, ((magAveraging << 5) | (magRate << 2) | (magBias)));
      writeByte(magAddr, 0x01, magGain << 5);
      writeByte(magAddr, 0x02, magMode);

      switch (magGain)
      {
        case 0: mag_scale = 0.73; break;
        case 1: mag_scale = 0.92; break;
        case 2: mag_scale = 1.22; break;
        case 3: mag_scale = 1.52; break;
        case 4: mag_scale = 2.27; break;
        case 5: mag_scale = 2.56; break;
        case 6: mag_scale = 3.03; break;
        case 7: mag_scale = 4.35; break;
        default: mag_scale = 0.92; writeByte(magAddr, 0x01, 1 << 5);  break;
      }
      delay(100);
    }

    void readMagRaw(int data[]) {
      readBytes(magAddr, 0x03, 6, buffer);
      if (magMode == 1)                //if it's single measurement mode
        writeByte(magAddr, 0x02, magMode);
      data[0] = (int16_t)(buffer[0] << 8) | buffer[1];
      data[1] = (int16_t)(buffer[4] << 8) | buffer[5];
      data[2] = (int16_t)(buffer[2] << 8) | buffer[3];
      delay(1);
    }

    void readMagScaled(float data[]) {
      int temp[3];
      float x, y, z;
      readMagRaw(temp);
//      data[0] = ((float)temp[0] - mag_offset[0]) * mag_scale;    //versi standar      
//      data[1] = ((float)temp[1] - mag_offset[1]) * mag_scale;
//      data[2] = ((float)temp[2] - mag_offset[2]) * mag_scale;

      x = (float)temp[0] * mag_scale - mag_offset[0];            //versi AHRS
      y = (float)temp[1] * mag_scale - mag_offset[1];
      z = (float)temp[2] * mag_scale - mag_offset[2];

      data[0] = x * mag_softiron_matrix[0][0] + y * mag_softiron_matrix[0][1] + z * mag_softiron_matrix[0][2];
      data[1] = x * mag_softiron_matrix[1][0] + y * mag_softiron_matrix[1][1] + z * mag_softiron_matrix[1][2];
      data[2] = x * mag_softiron_matrix[2][0] + y * mag_softiron_matrix[2][1] + z * mag_softiron_matrix[2][2];

    }

    float getHeading(float mx, float my) {
      float heading = atan2(my, mx);
      heading += declinationAngle;

      if (heading < 0)
        heading += 2 * M_PI;
      heading *= RAD_TO_DEG;
      return heading;
    }
};

class TENDOF
{
  private:
    byte buffer[6];
    float acc_scale;
    int rawAcc[3];

  public:
    void initialize() {
      writeBit(tendofAddr, 0x6B, 6, 0);              //disable sleep mode (wake up)
      writeByte(tendofAddr, 0x19, 4);                //set SMPLRT_DIV = 4 (sample rate = 200Hz)
      writeBits(tendofAddr, 0x1C, 4, 2, accRange);   //set full scale acc range
      writeBits(tendofAddr, 0x1A, 2, 3, mpuDLPF);
      writeBits(tendofAddr, 0x1C, 2, 3, mpuDHPF);

      setOffsetAcc(accOffset10dof);

      switch (accRange)
      {
        case 0: acc_scale = 16384.0; break;
        case 1: acc_scale = 8192.0; break;
        case 2: acc_scale = 4096.0; break;
        case 3: acc_scale = 2048.0; break;
        default: acc_scale = 16384.0; writeBits(tendofAddr, 0x1C, 4, 2, 0); break;//accRange = 0;
      }
      delay(100);
    }

    void setOffsetAcc(int data[])
    {
      setOffsetAX(data[0]);
      setOffsetAY(data[1]);
      setOffsetAZ(data[2]);
      //      writeByte(10dofAddr, 0x06, data[0] >> 8);
      //      writeByte(10dofAddr, 0x07, data[0]);
      //      writeByte(10dofAddr, 0x08, data[1] >> 8);
      //      writeByte(10dofAddr, 0x09, data[1]);
      //      writeByte(10dofAddr, 0x0A, data[2] >> 8);
      //      writeByte(10dofAddr, 0x0B, data[2]);
    }

    void setOffsetAX(int data) {
      writeByte(tendofAddr, 0x06, data >> 8);
      writeByte(tendofAddr, 0x07, data);
    }

    void setOffsetAY(int data) {
      writeByte(tendofAddr, 0x08, data >> 8);
      writeByte(tendofAddr, 0x09, data);
    }

    void setOffsetAZ(int data) {
      writeByte(tendofAddr, 0x0A, data >> 8);
      writeByte(tendofAddr, 0x0B, data);
    }

    void getAccRaw(int data[]) {
      readBytes(tendofAddr, 0x3B, 6, buffer);
      data[0] = (int16_t)(buffer[0] << 8) | buffer[1];
      data[1] = (int16_t)(buffer[2] << 8) | buffer[3];
      data[2] = (int16_t)(buffer[4] << 8) | buffer[5];
      delay(1);
    }

    void getAccScaled(float data[]) {
      int temp[3];
      getAccRaw(temp);
      data[0] = (float)(temp[0] - accOffset10dof[0]) / acc_scale;
      data[1] = (float)(temp[1] - accOffset10dof[1]) / acc_scale;
      data[2] = (float)(temp[2] - accOffset10dof[2]) / acc_scale;
    }

    int getOffsetAcc(int data[]) {
      readBytes(tendofAddr, 0x06, 6, buffer);
      data[0] = (buffer[0] << 8) | buffer[1];
      data[1] = (buffer[2] << 8) | buffer[3];
      data[2] = (buffer[4] << 8) | buffer[5];
    }

    float getPitch(int data[]) {
      return atan2((float) -data[0], sqrt(((float)data[2] * data[2]) + ((float)data[1] * data[1]))) * RAD_TO_DEG;
    }

    float getRoll(int data[]) {
      return atan2((float)data[1], sqrt(((float)data[2] * data[2]) + ((float)data[0] * data[0]))) * RAD_TO_DEG;
    }

    float getPitch(float data[]) {
      return atan2(-data[0], sqrt((data[2] * data[2]) + (data[1] * data[1]))) * RAD_TO_DEG;
    }

    float getRoll(float data[]) {
      return atan2(data[1], sqrt((data[2] * data[2]) + (data[0] * data[0]))) * RAD_TO_DEG;
    }
};

#endif _IMU_SENSOR_H_
