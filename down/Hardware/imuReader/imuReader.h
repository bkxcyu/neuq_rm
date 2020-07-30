#ifndef _IMUREADER_H_
#define _IMUREADER_H_
#include "sys.h"
#include "stm32f4xx.h"
#define YAWL ((unsigned int)(6))
#define YAWH ((unsigned int)(7))

/**@brief The structrue records some of the specific data detected by imu
  *
*/
typedef struct{
	float yaw;
	float time;
	
}IMU_DATA;

/** @brief Read value of yaw from imu and transfer it to arc
  * @return float Value of yaw(rad) 
*/
float yawRead(void);


#endif //_IMUREADER_H_
