const int numLeds = 8;
int a[numLeds] = {2, 3, 4, 5, 6, 7, 8, 9};
const int buttonPin = 10;

int ledLevel = 0;
bool lastButtonState = HIGH;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(a[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  randomSeed(analogRead(0));  // Optional: seed for randomness
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    ledLevel++;
    if (ledLevel >= 6) {
      ledLevel = 0;
    }
    delay(220);  // Debounce
  }

  lastButtonState = buttonState;

  switch (ledLevel) {          // if ledLevel=1 than case=1 and so on        
    case 0:
      forwardChaser();
      break;
    case 1:
      reverseChaser();
      break;
    case 2:
      centerOut();
      break;
    case 3:
      outsideIn();
      break;
    case 4:
      sparkleRandom();
      break;
    case 5:
      blinkAll();
      break;
  }
}

// Pattern 1: Forward chase
void forwardChaser() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(a[i], HIGH);
    delay(100);
    digitalWrite(a[i], LOW);
  }
}

// Pattern 2: Reverse chase
void reverseChaser() {
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(a[i], HIGH);
    delay(100);
    digitalWrite(a[i], LOW);
  }
}

// Pattern 3: Center-out
void centerOut() {
  int center1 = numLeds / 2 - 1;
  int center2 = numLeds / 2;
  for (int offset = 0; offset <= center1; offset++) {
    digitalWrite(a[center1 - offset], HIGH);
    digitalWrite(a[center2 + offset], HIGH);
    delay(100);
    digitalWrite(a[center1 - offset], LOW);
    digitalWrite(a[center2 + offset], LOW);
  }
}

// Pattern 4: Outside-in
void outsideIn() {
  for (int offset = 0; offset <= numLeds / 2 - 1; offset++) {
    digitalWrite(a[offset], HIGH);
    digitalWrite(a[numLeds - 1 - offset], HIGH);
    delay(100);
    digitalWrite(a[offset], LOW);
    digitalWrite(a[numLeds - 1 - offset], LOW);
  }
}

// Pattern 5: Random sparkle
void sparkleRandom() {               // randomseed(analogreed(0)) is helpful here
  for (int i = 0; i < 15; i++) {
    int r = random(0, numLeds);
    digitalWrite(a[r], HIGH);
    delay(80);
    digitalWrite(a[r], LOW);
  }
}

// Pattern 6: All blink
void blinkAll() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < numLeds; i++) digitalWrite(a[i], HIGH);
    delay(200);
    for (int i = 0; i < numLeds; i++) digitalWrite(a[i], LOW);
    delay(200);
  }
}
