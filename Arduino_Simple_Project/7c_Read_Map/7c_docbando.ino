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

int16_t nhietdo;
uint8_t vitriCamchung;
uint8_t bandoCamchung[10]={114,119,126,132,136,140,144,149,154,154};
uint8_t phantuNhietdo;
//---------------------------------------

void setup() {
  Monitor.begin(19200);
}

void loop() {
  kqADC6 = analogRead(A6);
  nhietdo = map(kqADC6,0,1023,-40,215);

  if (nhietdo < 0) {vitriCamchung = 114;}
  else if (nhietdo >= 140) {vitriCamchung = 154;}
  else {
    phantuNhietdo = nhietdo/14;
    vitriCamchung = bandoCamchung[phantuNhietdo];
  }

  goimaytinh1 = nhietdo;
  goimaytinh2 = vitriCamchung;
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