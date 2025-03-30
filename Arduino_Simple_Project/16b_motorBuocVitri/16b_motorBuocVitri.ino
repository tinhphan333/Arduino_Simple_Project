//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#include <TrTmonitor.h>
TrTmonitor Monitor(0);
//khai báo các biến để đồng bộ truyền nhận Arduino và App
int16_t goimaytinh1, goimaytinh2; //gửi lên đồng hồ READ1 & READ2 của App
uint8_t LEDgoimaytinh; //gửi hiển thị LED trên App
uint8_t nhanMaytinh1, nhanMaytinh2, nutMaytinh; //WRITE1 & WRITE2 && nút nhấn trên App

//Khai báo các biến bit để dễ xử lý
unsigned char NUT1, NUT2, NUT3, NUT4;
unsigned char LED1, LED2, LED3, LED4;
//---------------------------------------
//---- motoor Buoc (1) ---------------------------
#define B1 8  //b
#define B2 9  //c
#define B3 6  //a
#define B4 5  //g

#define B1on  digitalWrite(B1,HIGH)
#define B2on  digitalWrite(B2,HIGH)
#define B3on  digitalWrite(B3,HIGH)
#define B4on  digitalWrite(B4,HIGH)

#define B1off  digitalWrite(B1,LOW)
#define B2off  digitalWrite(B2,LOW)
#define B3off  digitalWrite(B3,LOW)
#define B4off  digitalWrite(B4,LOW)

void chaynguoc(uint8_t x)
{
  x = constrain(x, 5, 50);
  B1on; B2off; B3off; B4off; delay(x);
  B1off; B2on; B3off; B4off; delay(x);
  B1off; B2off; B3on; B4off; delay(x);
  B1off; B2off; B3off; B4on; delay(x);
}

void chaythuan(uint8_t x)
{
  x = constrain(x, 5, 50);
  B1off; B2off; B3on; B4off; delay(x);
  B1off; B2on; B3off; B4off; delay(x);
  B1on; B2off; B3off; B4off; delay(x);
  B1off; B2off; B3off; B4on; delay(x);
}

void dung(uint8_t x)
{
  x = constrain(x, 5, 50);
  B1off; B2off; B3off; B4off; delay(x);  delay(x);  delay(x);  delay(x);
}
//-------------------------------

//-------------------------------
void setup() {
  pinMode(B1,OUTPUT);
  pinMode(B2,OUTPUT);
  pinMode(B3,OUTPUT);
  pinMode(B4,OUTPUT);

  Monitor.begin(19200);
  nhanMaytinh1 = 0;
}
//-------------------------------
int16_t vitriSet, vitri; // 1 don vi = 4 buoc = 1 lan goi ham

void loop() {
  // vitriSet = nhanMaytinh1*2;
  if (NUT3) {vitriSet = 0;}
  if (NUT4) {vitriSet = 170;}

  if (NUT1) {chaynguoc(5);}
  else (NUT2) {chaythuan(5);}
  else {
    if(vitri > vitriSet) { vitri--; chaynguoc(5); }
    else if (vitri < vitriSet) { vitri++; chaythuan(5);}
    else { dung(5); }
  }

  goimaytinh1 = vitriSet;
  goimaytinh2 = vitri;
  //---------------------------------------------------------
  // đóng gói các bit vào byte trước khi gửi
  LEDgoimaytinh = LED1 + LED2*2 + LED3*4 + LED4*8; 
  //đồng bộ Arduino & App (truyền nhận Arduino & App): cần tối thiểu 20ms
  Monitor.synch(nhanMaytinh1, nhanMaytinh2, nutMaytinh, goimaytinh1, goimaytinh2, LEDgoimaytinh);
  //chuyển đổi byte nhận vào bit để tiện sử dụng
  NUT1 = (nutMaytinh&1);
  NUT2 = (nutMaytinh&2)>>1;
  NUT3 = (nutMaytinh&4)>>2;
  NUT4 = (nutMaytinh&8)>>3;
  //---------------------------------------------------------
  // delay(20);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx