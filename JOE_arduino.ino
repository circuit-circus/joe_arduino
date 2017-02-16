
const int leftButtonPin = 12;     // the number of the pushbutton pin
const int rightButtonPin = 11;     // the number of the pushbutton pin

const int ledPin = 13;

// variables will change:
int leftButtonState = 0;         // variable for reading the pushbutton status
int rightButtonState = 0;         // variable for reading the pushbutton status

int leftLastButtonState = 0;
int rightLastButtonState = 0;

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  if (Serial.available() > 0) { 
    // GET INFO
    char input = Serial.parseInt();
    if(input == 4) {
      digitalWrite(ledPin, HIGH);
    }
    delay(10);
  }

  // SEND INFO
  leftButtonState = digitalRead(leftButtonPin);
  rightButtonState = digitalRead(rightButtonPin);

  if (leftButtonState != leftLastButtonState) {
    if(leftButtonState == LOW) {
      Serial.println("L");
    }
    delay(10);
  }

  if (rightButtonState != rightLastButtonState) {
    if(rightButtonState == LOW) {
      Serial.println("R");
    }
    delay(10);
  }

  leftLastButtonState = leftButtonState;
  rightLastButtonState = rightButtonState;
}
