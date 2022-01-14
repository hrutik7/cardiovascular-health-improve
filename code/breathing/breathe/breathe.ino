int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
const int xpin = A5;
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
calibrate();

}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
for (int w = 0; w < 16; w++) {
    
    delay(500);
  }
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
    Serial.println("totave[a]");
    Serial.println(totave[a]);
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
    Serial.println('\n');
    Serial.print("steps: ");
    Serial.println(steps);
   
    delay(1000);
    
  }
  delay(1000);
//  Serial.print("Temperature: "); 
//  Serial.print(T);
//  Serial.println(" F"); 
  if(T != -459.67 ){
      int breathe = 0;
      Serial.println(breathe + 1);
    }
  delay(50);
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
  Serial.println(zavg);
}
