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

//----- motor DC ----------------
#define PWM1 5  //g ENA
#define IN1 11  //e
#define IN2 10  //d

void dkMotorDC1(int16_t x)
{
  x = constrain(x,-196,196);
  if (x > 0) {digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); analogWrite(PWM1,x+59);}
  else if (x < 0) {digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH); analogWrite(PWM1,-x+59);}
  else {analogWrite(PWM1,0);}
}
//---------------------------------------
uint32_t tdHientai, tdTruoc, chuky; //us
int16_t tanso, transoTruoc, giatoc;
int16_t demXung, demXungSET;
int8_t thuannguoc, lenxuong;

void ngatngoai1()
{
  if (digitalRead(2) == HIGH) { demXung++; thuannguoc = 1;} 
  else { demXung--; thuannguoc = -1;}
 
  tdTruoc = tdHientai;
  tdHientai = micros();
  chuyky = tdHientai-tdTruoc;
}
//---------------------------------------
int16_t giatriTocdo;
//---------------------------------------
void setup() {
  // pinMode(2,INPUT_PULLUP);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(PWM1,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(3), ngatngoai1, FALLING);
  Monitor.begin(19200);
  nhanMaytinh1=128;
}

void loop() {
  tansoTruoc = tanso;
  if ( micros() > (tdHientai+1000000)) {tanso = 0; thuannguoc = 0;} else {tanso = 1000000/chuky;}
  giatoc = tanso-tansoTruoc;


  if (NUT1) {demXungSET=3000; lenxuong = 1;}
  if (NUT2) {demXungSET=0; lenxuong = -1;}
  
  if (demXung < (demXungSET-50)) {dkMotorDC1(100);}
  else if (demXung > (demXungSET+50)) {dkMotorDC1(-100);}
  else {dkMotorDC1(0); lenxuong = 0;}

  if (giatoc < -25) {
    if (lenxuong == -1) { demXungSET = demXung; lenxuong = 0;}
    if (lenxuong == 1) {
      dkMotorDC1(0); delay(300);
      demXungSET = demXung-300;
      lenxuong = 0;
    }
    
  }

  goimaytinh1 = demXung;
  goimaytinh2 = giatoc;
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