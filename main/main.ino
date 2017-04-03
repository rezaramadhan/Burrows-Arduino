#define DATA_PIN 2
#define CLOCK_PIN 3
#define MAX_IDLE_SEC 5
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9,10,11,12,13);

byte display[] = {B10000001, B11101101, B01000011, B01001001, B00101101, B00011001};
int countdown = MAX_IDLE_SEC;
int iter = 1;

void setup() { 
  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("Welc. to Burrows!");
  
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, display[countdown]);
}

void loop() {

  // Write Score to LCD after reading from serial communication
  if(Serial.available() > 0){
    lcd.setCursor(0, 1);
    lcd.print(Serial.readString());  
  }


  // read from LDR, send to unity
  int LDR1 = analogRead(A0);
  int LDR2 = analogRead(A1);
  int LDR3 = analogRead(A2);
  if (LDR1 > 200 && LDR2 > 200 && LDR3 > 200) {
    Serial.write(7);
    iter++;
  } else {
    iter = 0;
    if (LDR1 > 200 && LDR2 <= 200 && LDR3 <= 200) {
      Serial.write(1);
    } else if (LDR1 <= 200 && LDR2 > 200 && LDR3 <= 200) {
      Serial.write(2);
    } else if (LDR1 <= 200 && LDR2 <= 200 && LDR3 > 200) {
      Serial.write(3);
    } else if (LDR1 > 200 && LDR2 > 200 && LDR3 <= 200) {
      Serial.write(4);
    } else if (LDR1 > 200 && LDR2 <= 200 && LDR3 > 200) {
      Serial.write(5);
    } else if (LDR1 <= 200 && LDR2 > 200 && LDR3 > 200) {
      Serial.write(6);
    } else if (LDR1 <= 200 && LDR2 <= 200 && LDR3 <= 200) {
      Serial.write(0);
    }
  }
  delay(20);

  if (iter == 0) {
    countdown = MAX_IDLE_SEC;
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, display[countdown]);  
  } else if (iter >= 50) {
    countdown--;
    if (countdown < 0) {
      countdown = MAX_IDLE_SEC;
    }
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, display[countdown]);
    iter = 1;
  }
}
