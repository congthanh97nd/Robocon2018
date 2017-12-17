#include "check_line.h"
int button1 = 11;
int button2 = 12;
int dem = 0;

void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.begin(9600);
  for (int i = 2; i < 10; i++)
  {
    pinMode(i, OUTPUT);
  }
  doc_gt_Eeprom();
}
void loop()
{
  int  buttonStatus1 = digitalRead(button1);
  int  buttonStatus2 = digitalRead(button2);
  if (buttonStatus1 == 1 )
  {
    check_line(solan);
    luu_gia_tri();
  }
  if (buttonStatus2 == 1 )
  {
    luu_gia_tri();
    check_san(solan);
  }
  PORTD = kt_ket_qua() << 2;
  PORTB = kt_ket_qua() >> 6;
  Serial.println(kt_ket_qua(), BIN);
}
