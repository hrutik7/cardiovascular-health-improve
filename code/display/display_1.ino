/* Starting with Arduino OLED coding
 *  for " arduino oled i2c tutorial : 0.96" 128 X 32 for beginners"
 *  subscribe for more arduino Tuorials and Projects
https://www.youtube.com/channel/UCM6rbuieQBBLFsxszWA85AQ?sub_confirmation=1
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels




void setup() 
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Serial.begin(115200);

}

void loop() 
{
 // display.setTextSize(1.5);
 // display.setTextColor(WHITE);
  display.setCursor(20,0);
  
  display.print("BREATHE");
  
  display.println("STEPS { }");
  display.display();


}
