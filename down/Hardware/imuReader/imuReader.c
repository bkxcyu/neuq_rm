#include "imuReader.h"

IMU_DATA imu_data;

float yawRead(void){
	return imu_data.yaw;
}
float yaw_angularRead(void)
{
  return imu_data.yaw_angular;
}
float pitch_angularRead(void)
{
	return imu_data.pitch_angular;
}
