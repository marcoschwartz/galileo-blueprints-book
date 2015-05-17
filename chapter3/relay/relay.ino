// Code to control the relay via a push button

// Pins
int relayPin = 7;
int buttonPin = 8;

// Button state
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int previousButtonState = LOW;

// Debounce variables
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

// State of the relay
int relayState = LOW;

void setup() {
  
  // Start Serial
  Serial.begin(115200);

  // Pins mode
  pinMode(relayPin, OUTPUT); 
  pinMode(buttonPin, INPUT);  
  
}

void loop() {
  
  // Read data from button
  int reading = digitalRead(buttonPin);
  
   // If the switch changed, due to noise or pressing
  if (reading != lastButtonState) {
    
    // Reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  // Debounce code
  if ((millis() - lastDebounceTime) > debounceDelay) {
  
    // If the button state has changed
    if (reading != buttonState) {
      buttonState = reading;
    }
    
    // If the button was pressed, changed the output
    if (previousButtonState == LOW &&  buttonState == HIGH) {
      relayState = !relayState;
    }
  }
  
  // Set the relay
  digitalWrite(relayPin, relayState);
  
  // Store previous states
  previousButtonState = buttonState;
  lastButtonState = reading;
  
}
