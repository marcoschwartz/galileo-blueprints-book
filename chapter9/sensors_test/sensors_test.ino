// Libraries
#include <Sensirion.h>

// Pins
int temperature_pin = A1;
int light_pin = A0;

int dataPin = 6;
int clockPin = 7;

// Soil sensor instance
Sensirion soil_sensor = Sensirion(dataPin, clockPin);

void setup() {

  // Serial
  Serial.begin(115200);  
}

// the loop routine runs over and over again forever:
void loop() {
  
  // Test photocell
  float light_reading = analogRead(light_pin);
  float light_level = light_reading/1024*100;
  Serial.print("Light level: ");
  Serial.println(light_level);
  
  // Test temperature sensor
  float temperature_reading = analogRead(temperature_pin);
  float temperature = (temperature_reading/1024*5000 - 500)/10; 
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  // Test soil sensor
  uint16_t rawData;
  
  soil_sensor.measTemp(&rawData);
  float tempC = soil_sensor.calcTemp(rawData);
  soil_sensor.measHumi(&rawData);
  float humidity = soil_sensor.calcHumi(rawData, tempC);
  
  Serial.print("Soil humidity: ");
  Serial.println(humidity);
  
  Serial.println("");
  delay(1000);
 
}
