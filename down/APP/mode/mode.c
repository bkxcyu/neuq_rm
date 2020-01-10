#include "json.h" 
#include "mode.h"


extern enum  chassis_mode_t  chassis_modes;
extern enum  gimbal_mode_t   gimbal_modes;
extern enum  fric_mode_t     fric_modes;

void chassis_behavior(void)
{

	switch(chassis_modes)
	{
		case chassis_normal_mode:
			
		break;
		
		case 	chassis_dodge_mode:
			
		break;
		
		case chassis_motion_mode:
			
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


