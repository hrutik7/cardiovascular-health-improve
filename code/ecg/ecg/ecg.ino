
const int buttonPin_2 = 7; 

int buttonState_2 = 0;

void setup() {
// initialize the serial communication:
Serial.begin(9600);

pinMode(5, INPUT); // Setup for leads off detection LO +
pinMode(6, INPUT); // Setup for leads off detection LO -
 
 pinMode(buttonPin_2, INPUT);
}
 
void loop() {
  buttonState_2 = digitalRead(buttonPin);
if (buttonState_2 == HIGH) {
        Serial.println(analogRead(A0));
    }

   else{
     Serial.println("Hello");
    }
}
