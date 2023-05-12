#ifndef MPU6050_DATA_HANDLE_INCLUDE_FLAG
#define MPU6050_DATA_HANDLE_INCLUDE_FLAG

const int MPU6050_SENSOR_ADDRESS = 0x68;
const int MPU6050_VALUE_RANGE_SETTING_REGISTER = 0x1B;
int MPU6050_VALUE_RANGE_SETTING = 0x00;
int MPU6050_VALUE_RANGE = 250; 

typedef struct {
    float acceleration_x, acceleration_y, acceleration_z;
    float  angle_speed_x,  angle_speed_y, angle_speed_z;
} MPU6050_SENSOR_DATA; 

void init_MPU6050();
void parse_sensor_data(MPU6050_SENSOR_DATA* output);
void display_sensor_data(MPU6050_SENSOR_DATA* data);

void read_raw_sensor_data(int16_t* acc_x, int16_t* acc_y, int16_t* acc_z, int16_t* gyr_x, int16_t* gyr_y, int16_t* gyr_z);
void display_raw_sensor_data(int16_t acc_x, int16_t acc_y, int16_t acc_z, int16_t gyr_x, int16_t gyr_y, int16_t gyr_z);

#endif