int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() { 
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop() { 
  setColor(random(0, 255), random(0, 255), random(0, 255));
  delay(300);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
