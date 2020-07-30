#include "imuReader.h"

IMU_DATA imu_data;

float yawRead(void){
	return imu_data.yaw;
}
