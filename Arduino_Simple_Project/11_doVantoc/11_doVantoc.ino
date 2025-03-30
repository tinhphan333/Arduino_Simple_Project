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
uint8_t doSang;
uint32_t tdHientai, tdTruoc, chuky; //us
uint16_t tanso;
int16_t demXung;
int8_t taySo;
uint32_t quangDuong;
uint16_t vanToc;

void ngatngoai1()
{
  if (taySo==1) {demXung++;}
  if (taySo==-1) {demXung--;}

  tdTruoc = tdHientai;
  tdHientai = micros();
  chuyky = tdHientai-tdTruoc;
}

void setup() {
  pinMode(5,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(3), ngatngoai1, FALLING);
  Monitor.begin(19200);
}

void loop() {
  if ( micros() > (tdHientai+360000)) {vanToc = 0;} else {vanToc = 360000/chuky;}

  quangDuong = demXung/10; //met

  goimaytinh1 = quangDuong;
  goimaytinh2 = tanso;
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
  if (NUT1) {taySo = 1; LED1=1; LED2=0; LED3=0;}
  if (NUT2) {taySo = 0; LED1=0; LED2=1; LED3=0;}
  if (NUT3) {taySo = -1; LED1=0; LED2=0; LED3=1;}
  if (NUT4) {demXung=0;}

  delay(20);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx