//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

void setup() {
  pinMode(B1,OUTPUT);
  pinMode(B2,OUTPUT);
  pinMode(B3,OUTPUT);
  pinMode(B4,OUTPUT);
}

void loop() {
  B1on; B2off; B3off; B4off; delay(100);
  B1off; B2on; B3off; B4off; delay(100);
  B1off; B2off; B3on; B4off; delay(100);
  B1off; B2off; B3off; B4on; delay(100);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx