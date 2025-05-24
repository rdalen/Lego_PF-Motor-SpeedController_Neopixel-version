/* This sketch controls two DC Motors with DRV8833 Motor Driver for the 32MHz LGT8F328P chip (ATMEGA328P upgrade) 
 * The PWM pins of the 328-SSOP20 (pseudo Pro mini) are
 * D3,D5 (also RxD - so no serial monitor possible), D6 (also TxD), D9, D10/D11, 
 *
 * To select the boards:
 * 1 - select LGTF328 board
 * 2 - select the variant 328-LQFP32 for the nano or the Pro mini stype
       or 328-SSOP20 for the pseudo Pro mini style

 * 3 - select the clock source Internal 32MHz
 * 4 - Select the clock divider factor; 2 (16Mhz clock because of the NeoPixel library
 * 5 - select the port
 * 
 * See https://wolles-elektronikkiste.de/en/minievb-boards-an-overview
 * and https://github.com/dbuezas/lgt8fx?tab=readme-ov-file
 * 
 * Rotary.h; https://github.com/buxtronix/arduino/tree/master/libraries/Rotary
 */


#include <Adafruit_NeoPixel.h>
#include "Rotary.h"  //this library solves the bounching issue with a state machine

#define RE_DT 14  // Rotary encoder signal DT (output A)
#define RE_CLK 15  // Rotary encoder signal CLK (output B)
#define RE_BUTTON 12 // for possible Rotary encoder button | active LOW
#define RE_MAX HALFSCALE // Count value of the half rotation of the Rotary encoder - will be scaled to a PWM value from 0-255
#define PWM_MAX 255

//Change OUTPUTA and OUTPUTB to change the RotaryEncoder direction
#define OUTPUTB RE_CLK //... also known as
#define OUTPUTA RE_DT

#define LONGPRESSTIME 2000 // for possible Rotary encoder button

//Rotery encoder instantiation
// The Rotary encoder is wired with the common to ground and the two outputs to pins OUTPUTA and OUTPUTB.
Rotary rotary = Rotary(OUTPUTA, OUTPUTB);

// Define the control inputs | Hence; the PWM pins of the arduino Uno/Nano/mini are; 3, 5, 6, 9, 10, 11
// SLEEP pin must be pulled HIGH
#define MOT_A1_PIN 10
#define MOT_A2_PIN 9

#define PIN_NEO_PIXEL 7  // Arduino pin that connects to NeoPixel ring
#define NUM_PIXELS 16 // The number of LEDs (pixels) on NeoPixel ring
#define HALFSCALE NUM_PIXELS/2 //Half scale of the Neopixel ring (is stop)
#define BRIGHTNESS 25 //default on scale 0-255
#define BRIGHNESS_STEP 25
#define COLORGREEN 0,255,0
#define COLORRED 255,0,0
#define COLORBLUE 0,0,255

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800); // set the NeoPixel ring initialization

int RE_counter = 0; // Rotary encoder counter
int valuePMW; // PWM value
int valuePMWlast = 0; 
bool buttonREActive;
bool longPressREActive;
long buttonRETimer;
int neoBrightness = BRIGHTNESS;

void setup() {

  // Initialize the serial UART
  Serial.begin(115200);
  Serial.println("start sketch");

  NeoPixel.begin();  // initialize the NeoPixel strip object
  NeoPixel.clear(); NeoPixel.show(); // reset all pixels  
  delay(500);
  NeoPixel.setPixelColor(0, NeoPixel.Color(COLORBLUE));  // set pixel 0 to blue as power on indication
  NeoPixel.setBrightness(BRIGHTNESS);  
  NeoPixel.show(); // show all the set pixels on neopixel ring
 
  Serial.print("Number of Pixels "); Serial.println(NUM_PIXELS);
  Serial.print("Half scale "); Serial.println(HALFSCALE);
  
  // Set the Rotary Encoder pins to INPUT
  pinMode(RE_BUTTON, INPUT_PULLUP);  //for possible Rotary encoder button | active LOW
//  pinMode (OUTPUTA,INPUT_PULLUP); // Rotary encoder OUTPUTA signal
//  pinMode (OUTPUTB,INPUT_PULLUP); // Rotary encoder OUTPUTB signal

  // Set all the motor control pins to OUTPUT
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
//  pinMode(MOT_B1_PIN, OUTPUT);
//  pinMode(MOT_B2_PIN, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
//  digitalWrite(MOT_B1_PIN, LOW);
//  digitalWrite(MOT_B2_PIN, LOW);

}

void loop() {

  valuePMW = map(read_RE(), 0, RE_MAX, 0, PWM_MAX) ; // map Rotary Encoder value to 255 steps (PWM)
  if (valuePMW != valuePMWlast) {
    Serial.print("PWM "); Serial.println(valuePMW);
    valuePMWlast = valuePMW;
    set_motor_pwm(valuePMW, MOT_A1_PIN, MOT_A2_PIN); //set PWM Motor output
    setNeopixels(valuePMW); //set value in neopixel ring
  }

  // for possible Rotary encoder button
  if (digitalRead(RE_BUTTON) == LOW) {  // Button pressed
   if (buttonREActive == false) {
     buttonREActive = true;
     buttonRETimer = millis();
   }
   if ((millis() - buttonRETimer > LONGPRESSTIME) && (longPressREActive == false)) {
     longPressREActive = true;
     Serial.println("buttonRE LongPressed"); 
//     valuePMW=0;
//     set_motor_pwm(valuePMW, MOT_A1_PIN, MOT_A2_PIN); //set PWM Motor output
     RE_counter=0;
     neoBrightness = BRIGHTNESS; //set default
     NeoPixel.setBrightness(neoBrightness);  
     NeoPixel.show(); // show all the set pixels on neopixel ring
   }
  } 
  else {                            // buttonRE released
    if (buttonREActive == true) {
      if (longPressREActive == true) {
        longPressREActive = false;
      } else {
        Serial.println("buttonRE ShortPressed");
        //on button press increase brightness in 10 steps
        neoBrightness = neoBrightness + BRIGHNESS_STEP;
        if (neoBrightness>255) {neoBrightness = BRIGHTNESS;}
        NeoPixel.setBrightness(neoBrightness);  
        NeoPixel.show(); // show all the set pixels on neopixel ring
        Serial.print("Brightness: "); Serial.println(neoBrightness);
         
      }
      buttonREActive = false;
    }
  }

}

//Read Rotary encoder
int read_RE() { 
  unsigned char result = rotary.process();
  if (result == DIR_CW) { //if turn Rotery encoder clockwise
    RE_counter++;
    if (RE_counter > RE_MAX) RE_counter=RE_MAX;
    Serial.print("Rotary Encoder: "); Serial.println(RE_counter);
  } else if (result == DIR_CCW) { //if turn Rotery encoder counter clockwise
    RE_counter--;
    if (RE_counter < -RE_MAX) RE_counter=-RE_MAX;
    Serial.print("Rotary Encoder: "); Serial.println(RE_counter);
  }
  return(RE_counter);
}

//PWM Motor output
void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // if reverse
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // else stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
//  Serial.print("Motor - PWM: "); Serial.println(pwm);
}

//Set neopixel ring to value - halfscale is stop
void setNeopixels(int pwm)
{
//  Serial.print("Neo - PWM: "); Serial.println(pwm);  
  NeoPixel.clear(); //Reset all pix
  if (pwm < 0) {  // if reverse
    for (int pixel = 0; pixel < HALFSCALE; pixel++) {  // for each pixel on the left halfscale
//      Serial.print("Neo - pixel reverse: "); Serial.print(HALFSCALE-pixel); Serial.print(" "); Serial.println(pixel * (PWM_MAX / (HALFSCALE-1)));  
      if (((pixel) * (PWM_MAX / (HALFSCALE-1))) < -valuePMW) { // fill pixels based on the rotary encoder value
        NeoPixel.setPixelColor(HALFSCALE-pixel, NeoPixel.Color(COLORRED));  // set these pixels to red color
      }
    }
  }
  if (pwm > 0) { // forward
    for (int pixel = HALFSCALE; pixel < NUM_PIXELS; pixel++) {  // for each pixel on the right halfscale
//      Serial.print("Neo - pixel reverse: "); Serial.print(pixel); Serial.print(" "); Serial.println((pixel - HALFSCALE) * (PWM_MAX / (HALFSCALE - 1)));  
      if (((pixel - HALFSCALE) * (PWM_MAX / (HALFSCALE - 1))) < valuePMW) { // fill pixels based on the rotary encoder value
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(COLORGREEN));  // set these pixels to green color
      }
    }
  }
//  if (pwm!=0) {NeoPixel.setPixelColor(0, NeoPixel.Color(COLORBLUE));}  // set pixel 0 to Blue color
  NeoPixel.setPixelColor(0, NeoPixel.Color(COLORBLUE));  // set pixel 0 to blue as power on indication
  NeoPixel.setBrightness(neoBrightness);  
  NeoPixel.show(); // show all the set pixels on neopixel ring

}

