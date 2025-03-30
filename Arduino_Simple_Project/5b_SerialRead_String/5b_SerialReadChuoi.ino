//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
char kytunhan;
String chuoiNhan;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  Serial.begin(9600);
  Serial.println("Setup...");

}

void loop() {
  while (Serial.available() > 0) {
    kytunhan = Serial.read();
    if(kytunhan != '\n') {chuoiNhan += kytunhan;}
    else {
      if (chuoiNhan == "1ON") {digitalWrite(6,HIGH); Serial.println("La sang");}
      if (chuoiNhan == "1OFF") {digitalWrite(6,LOW);  Serial.println("La tat");}
      if (chuoiNhan == "2ON") {digitalWrite(5,HIGH); Serial.println("Lg sang");}
      if (chuoiNhan == "2OFF") {digitalWrite(5,LOW);  Serial.println("Lg tat");}
      Serial.println(chuoiNhan);
      chuoiNhan = "";
    }
  }
  delay(100);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx