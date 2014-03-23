#include <ZumoMotors.h>
#include <Pushbutton.h>

#define MAX_SPEED 200

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

void setup()
{

}

void loop()
{
  // wait for button to start
  button.waitForButton();

  // accelerate both wheels to MAX_SPEED/2
  for (int speed = 0; speed <= MAX_SPEED/2; speed++){
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }

  // 1. Now that both wheels are at speed == MAX_SPEED/2, increase the speed of only left motor to MAX_SPEED to make right turn











  // 2. Once both wheels start moving at different speed, update delay to appropriate time here to make a 1/2 circle
  delay(1000);





  // 3. Try to spin the robot 360 here by gradually changing the speed of each wheel in opposing directions
  //    Challenge: Try to make Zumo spin in its current position instead of making another small circle
  //     a) set each motor to appropriate speed (Hint: You can set motor speed to a negative value to reverse)
  //     b) insert appropriate amount of delay













  // 4. Perform similar steps as done in #1 and #2 above to finish the trip
  //     a) set left motor speed higher than right motor
  //     b) insert appropriate amount of delay









  // decelerate both wheels to stop
  for (int speed = MAX_SPEED/2; speed >= 0; speed--){
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }

  button.waitForButton();
}
