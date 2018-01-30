#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


void setup() {
  // put your setup code here, to run once:
  pinMode(12, INPUT);
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println("System booting");

}

void loop() {
  // put your main code here, to run repeatedly:
  int trigger = digitalRead(12);
  //Serial.println(trigger);
  

  if (trigger == LOW) {
    myDFPlayer.next();
    Serial.println("Trigger pulled");
  }
delay(1000);
}
