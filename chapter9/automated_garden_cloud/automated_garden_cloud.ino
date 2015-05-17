// Libraries
#include <Sensirion.h>
#include <SPI.h>
#include <Ethernet.h>

// MAC address
byte mac[] = {  0x98, 0x4F, 0xEE, 0x01, 0x90, 0xC5 };

// Ethernet client
EthernetClient client;
IPAddress server(54,173,147,83);

String relay_state = "Off";

// Dweet parameters
#define thing_name  "intel_galileo_53e5fx"

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
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
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
    relay_state = "On";
    digitalWrite(relay_pin, HIGH);
  }
  
  // Deactivate pump if humidity gets high again
  if (humidity > high_threshold) {
    relay_state = "Off";
    digitalWrite(relay_pin, LOW);
  }
  
  Serial.println("Connecting...");
  
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    
    // Make a HTTP request:
    Serial.print("Sending request... ");
    
    client.print("GET /dweet/for/");
    client.print(thing_name);
    client.print("?temperature=");
    client.print(temperature);
    client.print("&humidity=");
    client.print(humidity);
    client.print("&light=");
    client.print(light_level);
    client.print("&relay=");
    client.print(relay_state);
    client.println(" HTTP/1.1");
    
    client.println("Host: dweet.io");
    client.println("Connection: close");
    client.println("");
    
    Serial.println("done.");
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.connected()) {
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }

  // if the server's disconnected, stop the client:
  client.stop();
  Serial.println("");
  Serial.println("Disconnecting.");
  
  Serial.println("");
  delay(5000);
 
}
