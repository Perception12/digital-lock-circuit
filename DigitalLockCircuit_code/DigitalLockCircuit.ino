#include <LiquidCrystal.h>
#include <Keypad.h>

#define RED_LED 9
#define GREEN_LED 8
#define RELAY 10 // Lock Relay or Motor

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// 4 rows
const byte ROWS = 4;
// 4 columns
const byte COLS = 4;

// define symbols on the buttons of the keypad
char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

// connect to the row pinouts of the keypsd
byte rowPins[ROWS] = {3, 2, A5, A4};
// connect to the column pinouts of the keypad
byte colPins[COLS] = {A3, A2, A1, A0};

// initialize an instance of class Keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char keyCount = 0;
char code[4]; // Hold pressed keys


void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);

  lcd.begin(16, 2);

  lcd.print("Password Access:");
  lcd.setCursor(0,1);
  lcd.cursor();

  digitalWrite(GREEN_LED, HIGH); // Turn green led off
  digitalWrite(RED_LED, LOW); // Turn red led on
  digitalWrite(RELAY, LOW); // Turn off relay (Locked)

}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey && (keyCount < 4) && (customKey != '=') && (customKey != 'C')) {
    code[keyCount] = customKey;
    // lcd.print(customKey);
    lcd.print("*"); // To display hidden entered keys
    keyCount++;
  }

  if (customKey == 'C') {
    lock(); // Lock and clear display
  }

  if (customKey == '=') { // Check Password and unlock
    if ((code[0] == '2') && (code[1] == '0') && (code[2] == '2') && (code[3] == '2')) { // Password is 2022
      lcd.setCursor(0,1);
      lcd.print("Door Open       ");
      digitalWrite(GREEN_LED, LOW); // Turn green on
      digitalWrite(RED_LED, HIGH); // Turn red off
      digitalWrite(RELAY, HIGH); // Turn on relay (unlocked)

      delay(4000); // Keep door open for 4 seconds
      lock();
    } else {
      lcd.setCursor(0,1);
      lcd.print("Invalid Password");
      delay(1500);
      lock();
    }
  }
}



void lock() {
  lcd.setCursor(0, 1);
  lcd.print("Door locked       ");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("              "); // Clear
  lcd.setCursor(0, 1);
  keyCount = 0;
  digitalWrite(GREEN_LED, HIGH); // Turn off green led
  digitalWrite(RED_LED, LOW); // Turn on red led
  digitalWrite(RELAY, LOW); // Turn off relay
}
