#define DATA_PIN 2
#define CLOCK_PIN 3
#define MAX_IDLE_SEC 5
#include <LiquidCrystal.h>

#define LED_PIN 5
#define BUZZER_PIN 6
#define BUTTON_PIN 7

             
int delayCounter = 0;
int delayNow = 900;
bool isOn = true;

byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";

// variables will change:
boolean buttonState = true;         // variable for reading the pushbutton status
int buttonRead = 0;

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
  lcd.setCursor(0,1);
  lcd.print("Score:");
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, display[countdown]);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  
//  attachInterrupt(0, btnListener, CHANGE);
}

void btnListener() {
  buttonRead = digitalRead(BUTTON_PIN);
  if (buttonRead == HIGH) {
    buttonState = !buttonState; 
  }
}


void playTone() {
  delayCounter += 20;
    if (isOn) {
      analogWrite(BUZZER_PIN,500);
      analogWrite(LED_PIN,delayCounter / 255);
    } else {
      analogWrite(BUZZER_PIN,0);
      analogWrite(LED_PIN,0);
    }
  
    if (delayCounter >= delayNow) {
      delayCounter = 0;
      isOn = !isOn;
      if (!isOn) {
        delayNow+= 10;
      }
    }
}

void stopTone() {
  analogWrite(BUZZER_PIN,0);
  analogWrite(LED_PIN,0);
  delayNow = 900;
  delayCounter = 0;
  isOn = true;
}


void loop() {

  // Write Score to LCD after reading from serial communication
  if(Serial.available() > 0){
    lcd.setCursor(7, 1);
    lcd.print(Serial.readString());  
  }

  buttonRead = digitalRead(BUTTON_PIN);
  if (buttonRead == HIGH) {
    buttonState = !buttonState; 
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
  
  // Print to LCD
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

  if (buttonState) {
    playTone();
  } else {
    stopTone();
  }
  
  delay(20);

}
