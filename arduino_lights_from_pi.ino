#include <FastLED.h>
#include <TimeLib.h>
#define LED_PIN     2

// Information about the LED strip itself
#define NUM_LEDS    384
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  128


// FastLED v2.1 provides two color-management controls:
//   (1) color correction settings for each LED strip, and
//   (2) master control of the overall output 'color temperature' 
//
// THIS EXAMPLE demonstrates the second, "color temperature" control.
// It shows a simple rainbow animation first with one temperature profile,
// and a few seconds later, with a different temperature profile.
//
// The first pixel of the strip will show the color temperature.
//
// HELPFUL HINTS for "seeing" the effect in this demo:
// * Don't look directly at the LED pixels.  Shine the LEDs aganst
//   a white wall, table, or piece of paper, and look at the reflected light.
//
// * If you watch it for a bit, and then walk away, and then come back 
//   to it, you'll probably be able to "see" whether it's currently using
//   the 'redder' or the 'bluer' temperature profile, even not counting
//   the lowest 'indicator' pixel.
//
//
// FastLED provides these pre-conigured incandescent color profiles:
//     Candle, Tungsten40W, Tungsten100W, Halogen, CarbonArc,
//     HighNoonSun, DirectSunlight, OvercastSky, ClearBlueSky,
// FastLED provides these pre-configured gaseous-light color profiles:
//     WarmFluorescent, StandardFluorescent, CoolWhiteFluorescent,
//     FullSpectrumFluorescent, GrowLightFluorescent, BlackLightFluorescent,
//     MercuryVapor, SodiumVapor, MetalHalide, HighPressureSodium,
// FastLED also provides an "Uncorrected temperature" profile
//    UncorrectedTemperature;

#define TEMPERATURE_1  DirectSunlight
#define TEMPERATURE_2 HighPressureSodium

// How many seconds to show each temperature before switching
#define DISPLAYTIME 20
// How many seconds to show black between switches
#define BLACKTIME   3

void loop()
{

//if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.println("read"+ data);
    if(data=="true"){
      lightsOn();
      Serial.println("i turned the lights on");
    }
    
 /* if(serialWriteRead()){

 // static uint8_t starthue = 0;

  lightsOn();
}
*/
else
{
  Serial.println("turning off");
 turnOff();
 Serial.println("i turned the lights off");
}
//}
//delay( 3000 );
  //FastLED.delay(8);
  Serial.println("end loop");
}

void lightsOn(){
  
for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
   leds[i] = CHSV(0,0,0);
    leds[i] = TEMPERATURE_2; // show indicator pixel
  
}
  
  FastLED.show();
  
}

void turnOff(){
   FastLED.clear();
  fill_solid(leds,NUM_LEDS, 0);
  FastLED.show();
}



void setup() {
  delay( 3000 ); // power-up safety delay
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  Serial.begin(9600);
}
