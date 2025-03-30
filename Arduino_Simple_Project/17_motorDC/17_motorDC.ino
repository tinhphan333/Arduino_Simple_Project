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
uint16_t tanso;
int16_t demXung, demXung2;
int8_t taySo, thuannguoc;

void ngatngoai1()
{
  if (taySo==1) {demXung++;}
  if (taySo==-1) {demXung--;}

  if (digitalRead(2) == HIGH) { demXung2++; thuannguoc = 1;} 
  else { demXung2--; thuannguoc = -1;}
 
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
  if ( micros() > (tdHientai+1000000)) {tanso = 0; thuannguoc = 0;} else {tanso = 1000000/chuky;}
  
  if (nhanMaytinh1<=110) {giatriTocdo = map(nhanMaytinh1,0,110,-196,-1); }
  else if (nhanMaytinh1>=145) {giatriTocdo = map(nhanMaytinh1,145,255,1,196); }
  else {giatriTocdo = 0; }
  dkMotorDC1(giatriTocdo);

  if (thuannguoc==1) {LED1 = 1; LED2 = 0;}
  if (thuannguoc==-1) {LED1 = 0; LED2 = 1;}
  if (thuannguoc==0) {LED1 = 0; LED2 = 0;}

  goimaytinh1 = demXung2;
  goimaytinh2 = tanso*thuannguoc;
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