#include "di_chuyen.h"
#include "inttypes.h"
#include <PS2X_lib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

int mahoa[15] = {1, 3, 2, 6, 4, 12, 8, 24, 16, 48, 32, 96, 64, 192, 128};
int loi[15] =   {7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7};
int ma[8] =   {A8, A9, A10, A11, A12, A13, A14, A15};
int dem = 0;

#define PS2_DAT        52
#define PS2_CMD        51
#define PS2_SEL        53
#define PS2_CLK        50

#define pressures   false
#define rumble      false

PS2X ps2x;

int error1 = 0;
byte type = 0;
byte vibrate = 0;
uint8_t tempRX;
uint8_t tempLY;
uint8_t tempRY;
uint8_t tempLX;



/*****************xet cac truong hop************************/
void read_sensor_values()
{
  byte read_K = (PINK & 0XFF);
  for (int i = 0; i < 15; i++)
  {
    if (read_K == mahoa[i])
    {
      error = loi[i];
    }
  }
  Serial.println(read_K, BIN);
}

void setup()
{
  error1 = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  for (int i = 0; i++; i < 8)
  {
    pinMode(ma[i], INPUT_PULLUP);
  }
  pinMode(14, OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  khoitao();
}
void loop()
{
  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  //**************************************************************
  tempRX = ps2x.Analog(PSS_RX);
  tempLY = ps2x.Analog(PSS_LY);
  if (ps2x.Button(PSB_R2) || ps2x.Button(PSB_L2))
  {
    dem = 0;
  }
  else if (ps2x.Button(PSB_TRIANGLE))
  {
    dem = 1;
  }
  else if (ps2x.NewButtonState(PSB_CROSS))
  {
    dem = 2;
  }
  if (dem == 0)
  {
    if (tempLY < 20 && tempRX > 100 && tempRX < 200)
    {
      tien();
      Serial.println("tien");
    }
    else if (tempLY > 220 && tempRX > 100 && tempRX < 200)
    {
      lui();
      Serial.println("lui");
    }
    else if (tempRX > 150 && tempLY > 100 && tempLY < 200)
    {
      phai();
      Serial.println("phai");
    }
    else if (tempRX < 20 && tempLY > 100 && tempLY < 200)
    {
      trai();
      Serial.println("trai");
    }
    else if (tempRX < 20 && tempLY < 20)
    {
      cheolentrai();
      Serial.println("len trai");
    }
    else if (tempRX > 150 && tempLY < 20)
    {
      cheolenphai();
      Serial.println("len phai");
    }
    else if (tempRX < 20 && tempLY > 200)
    {
      cheoxuongtrai();
      Serial.println("xuong trai");
    }
    else if (tempRX > 150 && tempLY > 200)
    {
      cheoxuongphai();
      Serial.println("xuong phai");
    }
    else if (ps2x.Button(PSB_L1) && !ps2x.Button(PSB_R1) && tempRX > 100 && tempRX < 200 && tempLY > 100 && tempLY < 200)
    {
      Serial.println("xoay trai");
      xoaytrai();
    }
    else if (!ps2x.Button(PSB_L1) && ps2x.Button(PSB_R1) && tempRX > 100 && tempRX < 200 && tempLY > 100 && tempLY < 200)
    {
      Serial.println("xoay phai");
      xoayphai();
    }
    else
    {
      stopAll();
      Serial.println("dung");
    }
  }
  else if (dem == 1)
  {
    tien1();
    read_sensor_values();
    Serial.println("che do line");
  }
  else if (dem == 2)
  {
    stopAll1();
    Serial.println("che do dung");
  }
  delay(10);
}
