#ifndef POWER_LIMITATION_H
#define POWER_LIMITATION_H

typedef struct{

  int motor1_p;
  int motor2_p;
  int motor3_p;
  int motor4_p;

  float all_motor_current;

  int Wd;
  float P_max;
  float P_max_feasible;
  float P_now;
  float buffer;

}MOTOR_POWER;

void power_limitation_jugement(void);
void power_limitation_init(void);
void power_limitation_caculation(void);
void power_limitation_coefficient(void);
void power_limitation_out(void);
void read_power(void);
void power_limitation_scale(void);
float abs1(float temp);

#endif 
