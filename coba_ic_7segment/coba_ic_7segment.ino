#define DATA_PIN 2
#define CLOCK_PIN 3
#define MAX_IDLE_SEC 5

byte display[] = {B10000001, B11101101, B01000011, B01001001, B00101101, B00011001};
int i = MAX_IDLE_SEC;
void setup() {
    // put your setup code here, to run once:
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, display[i]);
   i--;
   if (i < 0) {
    i = MAX_IDLE_SEC;
   }
   delay(1000);
}
