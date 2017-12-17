#include <EEPROM.h>
int A[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
unsigned int a[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int l_max[] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int l_min[] = {1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
unsigned int giatri[8];
unsigned int sensor[] = {A0, A1, A2, A3, A4, A5, A6, A7};
byte w[8] = {128, 64, 32, 16, 8, 4, 2, 1};
double Max[] = {0, 0, 0, 0, 0, 0, 0, 0};
double Min[] = {0, 0, 0, 0, 0, 0, 0, 0};
int KQ_MIN[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int KQ_MAX[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int solan = 8;
unsigned int b[8];



void EEPROM_ghi(unsigned int dchi, unsigned int dlieu)
{
  unsigned char dl_h, dl_l;
  dl_l = (unsigned char)(dlieu & 0x00ff);
  dlieu = dlieu >> 8;
  dl_h = (unsigned char)(dlieu & 0x00ff);
  EEPROM.write(dchi, dl_h);
  EEPROM.write(dchi + 1, dl_l);
}
unsigned int  EEPROM_doc(unsigned int dchi)
{
  unsigned int dl_h, dl_l;
  dl_h = (unsigned int)EEPROM.read(dchi);
  dl_l = (unsigned int)EEPROM.read(dchi + 1);
  return ((dl_h << 8) | dl_l);
}
void doc_gt_Eeprom(void)
{
  unsigned char i;
  for (i = 0; i < 8; i++) {
    b[i] = EEPROM_doc(2 * i);
  }
}


/************************so sanh gia tri doc voi gia tri mau*************************************/
unsigned char kiem_tra_vung (unsigned int gt_can_kt, unsigned int gt_mau)
{
  if ((gt_can_kt <   gt_mau))
    return (1);
  else return (0);
}
/************************doc gia tri hien tai cua quang tro**************************************/
int doc_cam_bien(int i)
{
  giatri[i] = analogRead(sensor[i]);
  return giatri[i];
}
/************************so sanh va chuyen doi ve 8 bit******************************************/
int kt_ket_qua(void)
{
  unsigned char i;
  byte ket_qua = 0b00000000;

  for (i = 0; i < 8; i++)
  {
    doc_cam_bien(i);
    if (kiem_tra_vung(giatri[i], b[i])) ket_qua |= w[7 - i];
    else ket_qua |= 0;
  }
  return ket_qua;
}
/***********************doc gia tri line********************************************************/
void check_line(int solan)
{
  for (int i = 2; i < 10; i++)
  {
    digitalWrite(i, 0);
  }
  delay(100);
  for (int i = 2; i < 10; i++)
  {
    digitalWrite(i, 1);
    delay(30);
  }
  for (int n = 0; n < solan; n++)
  {
    for (int j = 0; j < 100; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        if (l_max[i] < doc_cam_bien(i))
        {
          l_max[i] = doc_cam_bien(i);
        }
        Max[i] = l_max[i] + Max[i];
      }
    }
  }
  for (int i = 9; i > 1; i--)
  {
    digitalWrite(i, 0);
    delay(30);
  }
}
/***************************doc gia tri san*********************************************************/
void check_san(int solan)
{

  for (int i = 9; i > 1; i--)
  {
    digitalWrite(i, 0);
  }
  delay(100);
  for (int i = 9; i > 1; i--)
  {
    digitalWrite(i, 1);
    delay(30);
  }
  for (int n = 0; n < solan; n++)
  {
    for (int j = 0; j < 100; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        if (l_min[i] > doc_cam_bien(i))
        {
          l_min[i] = doc_cam_bien(i);
        }
        Min[i] = l_min[i] + Min[i];
      }
    }
  }
  for (int i = 2; i < 10; i++)
  {
    digitalWrite(i, 0);
    delay(30);
  }
} /*****************************************luu cac gia tri***********************************/
void luu_gia_tri()
{
  for (int i = 0; i < 8; i++)
  {
    KQ_MAX[i] = Max[i] / ((solan) * 100);
    KQ_MIN[i] = Min[i] / ((solan) * 100);
  }
  for (int i = 0; i < 8; i++)
  {
    a[i] = (KQ_MAX[i] + KQ_MIN[i]) / 2;
    EEPROM_ghi(i * 2, a[i]);
  }
}
