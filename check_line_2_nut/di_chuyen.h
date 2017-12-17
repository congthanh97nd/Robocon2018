#include "PID_v1.h"

int mahoa[15] = {1, 3, 2, 6, 4, 12, 8, 24, 16, 48, 32, 96, 64, 192, 128};
int loi[15] =   {7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7};
double Kp = 8;
double Kd = 3;//thoi gian dap ung
double Ki =1.5;
double setpoint = 0;

int enA = 9;
int in1 = 7;
int in2 = 6;

//Khai báo chân tín hiệu cho motor B
int in3 = 5;
int in4 = 4;
int enB = 3;
 
double error;
double output;

PID pid(&error, &output, &setpoint, Kp, Ki, Kd, DIRECT);
/*****************khoi tao*********************************/
void khoi_tao()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pid.SetMode(AUTOMATIC);
  pid.SetSampleTime(50);
  pid.SetOutputLimits(-150, 150);
}
/*****************xet cac truong hop************************/
void read_sensor_values()
{
  for (int i = 0; i < 15; i++)
  {
    if (kt_ket_qua() == mahoa[i])
    {
      error = loi[i];
    }
  }
}
/*****************dieu khien*******************************/
void go()
{
  int pwmB = 255 - output;
  int pwmA = 255 + output;
  constrain(pwmB, 0, 255);
  constrain(pwmA, 0, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, pwmB );
  analogWrite(enA, pwmA);
}

