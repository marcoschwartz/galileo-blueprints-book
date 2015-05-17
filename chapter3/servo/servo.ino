// Code to control the servomotor via a potentiometer
#include <Servo.h> 

// Pins
int potPin = A0;

// Servo object
Servo myservo;


void setup() {
  
  // Start Serial
  Serial.begin(115200);

  // Pins mode
  pinMode(potPin, INPUT);  
  
  // Attach servo
  myservo.attach(9);
  
}

void loop() {
  
  // Read data from potentiometer
  float reading = analogRead(potPin);
  float servo_position = reading/1023. * 180.;
  
  // Change servo position
  myservo.write(servo_position);  
}
