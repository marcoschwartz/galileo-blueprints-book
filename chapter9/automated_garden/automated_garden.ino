// Libraries
#include <Sensirion.h>

// Pins
int temperature_pin = A1;
int light_pin = A0;

int dataPin = 6;
int clockPin = 7;

int relay_pin = 8;

// Soil sensor instance
Sensirion soil_sensor = Sensirion(dataPin, clockPin);

// Humidity thresholds
float low_threshold = 40;
float high_threshold = 60;

void setup() {

  // Serial
  Serial.begin(115200);  
  
  // Pin mode
  pinMode(relay_pin, 8);
}

// the loop routine runs over and over again forever:
void loop() {
  
  // Measure & print data
  float light_reading = analogRead(light_pin);
  float light_level = light_reading/1024*100;
  Serial.print("Light level: ");
  Serial.println(light_level);
  
  float temperature_reading = analogRead(temperature_pin);
  float temperature = (temperature_reading/1024*5000 - 500)/10; 
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  uint16_t rawData;
  
  soil_sensor.measTemp(&rawData);
  float tempC = soil_sensor.calcTemp(rawData);
  soil_sensor.measHumi(&rawData);
  float humidity = soil_sensor.calcHumi(rawData, tempC);
  
  Serial.print("Soil humidity: ");
  Serial.println(humidity);
  
  // Activate pump if humidity gets low
  if (humidity < low_threshold) {
    digitalWrite(relay_pin, HIGH);
  }
  
  // Deactivate pump if humidity gets high again
  if (humidity > high_threshold) {
    digitalWrite(relay_pin, LOW);
  }
  
  Serial.println("");
  delay(1000);
 
}
