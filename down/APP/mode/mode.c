#include "json.h" 
#include "mode.h"
#include "motor.h"

extern enum  chassis_mode_t  chassis_modes;
extern enum  gimbal_mode_t   gimbal_modes;
extern enum  fric_mode_t     fric_modes;

void chassis_behavior(void)
{

	switch(chassis_modes)
	{
		case chassis_normal_mode:
			
		  max_motor_speed=15336;
		  max_base_linear_speed=217.812f;
		  max_base_rotational_speed=7.26057;
			vpid_out_max=8000;
		
		break;
		
		case 	chassis_dodge_mode:
			
		break;
		
		case chassis_motion_mode:
			
			max_motor_speed=30672;
		  max_base_linear_speed=435.624f;
		  max_base_rotational_speed=14.52114;
			vpid_out_max=16000;
		
		break;
		
		case  chassis_follow_mode:
			
		break;
		
		default:
		break;
		
		
	}

}

void  gimbal_behavior(void)
{
switch(gimbal_modes)
	{
	case gimbal_auto_mode:
		
	break;
	
	case gimbal_load_mode:
		
	break;
	
	case gimbal_turn_mode:
		
	break;
	
	case gimbal_side_mode:
		
	break;
	
	default:
	break;
	


   }

}




void  fric_behavior(void)
{
 switch(fric_modes)
 {
	 case fric_hand_mode:
		 
	 break;
	 
	 case fric_Shand_mode:
		 
	 break;
	 
	 case  fric_auto_mode:
		 
	 break;
	 
	 default:
	 break;
 
 }




}

void  all_behavior()
{

   chassis_behavior();
	 gimbal_behavior();
	 fric_behavior();

}


