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
int16_t kqADC6, kqADC7;
unsigned char nutSW1, nutSW3; 
unsigned char nutSW1Truoc, nutSW3Truoc; 
uint8_t demHienthi;

void setup() {
  pinMode(4,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

  Monitor.begin(19200);
}

void loop() {
  kqADC6 = analogRead(A6);
  kqADC7 = analogRead(A7);

  nutSW1Truoc = nutSW1; nutSW1 = digitalRead(4);
  nutSW3Truoc = nutSW3; nutSW3 = digitalRead(7);
  LED1 = nutSW1;
  LED2 = nutSW3;

  demHienthi++;
  if (demHienthi >= 10) {
    demHienthi = 0;
    LED4 = 1-LED4;
  }


  goimaytinh1 = kqADC6;
  goimaytinh2 = kqADC7;

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
  analogWrite(5,nhanMaytinh1);
  analogWrite(6,nhanMaytinh2);

  if (NUT1 == 1) {digitalWrite(8,HIGH);}  else  {digitalWrite(8,LOW);}
  if (NUT2 == 1) {digitalWrite(9,HIGH);}  else  {digitalWrite(9,LOW);}
  if (NUT3 == 1) {digitalWrite(11,HIGH);} else  {digitalWrite(11,LOW);}
  if (NUT4 == 1) {digitalWrite(12,HIGH);} else  {digitalWrite(12,LOW);}

  delay(20);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx