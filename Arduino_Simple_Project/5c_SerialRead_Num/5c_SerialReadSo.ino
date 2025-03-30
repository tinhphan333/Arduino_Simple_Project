//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
char kytunhan;
String chuoiNhan;
int soNhan;
unsigned char so;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup...");
}

void loop() {
  while (Serial.available() > 0) {
    kytunhan = Serial.read(); 
    // Serial.print(kytunhan); so = kytunhan; Serial.print(so);
    if(kytunhan != '\n') {chuoiNhan += kytunhan;}
    else {
      //nhan dang so
      // soNhan = (chuoiNhan[0]-48)*100 + (chuoiNhan[1]-48)*10 + (chuoiNhan[2]-48);
      soNhan = chuoiNhan.toInt(); //-32768 -> 32767
      Serial.println(soNhan);

      chuoiNhan = "";
    }
  }
  delay(100);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx