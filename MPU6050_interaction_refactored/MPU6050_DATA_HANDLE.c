#ifndef MPU6050_DATA_HANDLE_INCLUDE_FLAG
#define MPU6050_DATA_HANDLE_INCLUDE_FLAG
#include "MPU6050_DATA_HANDLE.h"

void init_MPU6050() {
  Wire.begin();
  
  // MPU6050 디바이스 리셋 후 깨우기
  Wire.beginTransmission(MPU6050_SENSOR_ADDRESS); 
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(); 

  // MPU6050의 '원시 데이터 값 범위' 설정하기 (기본값 250도)
  Wire.beginTransmission(MPU6050_SENSOR_ADDRESS);
  Wire.write(MPU6050_VALUE_RANGE_SETTING_REGISTER);
  Wire.write(MPU6050_VALUE_RANGE_SETTING); 
  Wire.endTransmission();

  // MPU6050에서 '원시 데이터 값 범위' 데이터 읽어오기
  Wire.requestFrom(MPU6050_SENSOR_ADDRESS, 1);
  byte value_range_config = Wire.read();

  switch(value_range_config & 0x18) {
    case 0x00: MPU6050_VALUE_RANGE =  250;  break;
    case 0x08: MPU6050_VALUE_RANGE =  500;  break;
    case 0x10: MPU6050_VALUE_RANGE = 1000;  break;
    case 0x18: MPU6050_VALUE_RANGE = 2000;  break;
      default: MPU6050_VALUE_RANGE =   -1;  break;
  }

  Serial.print("-- CONFIGURED 'VALUE RANGE CONVERTING CONSTANT' :: "); Serial.print(MPU6050_VALUE_RANGE); Serial.println(" --");
}

void parse_sensor_data(MPU6050_SENSOR_DATA* output) {
  /*
   * parse_sensor_data
   * @PARAM
   * MPU6050_SENSOR_DATA* output : 센서에서 받아들인 원시 데이터를 가공한 가속도 데이터와 각속도 데이터를 담는 구조체 포인터
   *                             - 값을 이곳에 저장함
   * 
   */ 
  Wire.beginTransmission(MPU6050_SENSOR_ADDRESS);

  int16_t acc_x, acc_y, acc_z, gyr_x, gyr_y, gyr_z;
  read_raw_sensor_data(&acc_x, &acc_y, &acc_z, &gyr_x, &gyr_y, &gyr_z);

  // 디버깅용 함수 제공
  // display_raw_sensor_data(acc_x, acc_y, acc_z, gyr_x, gyr_y, gyr_z);
  
  // 원시 데이터를 가속도 데이터와 각속도 데이터로 가공
  output->acceleration_x    = acc_x / (float)MPU6050_VALUE_RANGE;
  output->acceleration_y    = acc_y / (float)MPU6050_VALUE_RANGE;
  output->acceleration_z    = acc_z / (float)MPU6050_VALUE_RANGE;
  output->angle_speed_x     = gyr_x / (float)MPU6050_VALUE_RANGE;
  output->angle_speed_y     = gyr_y / (float)MPU6050_VALUE_RANGE;
  output->angle_speed_z     = gyr_z / (float)MPU6050_VALUE_RANGE;
}

void read_raw_sensor_data
(int16_t* acc_x,
 int16_t* acc_y,
 int16_t* acc_z,
 int16_t* gyr_x,
 int16_t* gyr_y,
 int16_t* gyr_z) {

  // 원시 데이터가 저장된 주소
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_SENSOR_ADDRESS, 14, true);

  *acc_x         = (Wire.read() <<  8) | Wire.read(); 
  *acc_y         = (Wire.read() <<  8) | Wire.read(); 
  *acc_z         = (Wire.read() <<  8) | Wire.read(); 
  int16_t  tempt = (Wire.read() <<  8) | Wire.read(); // 온도 버림
  *gyr_x         = (Wire.read() <<  8) | Wire.read(); 
  *gyr_y         = (Wire.read() <<  8) | Wire.read(); 
  *gyr_z         = (Wire.read() <<  8) | Wire.read(); 
}

void display_raw_sensor_data(int16_t acc_x, int16_t acc_y, int16_t acc_z, int16_t gyr_x, int16_t gyr_y, int16_t gyr_z) {
  Serial.print("acc_x = "); Serial.print(acc_x);  Serial.print(" ");
  Serial.print("acc_y = "); Serial.print(acc_y);  Serial.print(" ");
  Serial.print("acc_z = "); Serial.print(acc_z);  Serial.print(" ");
  Serial.print("asp_x = "); Serial.print(gyr_x);  Serial.print(" ");
  Serial.print("asp_y = "); Serial.print(gyr_y);  Serial.print(" ");
  Serial.print("asp_z = "); Serial.print(gyr_z);  Serial.println();
}

void display_sensor_data(MPU6050_SENSOR_DATA data) {
  Serial.print("acc_x = "); Serial.print(data.acceleration_x);  Serial.print(" ");
  Serial.print("acc_y = "); Serial.print(data.acceleration_y);  Serial.print(" ");
  Serial.print("acc_z = "); Serial.print(data.acceleration_z);  Serial.print(" ");
  Serial.print("asp_x = "); Serial.print(data.angle_speed_x);   Serial.print(" ");
  Serial.print("asp_y = "); Serial.print(data.angle_speed_y);   Serial.print(" ");
  Serial.print("asp_z = "); Serial.print(data.angle_speed_z);   Serial.println();
}

#endif