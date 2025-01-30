#include <Arduino.h>
#include <Keyboard.h>
#include <Bounce2.h>

// put function declarations here:

// const int Button1 = 2;
// const int Button2 = 3;
// const int Button3 = 4;
// const int Button4 = 5;

Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();

void setup() {
  // put your setup code here, to run once:
  // pinMode(Button1, INPUT_PULLUP);
  // pinMode(Button2, INPUT_PULLUP);
  // pinMode(Button3, INPUT_PULLUP);
  // pinMode(Button4, INPUT_PULLUP);

  button1.attach (2, INPUT_PULLUP);
  button1.interval(20);
  button1.setPressedState(LOW);

  button2.attach (3, INPUT_PULLUP);
  button2.interval(20);
  button2.setPressedState(LOW);

  button3.attach (4, INPUT_PULLUP);
  button3.interval(20);
  button3.setPressedState(LOW);

  button4.attach (5, INPUT_PULLUP);
  button4.interval(20);
  button4.setPressedState(LOW);

  //can effectively debounce with 0.1 microfarrat capacitor
  Keyboard.begin();
}

void loop() {
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  // put your main code here, to run repeatedly:

  if (button1.pressed()) {
    Keyboard.press('1');
  }
  if (button2.pressed()) {
    Keyboard.press('2');
  }
  if (button3.pressed()) {
    Keyboard.press('3');
  }
  if (button4.pressed()) {
    Keyboard.press('4');
  }

  if (button1.released()) {
    Keyboard.release('1');
  }
  if (button2.released()) {
    Keyboard.release('2');
  }
  if (button3.released()) {
    Keyboard.release('3');
  }
  if (button4.released()) {
    Keyboard.release('4');
  }

}