int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() { 
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  Serial.begin(9600);
}

void loop() { 
  
  for (int i = 0; i < 100; i++) { 
    int red = abs(cos(i*2*PI/100)*255);
    int green = abs(cos(((1.0/3)*PI) + (i*2*PI/100))*255);
    int blue = abs(cos(((2.0/3)*PI) + (i*2*PI/100))*255);
    setColor(red, green, blue);
    delay(50);
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
