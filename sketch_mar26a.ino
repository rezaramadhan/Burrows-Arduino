#define a 4
#define b 5
#define c A3
#define d A4
#define e A5
#define f 3
#define g 2

void showDigit(int digit){
  switch (digit){
    case 0:
    digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW);digitalWrite(e,LOW);digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
    break;
    case 1:
    digitalWrite(b,LOW);digitalWrite(c,LOW);
    digitalWrite(a,HIGH);digitalWrite(d,HIGH);digitalWrite(e,HIGH);digitalWrite(f,HIGH);digitalWrite(g,HIGH);
    break;
    case 2:
    digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(d,LOW);digitalWrite(e,LOW);digitalWrite(g,LOW);
    digitalWrite(c,HIGH);digitalWrite(f,HIGH);
    break;
    case 3:
    digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW);digitalWrite(g,LOW);
    digitalWrite(e,HIGH);digitalWrite(f,HIGH);
    break;
    case 4:
    digitalWrite(b,LOW);digitalWrite(c,LOW);digitalWrite(f,LOW);digitalWrite(g,LOW);
    digitalWrite(a,HIGH);digitalWrite(d,HIGH);digitalWrite(e,HIGH);
    break;
    case 5:
    digitalWrite(a,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW);digitalWrite(f,LOW);digitalWrite(g,LOW);
    digitalWrite(b,HIGH);digitalWrite(e,HIGH);
    break;
    case 6:
    digitalWrite(a,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW);digitalWrite(e,LOW);digitalWrite(f,LOW);digitalWrite(g,LOW);
    digitalWrite(b,HIGH);
    break;
    case 7:
    digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(c,LOW);
    digitalWrite(d,HIGH);digitalWrite(e,HIGH);digitalWrite(f,HIGH);digitalWrite(g,HIGH);
    break;
    case 8:
    digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW);digitalWrite(e,LOW);digitalWrite(f,LOW);digitalWrite(g,LOW);
    break;
    case 9:
    digitalWrite(a,LOW);digitalWrite(b,LOW);digitalWrite(c,LOW);digitalWrite(d,LOW);digitalWrite(f,LOW);digitalWrite(g,LOW);
    digitalWrite(e,HIGH);
    break;
  }
}

void setup() {
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
    showDigit(Serial.read());  
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
