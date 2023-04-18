#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define LED_PIN 13 // specify the pin the LED strip is connected to
#define LED_COUNT 10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//Set up inputs for the IR Sensor:
const int sensorPin = 5;
// Status of the sensor
bool beamBroken = false;
int breakCount = 0;

//For buzzer:
const int buzzerPin = 4;

//For "lose" reset button:
const int buttonPin = 3;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  resetGame();

}

void loop() {

//First, lets create a reset for when RED loses
  buttonState = digitalRead(buttonPin);
  if(buttonState != HIGH){
// Check if the beam is broken
    if(digitalRead(sensorPin) == LOW){
// Check if the beam was previously unbroken
      if(!beamBroken){
// Indicate that the beam is now broken
        beamBroken = true;
// Increment the break count
        counterBreak();
    }
  }
  
// Check if the beam is not broken
    else{
// Check if the beam was previously broken
      if(beamBroken){ 
// Indicate that the beam is now not broken
        beamBroken = false; 
      }
    }
    delay(100);

//When Player Reaches 10 points, finishing the game
    if(breakCount == 10) {
      lcd.init();
      lcd.backlight();
      lcd.setCursor(4,0);
      lcd.print("You Win!");
      lcd.setCursor(1,1);
      lcd.print("Congrats Red!!");
//Play Success Audio
      successAudio();
//Resetting Game
      resetGame();
    }
}
    else{
      lcd.init();
      lcd.backlight();
      lcd.setCursor(3,0);
      lcd.print("Better Luck");
      lcd.setCursor(3,1);
      lcd.print("Next Time!");

      resetGame();
    }
  }

//Down below are methods I created to make my code less messy

void successAudio() {
      strip.fill(0xCC0000,0,10);
      digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
      strip.show();
      strip.clear();
      delay(75); // Wait for 0.5 second
      digitalWrite(buzzerPin, LOW); // Turn the buzzer off
      strip.show();
      strip.fill(0xCC0000,0,10);
      delay(75);
      digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
      strip.show();
      strip.clear();
      delay(75);
      digitalWrite(buzzerPin, LOW); // Turn the buzzer off
      strip.show();
      strip.fill(0xCC0000,0,10);
      delay(75);
      digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
      strip.show();
      strip.clear();
      delay(75);
      digitalWrite(buzzerPin, LOW); // Turn the buzzer off
      strip.show();
      strip.fill(0xCC0000,0,10);
      delay(100);
}

void resetGame(){
//Resetting Game
      breakCount = 0;
      lcd.init(); // initialize the lcd
// Print original message to the LCD.
      lcd.backlight();
      lcd.setCursor(4,0);
      lcd.print("Red Team");
      lcd.setCursor(4,1);
      lcd.print("Score: ");
      lcd.setCursor(11,1);
      lcd.print(breakCount);
}

void goalAudio(){
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
}

void counterBreak() {
      breakCount++;
      lcd.backlight();
      lcd.setCursor(11,1);
      lcd.print(breakCount);
      redColor();
}

void redColor(){
  goalAudio();
  for (int i = 0; i <= 10; i++) {
    strip.fill(0xCC0000,0,10);
    strip.show();
    strip.clear();
    delay(50);
    strip.show();
  }
}
