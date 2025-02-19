#include <Arduino.h>
#include <Keyboard.h>
#include <Bounce2.h>
#include <WebUSB.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

#define NUMKEYS 5

struct KeyBindings
{
  uint8_t key1[NUMKEYS] = {49};
  uint8_t key2[NUMKEYS] = {50};
  uint8_t key3[NUMKEYS] = {51};
  uint8_t key4[NUMKEYS] = {52};
};

KeyBindings bindings;

void saveToEEPROM()
{
  EEPROM.put(0, bindings);
}

void loadFromEEPROM()
{
  EEPROM.get(0, bindings);
}

String lastString;

// void updateBindings(uint8_t b1[], uint8_t b2[], uint8_t b3[], uint8_t b4[])
// {
//   // Store up to MAX_KEYS_PER_BUTTON keys per button
//   for (int i = 0; i < NUMKEYS; i++)
//   {
//     bindings.key1[i] = (i < sizeof(b1) / sizeof(b1[0])) ? b1[i] : 255; // Add 0 if not enough keys
//     bindings.key2[i] = (i < sizeof(b2) / sizeof(b2[0])) ? b2[i] : 255;
//     bindings.key3[i] = (i < sizeof(b3) / sizeof(b3[0])) ? b3[i] : 255;
//     bindings.key4[i] = (i < sizeof(b4) / sizeof(b4[0])) ? b4[i] : 255;
//   }

//   // saveToEEPROM(); // Save new bindings to EEPROM
// }

void parseAndStoreJSON(String jsonString)
{
  // Use DynamicJsonDocument to automatically handle memory allocation
  DynamicJsonDocument doc(1024); // You can set a default size, it will grow as needed

  DeserializationError error = deserializeJson(doc, jsonString);

  if (error)
  {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.f_str());
    return;
  }

  // Extract the key arrays and store them in the struct
  for (int i = 0; i < NUMKEYS; i++)
  {
    bindings.key1[i] = (!doc["1"][i].isNull() || doc["1"].size() == 0) ? doc["1"][i].as<int>() : 255;
    bindings.key2[i] = (!doc["2"][i].isNull() || doc["2"].size() == 0) ? doc["2"][i].as<int>() : 255;
    bindings.key3[i] = (!doc["3"][i].isNull() || doc["3"].size() == 0) ? doc["3"][i].as<int>() : 255;
    bindings.key4[i] = (!doc["4"][i].isNull() || doc["4"].size() == 0) ? doc["4"][i].as<int>() : 255;
  }

  saveToEEPROM(); // Save to EEPROM after parsing and storing the keys
}

WebUSB WebUSBSerial(1 /* https:// */, "https://mpschneider2.github.io/LWHS-Adaptive-Game-Controller/");

#define Serial WebUSBSerial

const int ledPin = 9;

// put function declarations here:

// const int Button1 = 2;
// const int Button2 = 3;
// const int Button3 = 4;
// const int Button4 = 5;

Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();

void setup()
{
  // put your setup code here, to run once:
  // pinMode(Button1, INPUT_PULLUP);
  // pinMode(Button2, INPUT_PULLUP);
  // pinMode(Button3, INPUT_PULLUP);
  // pinMode(Button4, INPUT_PULLUP);

  button1.attach(2, INPUT_PULLUP);
  button1.interval(20);
  button1.setPressedState(LOW);

  button2.attach(3, INPUT_PULLUP);
  button2.interval(20);
  button2.setPressedState(LOW);

  button3.attach(4, INPUT_PULLUP);
  button3.interval(20);
  button3.setPressedState(LOW);

  button4.attach(5, INPUT_PULLUP);
  button4.interval(20);
  button4.setPressedState(LOW);

  // can effectively debounce with 0.1 microfarrat capacitor
  Keyboard.begin();

  if (EEPROM.read(500) == 100)  {// some arbitrary number
    loadFromEEPROM();
  }

  // while (!Serial)
  // {
  //   ;
  // }
  // Serial.begin(9600);
  // // Serial.write("Sketch begins.\r\n> ");
  // Serial.flush();
  // pinMode(ledPin, OUTPUT);
}

void loop()
{
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  // put your main code here, to run repeatedly:

  if (button1.pressed())
  {
    // Keyboard.press('1');
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key1[i] != 255) {
        Keyboard.press(bindings.key1[i]);
      }
    }

  }
  if (button2.pressed())
  {
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key2[i] != 255) {
        Keyboard.press(bindings.key2[i]);
      }
    }
  }
  if (button3.pressed())
  {
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key3[i] != 255) {
        Keyboard.press(bindings.key3[i]);
      }
    }
  }
  if (button4.pressed())
  {
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key4[i] != 255) {
        Keyboard.press(bindings.key4[i]);
      }
    }
  }

  if (button1.released())
  {
    // Keyboard.release('1');
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key1[i] != 255) {
        Keyboard.release(bindings.key1[i]);
      }
    }
  }
  if (button2.released())
  {
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key2[i] != 255) {
        Keyboard.release(bindings.key2[i]);
      }
    }
  }
  if (button3.released())
  {
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key3[i] != 255) {
        Keyboard.release(bindings.key3[i]);
      }
    }
  }
  if (button4.released())
  {
    for (int i = 0; i < NUMKEYS; i++) {
      if (bindings.key4[i] != 255) {
        Keyboard.release(bindings.key4[i]);
      }
    }
  }

  if (Serial && Serial.available())
  {
    // int byte = Serial.read();
    // Serial.write(byte);
    // if (byte == 'H') {
    //   Serial.write("\r\nTurning LED on.");
    //   digitalWrite(ledPin, HIGH);
    // } else if (byte == 'L') {
    //   Serial.write("\r\nTurning LED off.");
    //   digitalWrite(ledPin, LOW);
    // }
    // Serial.write("\r\n> ");
    // Serial.flush();
    String str = Serial.readString();

    if (str != "" && str!= lastString) {
      parseAndStoreJSON(str);
      lastString = str;
      saveToEEPROM();
      EEPROM.update(500, 100);
      Serial.write("Success!");
      Serial.flush();
    }

    // saveToEEPROM();
  }
}