#include <ZumoBuzzer.h>
#include <Pushbutton.h>

/*
 * This example uses the ZumoBuzzer library to play a series of notes on
 * the buzzer.  It also uses Pushbutton library to allow the user to
 * stop/reset the melody with the user pushbutton.
 */

#define MELODY_LENGTH 95

// These arrays take up a total of 285 bytes of RAM (out of a limit of 1k (ATmega168), 2k (ATmega328), or 2.5k(ATmega32U4))
unsigned char note[MELODY_LENGTH] = 
{
  NOTE_E(5), 
  NOTE_D(5), 
  NOTE_E(5), 
  NOTE_D(5),
  NOTE_E(5), 
  NOTE_E(5), 
  NOTE_G(5),
  SILENT_NOTE,
  NOTE_A(5),
  NOTE_D(5),
  NOTE_D(5),
  NOTE_C(5),
  NOTE_D(5),
  NOTE_C(5),
  NOTE_E(5),
  NOTE_C(5),
  NOTE_D(5),
  NOTE_E(5),
  NOTE_C(5),
  NOTE_C(5),
  SILENT_NOTE,
  NOTE_E(5),
  NOTE_C(5),
  NOTE_C(5),
  SILENT_NOTE,
  SILENT_NOTE
};

unsigned int duration[MELODY_LENGTH] =
{
  250, 250, 250, 250, 250, 500, 750, 250, 250, 500, 250, 250,

  250, 500, 500, 500, 750, 500, 250, 250, 3000, 500, 250, 250, 3000
};

ZumoBuzzer buzzer;
Pushbutton button(ZUMO_BUTTON);
unsigned char currentIdx;

void setup()                    // run once, when the sketch starts
{
  currentIdx = 0;
}

void loop()                     // run over and over again
{
  // if we haven't finished playing the song and 
  // the buzzer is ready for the next note, play the next note
  if (currentIdx < MELODY_LENGTH && !buzzer.isPlaying())
  {
    // play note at max volume
    buzzer.playNote(note[currentIdx], duration[currentIdx], 15);
    currentIdx++;
  }

  // Insert some other useful code here...
  // the melody will play normally while the rest of your code executes
  // as long as it executes quickly enough to keep from inserting delays
  // between the notes.
  
  // For example, let the user pushbutton function as a stop/reset melody button
  if (button.isPressed())
  {
    buzzer.stopPlaying(); // silence the buzzer
    if (currentIdx < MELODY_LENGTH)
      currentIdx = MELODY_LENGTH;        // terminate the melody
    else
      currentIdx = 0;                    // restart the melody
    button.waitForRelease();  // wait here for the button to be released
  }
}
