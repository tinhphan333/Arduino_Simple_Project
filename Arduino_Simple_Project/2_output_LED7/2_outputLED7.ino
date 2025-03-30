//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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


//----------------------- 
// unsigned char i;  
//-----------------------

void setup() {
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
//-------------------------------
void loop() {
  for (uint8_t i=0; i<10; i++) {hienthiLED(i); delay(500);} 
  hienthiLED(16); delay(500);   
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx