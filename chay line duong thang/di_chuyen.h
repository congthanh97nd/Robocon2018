 #include "Arduino.h"
#include "moving.h"

double Kp = 3 ;
double Kd = 0;
double Ki = 0.03;

double error, previous_error, P, I, D, PID_value;

MOTOR motor1;
MOTOR motor2;
MOTOR motor3;
MOTOR motor4;

void khoitao()
{
  motor1.setpin(3, 2);
  motor2.setpin(5, 4);
  motor3.setpin(9, 8);
  motor4.setpin(6, 7);
  motor1.tocdo(60, 5);
  motor2.tocdo(60, 5);
  motor3.tocdo(60, 5);
  motor4.tocdo(65, 5);
}


void tien()
{
  motor1.Backward(); motor2.Forward();
  motor4.Backward(); motor3.Forward();

  motor1.tangtoc();
  motor2.tangtoc();
  motor3.tangtoc();
  motor4.tangtoc();

}
void lui()
{
  motor1.Forward(); motor2.Backward();
  motor4.Forward(); motor3.Backward();

  motor1.tangtoc();
  motor2.tangtoc();
  motor3.tangtoc();
  motor4.tangtoc();
}
void trai()
{
  motor1.Forward(); motor2.Forward();
  motor4.Backward(); motor3.Backward();

  motor1.tangtoc();
  motor2.tangtoc();
  motor3.tangtoc();
  motor4.tangtoc();
}
void phai()
{
  motor1.Backward(); motor2.Backward();
  motor4.Forward(); motor3.Forward();

  motor1.tangtoc();
  motor2.tangtoc();
  motor3.tangtoc();
  motor4.tangtoc();
}
void xoayphai()
{
  motor1.Backward(); motor2.Backward();
  motor4.Backward(); motor3.Backward();

  motor1.tangtoc();
  motor2.tangtoc();
  motor3.tangtoc();
  motor4.tangtoc();

}
void xoaytrai()
{
  motor1.Forward(); motor2.Forward();
  motor4.Forward(); motor3.Forward();

  motor1.tangtoc();
  motor2.tangtoc();
  motor3.tangtoc();
  motor4.tangtoc();

}
void cheolenphai()
{
  motor1.Backward(); motor2.Forward();
  motor4.Forward(); motor3.Forward();

  motor1.tangtoc();
  motor2.Stop();
  motor3.tangtoc();
  motor4.Stop();

}
void cheolentrai()
{
  motor1.Forward(); motor2.Forward();
  motor4.Backward(); motor3.Backward();

  motor1.Stop();
  motor2.tangtoc();
  motor3.Stop();
  motor4.tangtoc();
}
void cheoxuongtrai()
{
  motor1.Forward(); motor2.Forward();
  motor4.Forward(); motor3.Backward();

  motor1.tangtoc();
  motor2.Stop();
  motor3.tangtoc();
  motor4.Stop();
}
void cheoxuongphai()
{
  motor1.Forward(); motor2.Backward();
  motor4.Forward(); motor3.Backward();

  motor1.Stop();
  motor2.tangtoc();
  motor3.Stop();
  motor4.tangtoc();
}
void calculate_pid()
{
  P = error;
  I = I + error;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_error = error;
}
void tien1()
{
  calculate_pid();

  motor1.Backward(); motor2.Forward();
  motor4.Backward(); motor3.Forward();

  motor1.pidtangxung(60 - PID_value); motor2.pidgiamxung(60 + PID_value);
  motor4.pidtangxung(65 + PID_value); motor3.pidgiamxung(60 - PID_value);

}

void stopAll()
{
  motor1.Stop();
  motor2.Stop();
  motor3.Stop();
  motor4.Stop();
}
void stopAll1()
{
  motor1.Stop1();
  motor2.Stop1();
  motor3.Stop1();
  motor4.Stop1();
}
