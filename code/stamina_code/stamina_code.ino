void setup() {
  Serial.begin(9600);
  pinMode(10,INPUT);
 pinMode(11,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 //Serial.println(analogRead(A0));
  if((digitalRead(10) == 1) || (digitalRead(11) ==1)) {
    Serial.println('!');
    }
   else{
      Serial.println(analogRead(A1));
    }
    delay(100);
}
