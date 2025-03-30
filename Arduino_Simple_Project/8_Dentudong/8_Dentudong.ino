//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
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

//--- LED 7 doan (1) -----------
#define La 6 
#define Lg 5

#define Lb 8 
#define Lc 9 
#define Ld 10
#define Le 11 
#define Lf 12



void hienthiLED(unsigned char so)
{
    if(so==0) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,HIGH);digitalWrite(Lf,HIGH);digitalWrite(Lg,LOW);}
    if(so==1) {digitalWrite(La,LOW);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,LOW);digitalWrite(Le,LOW);digitalWrite(Lf,LOW);digitalWrite(Lg,LOW);}
    if(so==2) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,LOW);digitalWrite(Ld,HIGH);digitalWrite(Le,HIGH);digitalWrite(Lf,LOW);digitalWrite(Lg,HIGH);}
    if(so==3) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,LOW);digitalWrite(Lf,LOW);digitalWrite(Lg,HIGH);}
    if(so==4) {digitalWrite(La,LOW);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,LOW);digitalWrite(Le,LOW);digitalWrite(Lf,HIGH);digitalWrite(Lg,HIGH);}
    if(so==5) {digitalWrite(La,HIGH);digitalWrite(Lb,LOW);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,LOW);digitalWrite(Lf,HIGH);digitalWrite(Lg,HIGH);}
    if(so==6) {digitalWrite(La,HIGH);digitalWrite(Lb,LOW);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,HIGH);digitalWrite(Lf,HIGH);digitalWrite(Lg,HIGH);}
    if(so==7) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,LOW);digitalWrite(Le,LOW);digitalWrite(Lf,LOW);digitalWrite(Lg,LOW);}
    if(so==8) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,HIGH);digitalWrite(Lf,HIGH);digitalWrite(Lg,HIGH);}
    if(so==9) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,LOW);digitalWrite(Lf,HIGH);digitalWrite(Lg,HIGH);}  
    
    if(so==16) {digitalWrite(La,LOW);digitalWrite(Lb,LOW);digitalWrite(Lc,LOW);digitalWrite(Ld,LOW);digitalWrite(Le,LOW);digitalWrite(Lf,LOW);digitalWrite(Lg,LOW);}  
    if(so==20) {digitalWrite(La,HIGH);digitalWrite(Lb,HIGH);digitalWrite(Lc,HIGH);digitalWrite(Ld,HIGH);digitalWrite(Le,HIGH);digitalWrite(Lf,HIGH);digitalWrite(Lg,HIGH);}
}

//-------------------------------------
int16_t kqADC5;

void setup() {
  Monitor.begin(19200);
  pinMode(La,OUTPUT);
  pinMode(Lb,OUTPUT);
  pinMode(Lc,OUTPUT);
  pinMode(Ld,OUTPUT);
  pinMode(Le,OUTPUT);
  pinMode(Lf,OUTPUT);
  pinMode(Lg,OUTPUT);

  hienthiLED(20);
  delay(500); 
  hienthiLED(16);  
  delay(500); 
}

void loop() {
  kqADC5 = analogRead(A5);
  goimaytinh1 = kqADC5;

  if (kqADC5 > 750) { hienthiLED(20); LED1=1;}
  if (kqADC5 < 650) { hienthiLED(16); LED1=0;}

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

  delay(20);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx