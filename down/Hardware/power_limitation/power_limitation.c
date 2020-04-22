#include "power_limitation.h"
#include "motor.h"


MOTOR_POWER power;

void power_limitation_init()
{
  power.Wd = 5;
  power.P_max = 80;
  power.P_max_feasible = 80;
  power.motor1_p = 0;
  power.motor2_p = 0;
  power.motor3_p = 0;
  power.motor4_p = 0;
  power.all_motor_current = 0;
}

void power_limitation_caculation() //这个函数可以近似计算小车启动时的瞬时功率，可用作测试实验验证
{
  power.motor1_p = motor1.vpid.PID_OUT;
  power.motor2_p = motor2.vpid.PID_OUT;
  power.motor3_p = motor3.vpid.PID_OUT;
  power.motor4_p = motor4.vpid.PID_OUT;

  power.all_motor_current = (power.motor1_p + power.motor2_p + power.motor3_p + power.motor4_p)/819.2;
  power.all_motor_current = abs1(power.all_motor_current);

  power.P_now = 24 *  power.all_motor_current;
}

void power_limitation_jugement()
{
  if(1) //if we can get the referee system's information in 200ms,we can go on.If not,we should take strict limitation on it.
  {
    if(power.buffer < power.Wd)
    power.P_max_feasible = power.P_max;
    else if(power.buffer >= power.Wd)
    power.P_max_feasible = (power.buffer - power.Wd)/0.1f;
  }
  else
  {
    power.P_max_feasible = 80;  
  }
  
}

void power_limitation_coefficient()
{
   if(power.P_now >= power.P_max_feasible)
     motor1.vpid.PID_OUT = motor1.vpid.PID_OUT * (power.P_max_feasible/power.P_now);
     motor2.vpid.PID_OUT = motor2.vpid.PID_OUT * (power.P_max_feasible/power.P_now);
     motor3.vpid.PID_OUT = motor3.vpid.PID_OUT * (power.P_max_feasible/power.P_now);
     motor4.vpid.PID_OUT = motor4.vpid.PID_OUT * (power.P_max_feasible/power.P_now);
  
}

void power_limitation_scale()
{
  if(power.P_now >= power.P_max_feasible)
    motor1.target_speed = motor1.target_speed * (power.P_max_feasible/power.P_now);
    motor2.target_speed = motor2.target_speed * (power.P_max_feasible/power.P_now);
    motor3.target_speed = motor3.target_speed * (power.P_max_feasible/power.P_now);
    motor4.target_speed = motor4.target_speed * (power.P_max_feasible/power.P_now);

}

void power_limitation_out()
{
  motor1.vpid.PID_OUT = power.motor1_p;
  motor2.vpid.PID_OUT = power.motor2_p;
  motor3.vpid.PID_OUT = power.motor3_p;
  motor4.vpid.PID_OUT = power.motor4_p;

}
void read_power()  //This function is to get information from the referee system.
{


}

float abs1(float temp)
{
    if(temp <= 0)
      temp = -temp;
    return temp;  
}

