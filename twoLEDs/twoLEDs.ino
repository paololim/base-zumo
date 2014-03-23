
const int ledOne = 8; 
const int ledTwo = 9;     
const int ledThree = 10;

void setup() {
  // initialize the LED pins as an outputs:
  pinMode(ledOne, OUTPUT);      
  pinMode(ledTwo, OUTPUT);      
  pinMode(ledThree, OUTPUT);      
}

void loop(){
  blinkLed(ledOne, 100);
  blinkLed(ledTwo, 100);
  blinkLed(ledThree, 100);

  blinkLed(ledOne, 100);
  blinkLed(ledTwo, 100);
  blinkLed(ledThree, 100);

  turnOn(ledOne);
  turnOn(ledTwo);
  turnOn(ledThree);
  delay(700);
  turnOff(ledOne);
  turnOff(ledTwo);
  turnOff(ledThree);
}

void blinkLed(int ledPin, int lightTimeOn){
  turnOn(ledPin);
  delay(lightTimeOn);
  turnOff(ledPin);
}

void turnOn(int ledPin){
  digitalWrite(ledPin, HIGH); 
}

void turnOff(int ledPin){
  digitalWrite(ledPin, LOW);
}
