#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <DFPlayer.h>
#include <DFPlayerSerial.h>


#define PIXEL_PIN A0
#define TRIGGER_PIN 11
#define AUX_PIN 12
int state = 0;
int scopeState = 0;
int numOfLEDs = 4;
bool oldState = HIGH;
int scopSelect = 0;
int lastButtonState_aux = 0;
int lastButtonState_trigger = 0;   ///// not used yet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//sets sound pins and creats DFPlayer object
#define DFPLAYER_RX 8
#define DFPLAYER_TX 7
DFPlayer myDFPlayer;

uint8_t track = 0001; //FOR TESTING - sets the file to play

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfLEDs, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(64);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(11,INPUT);
  digitalWrite(11, LOW);
  pinMode(12,INPUT);
  digitalWrite(12, LOW);
  ///LED setup
  strip.setPixelColor(1, 50, 0, 200);
  strip.setPixelColor(2, 255, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.show();
  ///Sound setup
  myDFPlayer.setSerial(DFPLAYER_TX, DFPLAYER_RX);
  myDFPlayer.setVolume(40);

}

void loop() {

  ////////////////////////////
  // Trigger pull operation //
  ////////////////////////////
  state = digitalRead(TRIGGER_PIN);
  scopeState = digitalRead(AUX_PIN);
  //Serial.print("state is: " + state);
  if (state == LOW) {
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
    //Serial.println("its low");
  }
  else {
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    myDFPlayer.playPhysicalTrack(track);
    //dfpExecute(0x0f,0x01,0x01);
    Serial.println("Trigger pull");
  }
  
  ////////////////////////////////////////
  // Sets the color of the scope optics //
  ////////////////////////////////////////
  if (scopeState != lastButtonState_aux) {
    if (scopeState == HIGH) {
      Serial.println("Aux button push");
      lastButtonState_aux = scopeState;
      if (scopSelect == 0) {
        scopSelect = 1;
        strip.setPixelColor(2, 255, 0, 0);
        strip.setPixelColor(3, 0, 0, 0);
        strip.show();
      }
      else if (scopSelect == 1) {
        scopSelect = 0;
        strip.setPixelColor(2, 0, 0, 0);
        strip.setPixelColor(3, 0, 0, 255);
        strip.show();
      }
    }
    else {
      lastButtonState_aux = scopeState;
    }
  }
  delay(5000);
}
