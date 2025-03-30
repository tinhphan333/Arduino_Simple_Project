//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
char kytunhan;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  Serial.begin(9600);
  Serial.println("Setup...");

}

void loop() {
  if (Serial.available() > 0) {
    kytunhan = Serial.read();
    if (kytunhan == '1') {digitalWrite(6,HIGH); Serial.println("La sang");}
    if (kytunhan == '0') {digitalWrite(6,LOW);  Serial.println("La tat");}
    
    if (kytunhan == '3') {digitalWrite(5,HIGH); Serial.println("Lg sang");}
    if (kytunhan == '2') {digitalWrite(5,LOW);  Serial.println("Lg tat");}
  }
  delay(100);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx