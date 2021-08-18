#ifndef ControlMotor_h
#define ControlMotor_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ControlMotor
{
  public:
    ControlMotor(int MR1,int MR2,int ML1,int ML2,int PWMR,int PWML);
    void Motor(int speed, int giro);
  private:
    void CalculateSpeed(int speed, int turn, int *vel_left, int *vel_right );
    int MotRight1;
    int MotRight2;
    int MotLeft1;
    int MotLeft2;
    int pwmR;
    int pwmL;
};

#endif
