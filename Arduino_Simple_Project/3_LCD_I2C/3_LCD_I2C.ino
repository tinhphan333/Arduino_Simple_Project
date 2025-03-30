

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//-----------------------------
uint8_t dem;

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world! $ @");
  delay(1000);
  lcd.noBacklight();
  delay(1000);
	lcd.backlight();

  // lcd.setCursor(2, 1);
	// lcd.print("TT lap trinh");

  // for (uint8_t i; i<50; i++) {
  //   delay(100);
  //   lcd.noBacklight();
  //   delay(100);
  //   lcd.backlight();
  // }

}

void loop()
{
  dem++;
  lcd.setCursor(3, 1);

  // if (dem<10) {lcd.print("  "); lcd.print(dem);}
  // else if (dem<100) {lcd.print(" "); lcd.print(dem);}
  // else {lcd.print(dem);}

  lcd.print(dem/100);
  lcd.print(dem/10%10);
  // lcd.print(dem%10);
  lcd.write(dem%10 + 48);
  
	delay(100);
}
