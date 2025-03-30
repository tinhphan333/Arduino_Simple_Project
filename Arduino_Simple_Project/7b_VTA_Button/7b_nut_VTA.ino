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
uint8_t DEN1, DEN2;
unsigned char nutSW1, nutSW3; 
unsigned char nutSW1Truoc, nutSW3Truoc; 

int16_t kqADC6;
uint8_t VTA;
//---------------------------------------

void setup() {
  pinMode(4,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  Monitor.begin(19200);
}

void loop() {
  kqADC6 = analogRead(A6);
  if (kqADC6 < 102) {LED4 = 1; VTA=30;}
  else if (kqADC6 > 920) {LED3 = 1; VTA=30;}
  else { 
    LED3=0; LED4=0; 
    // VTA = (int32_t) (kqADC6-102)*100/818; 
    VTA = map(kqADC6,102,920,0,100);
  }
  
  nutSW1Truoc = nutSW1; nutSW1 = digitalRead(4);
  nutSW3Truoc = nutSW3; nutSW3 = digitalRead(7); 
  
  if(nutSW1Truoc == 1 && nutSW1 == 0) { DEN1 = 1-DEN1; }
  if(nutSW3Truoc == 1 && nutSW3 == 0) { DEN2 = 1-DEN2; }

  LED1 = DEN1;
  LED2 = DEN2;
  goimaytinh1 = kqADC6;
  goimaytinh2 = VTA;
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