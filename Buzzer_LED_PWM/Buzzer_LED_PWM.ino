/* Play Melody
 * -----------
 *
 * Program to play melodies stored in an array, it requires to know
 * about timing issues and about how to play tones.
 *
 * The calculation of the tones is made following the mathematical
 * operation:
 *
 *       timeHigh = 1/(2 * toneFrequency) = period / 2
 *
 * where the different tones are described as in the table:
 *
 * note         frequency       period  PW (timeHigh)   
 * c            261 Hz          3830    1915    
 * d            294 Hz          3400    1700    
 * e            329 Hz          3038    1519    
 * f            349 Hz          2864    1432    
 * g            392 Hz          2550    1275    
 * a            440 Hz          2272    1136    
 * b            493 Hz          2028    1014    
 * C            523 Hz          1912    956
 *
 * (cleft) 2005 D. Cuartielles for K3
 */

#define LED_PIN 5
#define BUZZER_PIN 6
#define BUTTON_PIN 7
             
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";
// count length: 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
//                                10                  20                  30
int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;
int statePin = LOW;

// variables will change:
boolean buttonState = true;         // variable for reading the pushbutton status
int buttonRead = 0;

void setup() {
 pinMode(LED_PIN, OUTPUT); 

  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
  
  attachInterrupt(0, pin_ISR, CHANGE);
}

void pin_ISR() {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonRead == HIGH) {
    buttonState = !buttonState;
    
  }
}

void loop() {
  if (buttonState == true) {
    analogWrite(BUZZER_PIN, 0);     
    for (count = 0; count < MAX_COUNT; count++) {
//      statePin = !statePin;
//      digitalWrite(LED_PIN, statePin);
      for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) {
        for (count2=0;count2<8;count2++) {
          if (names[count2] == melody[count*2 + 1]) {       
            analogWrite(BUZZER_PIN,500);
            delayMicroseconds(tones[count2]);
            analogWrite(BUZZER_PIN, 0);
            delayMicroseconds(tones[count2]);
          }
          if (melody[count*2 + 1] == 'p') {
            // make a pause of a certain size
            analogWrite(BUZZER_PIN, 0);
            delayMicroseconds(500);
          }
          if (buttonState == true)
            break;
        }
        if (buttonState == true)
          break;
      }
    }
  
  }

  
}
