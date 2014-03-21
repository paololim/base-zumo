/*
 * Demo line-following code for the Pololu Zumo Robot
 *
 * This code will follow a black line on a white background, using a
 * PID-based algorithm.  It works decently on courses with smooth, 6"
 * radius curves and has been tested with Zumos using 30:1 HP and
 * 75:1 HP motors.  Modifications might be required for it to work
 * well on different courses or with different motors.
 *
 * http://www.pololu.com/catalog/product/2506
 * http://www.pololu.com
 * http://forum.pololu.com
 */

// LINE FOLLOWER + BUZZER MARIO

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

#define MELODY_LENGTH 95

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
unsigned char currentIdx;

// This is the maximum speed the motors will be allowed to turn.
const int MAX_SPEED = 150; // TODO: What happens when we adjust MAX_SPEED?

// These arrays take up a total of 285 bytes of RAM (out of a limit of 1k (ATmega168), 2k (ATmega328), or 2.5k(ATmega32U4))
unsigned char note[MELODY_LENGTH] = 
{
  NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_C(5), NOTE_E(5),
  NOTE_G(5), SILENT_NOTE, NOTE_G(4), SILENT_NOTE,
  NOTE_C(5), NOTE_G(4), SILENT_NOTE, NOTE_E(4), NOTE_A(4), NOTE_B(4), NOTE_B_FLAT(4), NOTE_A(4), NOTE_G(4),
  NOTE_E(5), NOTE_G(5), NOTE_A(5), NOTE_F(5), NOTE_G(5), SILENT_NOTE, NOTE_E(5), NOTE_C(5), NOTE_D(5), NOTE_B(4),
  NOTE_C(5), NOTE_G(4), SILENT_NOTE, NOTE_E(4), NOTE_A(4), NOTE_B(4), NOTE_B_FLAT(4), NOTE_A(4), NOTE_G(4),
  NOTE_E(5), NOTE_G(5), NOTE_A(5), NOTE_F(5), NOTE_G(5), SILENT_NOTE, NOTE_E(5), NOTE_C(5), NOTE_D(5), NOTE_B(4),
  SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE,
  NOTE_G_SHARP(4), NOTE_A(4), NOTE_C(5), SILENT_NOTE, NOTE_A(4), NOTE_C(5), NOTE_D(5),
  SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE,
  NOTE_C(6), SILENT_NOTE, NOTE_C(6), SILENT_NOTE, NOTE_C(6),
  SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE,
  NOTE_G_SHARP(4), NOTE_A(4), NOTE_C(5), SILENT_NOTE, NOTE_A(4), NOTE_C(5), NOTE_D(5),
  SILENT_NOTE, NOTE_E_FLAT(5), SILENT_NOTE, NOTE_D(5), NOTE_C(5)
};

unsigned int duration[MELODY_LENGTH] =
{
  100, 25, 125, 125, 125, 125, 125, 250, 250, 250, 250, 250,
  375, 125, 250, 375, 250, 250, 125, 250, 167, 167, 167, 250, 125, 125,
  125, 250, 125, 125, 375,
  375, 125, 250, 375, 250, 250, 125, 250, 167, 167, 167, 250, 125, 125,
  125, 250, 125, 125, 375,
  250, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  250, 125, 125, 125, 250, 125, 125, 200, 50, 100, 25, 500,
  250, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  250, 250, 125, 375, 500
};

void setup()
{
  currentIdx = 0;

  // Initialize the reflectance sensors module
  reflectanceSensors.init();

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Turn on LED to indicate we are in calibration mode
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);

  // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);
  buzzer.play(">g32>>c32");

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  
  while(buzzer.isPlaying());
}

/**
* Actual infinite loop here
*/
void loop()
{
  // TODO: Add code line to make zumo start playing a song
  
  // TODO: Add code line to make zumo start following black line
}

void playSong()
{
  /**
  * Make it play a song
  */
  // if we haven't finished playing the song and the buzzer is ready for the next note, play the next note
  if (currentIdx < MELODY_LENGTH && !buzzer.isPlaying())
  {
    // play note at max volume
    buzzer.playNote(note[currentIdx], duration[currentIdx], 10);
    
    // TODO: After playing a note, make the light blink on and off
    
    currentIdx++;
  } else if (currentIdx == MELODY_LENGTH) {
    currentIdx = 0;
    
    // TODO: When music ends, make ZUMO rotate 180 degrees
    
    // TODO: Add line to wait for a button to make zumo continue and go other way
  }
}

void followLine()
{
  /**
  * Line follower look stuff here
  */
  unsigned int sensors[6];

  // Get the position of the line.  Note that we *must* provide the "sensors"
  // argument to readLine() here, even though we are not interested in the
  // individual sensor readings
  int position = reflectanceSensors.readLine(sensors);

  // Our "error" is how far we are away from the center of the line, which corresponds to position 2500.
  int error = position - 2500;

  // Get motor speed difference using proportional and derivative PID terms
  // (the integral term is generally not very useful for line following).
  // Here we are using a proportional constant of 1/4 and a derivative
  // constant of 6, which should work decently for many Zumo motor choices.
  // You probably want to use trial and error to tune these constants for
  // your particular Zumo and line course.
  int speedDifference = error / 4 + 6 * (error - lastError);
  lastError = error;

  // Get individual motor speeds.  The sign of speedDifference
  // determines if the robot turns left or right.
  int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;

  // Here we constrain our motor speeds to be between 0 and MAX_SPEED.
  // Generally speaking, one motor will always be turning at MAX_SPEED
  // and the other will be at MAX_SPEED-|speedDifference| if that is positive,
  // else it will be stationary.  For some applications, you might want to
  // allow the motor speed to go negative so that it can spin in reverse.
  if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > MAX_SPEED)
    m1Speed = MAX_SPEED;
  if (m2Speed > MAX_SPEED)
    m2Speed = MAX_SPEED;

  motors.setSpeeds(m1Speed, m2Speed);
}
