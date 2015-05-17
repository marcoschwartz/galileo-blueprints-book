// Motor pins
int speed_motor1 = 6;  
int speed_motor2 = 5;
int direction_motor1 = 7;
int direction_motor2 = 4;

// Sensor pins
int distance_sensor = A0;

// Variable to be exposed to the API
int distance;

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
}

void loop() {  
  
  forward();
  delay(2000);
  left();
  delay(2000);
  right();
  delay(2000);
  stop();
  delay(2000);
  
  // Measure distance
  distance = measure_distance(distance_sensor);
  Serial.print("Measured distance: ");
  Serial.println(distance);
  
}

// Forward
int forward() {
  
  send_motor_command(speed_motor1,direction_motor1,100,1);
  send_motor_command(speed_motor2,direction_motor2,100,1);
  return 1;
}

// Backward
int backward() {
  
  send_motor_command(speed_motor1,direction_motor1,100,0);
  send_motor_command(speed_motor2,direction_motor2,100,0);
  return 1;
}

// Left
int left() {
  
  send_motor_command(speed_motor1,direction_motor1,75,0);
  send_motor_command(speed_motor2,direction_motor2,75,1);
  return 1;
}

// Right
int right() {
  
  send_motor_command(speed_motor1,direction_motor1,75,1);
  send_motor_command(speed_motor2,direction_motor2,75,0);
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
