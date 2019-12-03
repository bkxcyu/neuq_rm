#ifndef ZHIDAO_H_INCLUDED
#define ZHIDAO_H_INCLUDED

class GimbalContrl
{
public:
    GimbalContrl(int x,int y,int z);
    double getpitch();
    //~GimbalContrl();
    double getyaw();
    double gets();
    double setpitch();
    double alinepitch(double x,double y);
    double sets();
    double setyaw();

private:
    double x,y,z,pitch;
    const double v=20.0;
    double s;
    double yaw;
};

#endif // ZHIDAO_H_INCLUDED
