#define a 4
#define b 5
#define c A3
#define d A4
#define e A5
#define f 3
#define g 2

void showDigit(int digit){
  
}

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
LiquidCrystal lcd(8,9,10,11,12,13);

void setup() { 
  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("Welc. to Burrows!");
  
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  
  
}

void loop() {
  if(Serial.available() > 0){
    lcd.setCursor(0, 1);
    lcd.print(Serial.readString());  
  }
  
  int LDR1 = analogRead(A0);
  int LDR2 = analogRead(A1);
  int LDR3 = analogRead(A2);
//  Serial.print(LDR1);
//  Serial.print(" ");
//  Serial.print(LDR2);
//  Serial.print(" ");
//  Serial.println(LDR3);
//  delay(500);
  if (LDR1 <= 200 && LDR2 <= 200 && LDR3 <= 200) {
    Serial.write(0);
    //Serial.println('0');
  }

  else if (LDR1 > 200 && LDR2 <= 200 && LDR3 <= 200) {
    Serial.write(1);
    //Serial.println('1');
  }

  else if (LDR1 <= 200 && LDR2 > 200 && LDR3 <= 200) {
    Serial.write(2);
    //Serial.println('2');
  }

  else if (LDR1 <= 200 && LDR2 <= 200 && LDR3 > 200) {
    Serial.write(3);
    //Serial.println('3');
  }

  else if (LDR1 > 200 && LDR2 > 200 && LDR3 <= 200) {
    Serial.write(4);
    //Serial.println('4');
  }

  else if (LDR1 > 200 && LDR2 <= 200 && LDR3 > 200) {
    Serial.write(5);
    //Serial.println('5');
  }

  else if (LDR1 <= 200 && LDR2 > 200 && LDR3 > 200) {
    Serial.write(6);
    //Serial.println('6');
  }
  
  else if (LDR1 > 200 && LDR2 > 200 && LDR3 > 200) {
    Serial.write(7);
    //Serial.println('7');
  }
  delay(20);

//    for(int i = 0; i < 10; i++ ){
//      showDigit(i);
//      delay(500);
//    }
}
