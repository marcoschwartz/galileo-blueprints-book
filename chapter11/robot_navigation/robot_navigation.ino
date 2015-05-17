// Motor pins
int speed_motor1 = 6;  
int speed_motor2 = 5;
int direction_motor1 = 7;
int direction_motor2 = 4;

// Sensor pin
int distance_sensor = A0;

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  
  // Go forward by default
  forward();
}

void loop() {  
  
  // Measure distance
  int distance = measure_distance(distance_sensor);
  
  // If obstacle in front
  if (distance < 10) {
  
    // Go backward
    backward();
    delay(2000);
    
    // Turn around
    left();
    delay(500);
    
    // Go forward again
    forward();
  }
  
}

// Forward
int forward() {
  
  send_motor_command(speed_motor1,direction_motor1,200,1);
  send_motor_command(speed_motor2,direction_motor2,200,1);
  return 1;
}

// Backward
int backward() {
  
  send_motor_command(speed_motor1,direction_motor1,200,0);
  send_motor_command(speed_motor2,direction_motor2,200,0);
  return 1
}

// Left
int left() {
  
  send_motor_command(speed_motor1,direction_motor1,150,0);
  send_motor_command(speed_motor2,direction_motor2,150,1);
  return 1;
}

// Right
int right() {
  
  send_motor_command(speed_motor1,direction_motor1,150,1);
  send_motor_command(speed_motor2,direction_motor2,150,0);
  return 1;
}

// Stop
int stop() {
  
  send_motor_command(speed_motor1,direction_motor1,0,1);
  send_motor_command(speed_motor2,direction_motor2,0,1);
  return 1;
}

// Function to command a given motor of the robot
void send_motor_command(int speed_pin, int direction_pin, int pwm, boolean dir)
{
  analogWrite(speed_pin,pwm); // Set PWM control, 0 for stop, and 255 for maximum speed
  digitalWrite(direction_pin,dir);
}

// Measure distance from the ultrasonic sensor
int measure_distance(int pin){
  
  unsigned int Distance=0;
  unsigned long DistanceMeasured=pulseIn(pin,LOW);
  
  if(DistanceMeasured==50000){              // the reading is invalid.
      Serial.print("Invalid");    
   }
    else{
      Distance=DistanceMeasured/50;      // every 50us low level stands for 1cm
   }
   
  return Distance;
}
