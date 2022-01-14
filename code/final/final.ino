
int TR_PIN = A0;
double a1, b1, c1, d1, r2, r1, vo, tempC, tempF, tempK;
float counterBreathe = 0;
const int xpin = A3;
const int ypin = A6;
const int zpin = A7;

int Dignouse;


float threshold = 6;
int xval[100] = {0};
int yval[100] = {0};
int zval[100] = {0};
int xavg, yavg, zavg;
int steps, flag = 0;

const int buttonPin = 2;     // the number of the pushbutton pin

const int buttonPin_1 = 3;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonState_1 = 0;         // variable for reading the pushbutton status
void setup()
{
  Serial.begin(9600);

  a1 = 3.354016E-03 ;
  b1 = 2.569850E-04 ;
  c1 = 2.620131E-06 ;
  d1 = 6.383091E-08 ;

  r1 = 9720.0;

 pinMode(buttonPin, INPUT);
  
  delay(100);
  pinMode(TR_PIN, INPUT);
 calibrate();
}

void loop()
{

 buttonState = digitalRead(buttonPin);
  buttonState_1 = digitalRead(buttonPin_1);
  Serial.println(buttonState);
 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
        start();
    }
    Serial.println("inside void loop");
  } 


 
void start(){
  Serial.println("Button is pressed");
   for(;;){
    Serial.println("Im in for loop");
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
  
 
    vo = analogRead(TR_PIN);
  vo = vo / (1023.0 / 5.0);

//   voltage divider calculation
//   vo = 5 * r2 /(r1+r2);
   //solve for r2
  // get the exact value for voltage divider r1
//
  r2 = ( vo * r1) / (5.0 - vo);
//
  //equation from data sheet
  tempK = 1.0 / (a1 + (b1 * (log(r2 / 10000.0))) + (c1 * pow(log(r2 / 10000.0), 2.0)) + (d1 * pow(log(r2 / 10000.0), 3.0)));
  tempC  = (tempK - 273.15);
   Serial.println("tempC : " + String(tempC));
   Serial.println("steps : " + String(steps));

 delay(1000);

  

  if(tempC <= 25.00 && tempC >=24.00){
  counterBreathe = counterBreathe + 1;
 Serial.println("breathe : " +  String(counterBreathe));
   
}
   

// 
//  
  
//    
 Serial.println("buttonState_1 : " +  String(buttonState_1));
 if (buttonState_1 == HIGH) {

   if(steps == counterBreathe){
         Serial.println("session end :");
         delay(1000);
          Serial.print("Result : ");
         Serial.println("that was good run");
         delay(2000);
           break;
      }
     else if(steps > counterBreathe ){
         Dignouse = steps - counterBreathe;
          Serial.println("session end :");
         delay(1000);
          Serial.print("Result : ");
         Serial.println("that was good run");
         delay(2000);
         Serial.println("you are breathing slow");
         Serial.println("increment in No. of breath : " + String(Dignouse));
           break;
        }
     else if(steps < counterBreathe ){
        Dignouse = counterBreathe - steps ;
         Serial.println("session end :");
         delay(1000);
          Serial.print("Result : ");
         Serial.println("that was good run");
         delay(2000);
        
         Serial.println("you are breathing fast");
         Serial.println("Decrement in No. of breath : " + String(Dignouse));
           break;
        }

 }
  
  }
  
  
  // read the temp
//  vo = analogRead(TR_PIN);
//  vo = vo / (1023.0 / 5.0);
//
//  // voltage divider calculation
//  // vo = 5 * r2 /(r1+r2)
// // solve for r2
//  // get the exact value for voltage divider r1//
//  r2 = ( vo * r1) / (5.0 - vo);
//
//  //equation from data sheet
//  tempK = 1.0 / (a1 + (b1 * (log(r2 / 10000.0))) + (c1 * pow(log(r2 / 10000.0), 2.0)) + (d1 * pow(log(r2 / 10000.0), 3.0)));
//  tempC  = (tempK - 273.15);
// 
//  if(tempC <= 24.62 && tempC >=24.00){
//  counterBreathe = counterBreathe + 1;
//
//  }
 break;
 } 
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

  for (int j = 0; j < 100; j++)
  {
    yval[j] = float(analogRead(ypin) - 346);
    sum1 = yval[j] + sum1;
  }
  yavg = sum1 / 100.0;
  
  delay(100);
  for (int q = 0; q < 100; q++)
  {
    zval[q] = float(analogRead(zpin) - 416);
    sum2 = zval[q] + sum2;
  }
  zavg = sum2 / 100.0;
 
}
