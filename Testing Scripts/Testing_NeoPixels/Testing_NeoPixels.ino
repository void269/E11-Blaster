/*What am I trying to figure out:
 * Can I run NeoPixel LEDs (individually addressable LEDs) off the A0 pin
 * 
 * What are the test parameters:
 * 4 NeoPixels
 * All NeoPixels are connected in a series
 * LED0 is momentarally turned on by pin D11
 * LED1 is always on with power
 * LED2 and LED3 toggle back and forth with pin D12
 * Data pin is connected to pin A0
 * 
 * Did it work:
 * Yes
 * this sets the color to use -> strip.setPixelColor(1, 50, 0, 200);
 *                                                   |  |   |  |_> Blue 0-255
 *                                                   |  |   |____> Green 0-255
 *                                                   |  |________> Red 0-255
 *                                                   |___________> LED number starting at 0 from closest to the board out
 * then using this apply the color to the LED -> strip.show();
 * 
 * Notes:
 * I needed to add a 10k resister (a smaller one my work too, thats just what I had laying around) from pins D11 and D12 to Ground.
 * Otherwise there was noise on the pins causing them to act as if they were bein supplied with 5v
 */

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN A0
#define TRIGGER_PIN 11
#define AUX_PIN 12
int triggerState = 0;
int scopeState = 0;
int numOfLEDs = 4; //this tells the Adafruit NeoPixel library how many LED's are connected together
int scopSelect = 0;
int lastButtonState_aux = 0;
int lastButtonState_trigger = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfLEDs, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(64);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.println("Start up");
  pinMode(TRIGGER_PIN,INPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(AUX_PIN,INPUT);
  digitalWrite(AUX_PIN, LOW);
  ///LED setup
  strip.setPixelColor(1, 50, 0, 200); //blue with a bit of red, I just like the color ;-)
  strip.setPixelColor(2, 255, 0, 0);  //full red
  strip.setPixelColor(3, 0, 0, 0);    // off
  strip.show();


}

void loop() {
  ////////////////////
  // Variable setup //
  ////////////////////
  triggerState = digitalRead(TRIGGER_PIN);
  scopeState = digitalRead(AUX_PIN);
  //Serial.print("state is: " + triggerState);
  
  /////////////////////////////////////////////////////////
  // Waits for the D11/TRIGGER_PIN to be connected to 5v //
  // When it is it will light up LED0 red                //
  /////////////////////////////////////////////////////////
  if (triggerState == LOW) {
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
    Serial.println("its low");
  }
  else {
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    Serial.println("Trigger pull");
  }
  
  /////////////////////////////////////////////////////////////////////////
  // Waits for the D12/AUX_PIN to be connected to 5v                     //
  // When it is it will toggle LED2 and 3, they are seto to Blue and Red //
  /////////////////////////////////////////////////////////////////////////
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

  ///////////////////////////////////////////
  // added delay to slow things down a bit //
  ///////////////////////////////////////////
  delay(100);
}
