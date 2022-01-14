








#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int TR_PIN = A0;
double a1, b1, c1, d1, r2, r1, vo, tempC, tempF, tempK;
float counterBreathe = 0;
const int xpin = A3;
const int ypin = A6;
const int zpin = A7;




float threshold = 6;
float xval[100] = {0};
float yval[100] = {0};
float zval[100] = {0};
float xavg, yavg, zavg;
int steps, flag = 0;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  Serial.println(F("SSD1306 allocation "));
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("SUBS 2 ME"); //Write custom text here
  display.display(); 
  delay(100);
  a1 = 3.354016E-03 ;
  b1 = 2.569850E-04 ;
  c1 = 2.620131E-06 ;
  d1 = 6.383091E-08 ;

  r1 = 9720.0;


  delay(100);
  pinMode(TR_PIN, INPUT);
  calibrate();
}

void loop() {
  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);









  int acc = 0;
  float totvect[100] = {0};
  float totave[100] = {0};
  float xaccl[100] = {0};
  float yaccl[100] = {0};
  float zaccl[100] = {0};
  for (int a = 0; a < 100; a++)
  {
    xaccl[a] = float(analogRead(xpin) - 345);
    delay(1);
    yaccl[a] = float(analogRead(ypin) - 346);
    delay(1);
    zaccl[a] = float(analogRead(zpin) - 416);
    delay(1);
    totvect[a] = sqrt(((xaccl[a] - xavg) * (xaccl[a] - xavg)) + ((yaccl[a] - yavg) * (yaccl[a] - yavg)) + ((zval[a] - zavg) * (zval[a] - zavg)));
    totave[a] = (totvect[a] + totvect[a - 1]) / 2 ;
//    Serial.println(F("totave[a]"));
//    Serial.println(totave[a]);
    delay(100);
    if (totave[a] > threshold && flag == 0)
    {
      steps = steps + 1;
      flag = 1;
    }
    else if (totave[a] > threshold && flag == 1)
    {
      // Don't Count
    }
    if (totave[a] < threshold   && flag == 1)
    {
      flag = 0;
    }
    if (steps < 0) {
      steps = 0;
    }
 //   Serial.println(F('\n'));
 //   Serial.print(F("steps: "));
  //  Serial.println(F(steps));
    vo = analogRead(TR_PIN);
  vo = vo / (1023.0 / 5.0);

  // voltage divider calculation
  // vo = 5 * r2 /(r1+r2)
  // solve for r2
  // get the exact value for voltage divider r1

  r2 = ( vo * r1) / (5.0 - vo);

  //equation from data sheet
  tempK = 1.0 / (a1 + (b1 * (log(r2 / 10000.0))) + (c1 * pow(log(r2 / 10000.0), 2.0)) + (d1 * pow(log(r2 / 10000.0), 3.0)));
  tempC  = (tempK - 273.15);
 // Serial.println(tempC);

 // delay(1000);

   
  if(tempC <= 24.62 && tempC >=24.00){
  counterBreathe = counterBreathe + 1;
 // Serial.println("im in if");
  display.clearDisplay();
  display.print("No. of breath : " + String(counterBreathe));
  display.display(); 
  }

  
 // Serial.println(F(tempC));

   display.clearDisplay();
 
  
  display.println("STEPS :" + String(steps));
  
  display.display();
  
display.startscrollright(0x00, 0x00);
    
    
  }
  
  
  // read the temp
  vo = analogRead(TR_PIN);
  vo = vo / (1023.0 / 5.0);

  // voltage divider calculation
  // vo = 5 * r2 /(r1+r2)
  // solve for r2
  // get the exact value for voltage divider r1

  r2 = ( vo * r1) / (5.0 - vo);

  //equation from data sheet
  tempK = 1.0 / (a1 + (b1 * (log(r2 / 10000.0))) + (c1 * pow(log(r2 / 10000.0), 2.0)) + (d1 * pow(log(r2 / 10000.0), 3.0)));
  tempC  = (tempK - 273.15);


   
  if(tempC <= 24.62 && tempC >=24.00){
  counterBreathe = counterBreathe + 1;
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  
//  display.println("Breath" + String(counterBreathe));
//  
//  display.println("STEPS" + String(steps));
//  display.display();
 display.clearDisplay();
  display.print("No of breath" + String(counterBreathe));
  display.display(); 
  }
  
  
  
//  Serial.println(F(tempC));
 
}









void calibrate()
{
  float sum = 0;
  float sum1 = 0;
  float sum2 = 0;
  for (int i = 0; i < 100; i++) {
    xval[i] = float(analogRead(xpin) - 345);
    sum = xval[i] + sum;
  }
  delay(100);
  xavg = sum / 100.0;
  Serial.println(xavg);
  for (int j = 0; j < 100; j++)
  {
    yval[j] = float(analogRead(ypin) - 346);
    sum1 = yval[j] + sum1;
  }
  yavg = sum1 / 100.0;
  Serial.println(yavg);
  delay(100);
  for (int q = 0; q < 100; q++)
  {
    zval[q] = float(analogRead(zpin) - 416);
    sum2 = zval[q] + sum2;
  }
  zavg = sum2 / 100.0;
  delay(100);
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  
//  display.println("Breath : " + String(counterBreathe));
//  
//  display.println("STEPS : " + String(steps));
//  display.display();
  Serial.println(zavg);

}
