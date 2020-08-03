#ifndef _IMUREADER_H_
#define _IMUREADER_H_
#include "sys.h"
#include "stm32f4xx.h"
#define YAWL ((unsigned int)(6))
#define YAWH ((unsigned int)(7))
#define YAWL_angular ((unsigned int)(6))
#define YAWH_angular ((unsigned int)(7))
#define PITCHL_angular ((unsigned int)(4))
#define PITCHH_angular ((unsigned int)(5))	

/**@brief The structrue records some of the specific data detected by imu
  *
*/

typedef struct{
	float yaw;
	float time;
	float yaw_angular;
	float pitch_angular;
	float ax;  //º”ÀŸ∂»
	float ay;
	float az;
	float vx;
	float vy;
	float vz;
	
}IMU_DATA;




/** @brief Read value of yaw from imu and transfer it to arc
  * @return float Value of yaw(rad) 
*/
float yawRead(void);
float yaw_angularRead(void);
float pitch_angularRead(void);
float x_accelerationRead(void);
float y_accelerationRead(void);
float z_accelerationRead(void);

#endif //_IMUREADER_H_
