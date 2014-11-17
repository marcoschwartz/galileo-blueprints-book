// Code to measure data and print it on the Serial monitor

// Libraries
#include "DHT_Galileo.h"

// DHT sensor type
#define DHTTYPE DHT11 // DHT 11 

// DHT sensor pins
#define DHTIN 5
#define DHTOUT 6

// DHT instance
DHT_Galileo dht(DHTIN,DHTOUT, DHTTYPE);

void setup()
{
  // Initialize the Serial port
  Serial.begin(115200);
  
  // Init DHT
  dht.begin();
}


void loop()
{
  // Measure from DHT
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Measure light level
  float sensor_reading = analogRead(A0);
  float light = sensor_reading/1024*100;
  
  // Display temperature
  Serial.print("Temperature: ");
  Serial.print((int)temperature);
  Serial.println(" C");
  
   // Display humidity
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  // Display light level
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println("%");
  Serial.println("");
  
  // Wait 500 ms
  delay(500);
  
}
