//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
uint8_t dem;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup...");
  Serial.println("Chuẩn bị giao tiếp ... ");

}

void loop() {
  dem++;
  Serial.println(dem);
  // Serial.write(7);
  delay(1000);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx