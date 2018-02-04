// at 3v the best analogWrite is 100(low), 150(med), 200(high), 255(extreme)
// although 100 may be too low to use but anything below that and the motor wont turn
// running at 5v, although would be nice, will brown out the board and cuase it to reboot :(




#define LS1       3
#define LS2       5
#define LS3       6

int step = 0;

void setup() {
  pinMode(LS1, OUTPUT);
  pinMode(LS2, OUTPUT);
  pinMode(LS3, OUTPUT);
  //digitalWrite(LS1,HIGH);
  //digitalWrite(LS2,HIGH);
  //digitalWrite(LS3,HIGH);
  Serial.begin(9600);
}

void loop() {
    Serial.println(100);
    analogWrite(LS2,100);
    delay(3000);
    Serial.println(150);
    analogWrite(LS2,150);
    delay(3000);
    Serial.println(200);
    analogWrite(LS2,200);
    delay(3000);
    Serial.println(255);
    analogWrite(LS2,255);
    delay(3000);
    
    //analogWrite(LS1,255);
    //digitalWrite(LS1,HIGH);
}
