#include <Servo.h>

// Buttons
const int leftButtonPin = 12;
const int rightButtonPin = 13;

int leftButtonState = 0;
int rightButtonState = 0;

int leftLastButtonState = 0;
int rightLastButtonState = 0;

unsigned long leftLastDebounceTime = 0;
unsigned long rightLastDebounceTime = 0;
unsigned long debounceDelay = 50;


// Servos
Servo servos[9];
int noOfServos = 9;

void setup() {
  Serial.begin(9600);
  
  // initialize the pushbutton pin as an input:
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  
  // Attach servos to pin 2-11
  for(int i = 0; i < noOfServos; i++) {
    servos[i].write(0);
    servos[i].attach(i+2);
  }
  
}

void loop() {

  // Get info from Joe
  if (Serial.available() > 0) {
    String readInput = Serial.readStringUntil('\n');
    int input = readInput.toInt();
    
    // Test that input is within servo range
    if(input < 0 || input > 5) return;
    
    servos[input].write(180);
    delay(1000);
    servos[input].write(0);
    delay(1000);
    
    // Drink 2, 4, 5 need milk
    switch (input) {
      case 2:
        servos[6].write(180);
        delay(1000);
        servos[6].write(0);
        break;
      case 4:
        servos[7].write(180);
        delay(1000);
        servos[7].write(0);
        break;
      case 5:
        servos[8].write(180);
        delay(1000);
        servos[8].write(0);
        break;
    }    
  }

  // SEND INFO
  int leftButtonReading = digitalRead(leftButtonPin);
  int rightButtonReading= digitalRead(rightButtonPin);

  // If the switch changed, due to noise or pressing, reset the debouncing timer
  if (leftButtonReading != leftLastButtonState) {
    leftLastDebounceTime = millis();
  }

  if (rightButtonReading != rightLastButtonState) {
    rightLastDebounceTime = millis();
  }


  // Whatever the reading is at, it's been there for longer than the debounce delay, so take it as the actual current state
  if ((millis() - leftLastDebounceTime) > debounceDelay) {
    // If the button state has changed:
    if (leftButtonReading != leftButtonState) {
      leftButtonState = leftButtonReading;

      // only toggle the LED if the new button state is LOW
      if(leftButtonState == LOW) {
        Serial.println("L");
      }
    }
  }

  if ((millis() - rightLastDebounceTime) > debounceDelay) {
    if (rightButtonReading != rightButtonState) {
      rightButtonState = rightButtonReading;

      if(rightButtonState == LOW) {
        Serial.println("R");
      }
    }
  }

  // Save the reading.
  leftLastButtonState = leftButtonReading;
  rightLastButtonState = rightButtonReading;


}
