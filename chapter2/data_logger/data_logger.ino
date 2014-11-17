// Code to measure data and log it on an SD card

// Libraries
#include "DHT_Galileo.h"
#include <SD.h>

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
  
  // Init SD card
  Serial.print("Initializing SD card...");
  
  if (!SD.begin()) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  system("/sbin/fdisk -l > /dev/ttyGS0");  
  
  // Create file
  //createFile("data.txt");
  
  // Init DHT
  dht.begin();
  
  // Set date and time (only run once!)
  //system("date 171110202014"); //sets the date & time to 10:00 1st Jan 2014
}


void loop()
{
  // Measure from DHT
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();

  // Measure light level
  float sensor_reading = analogRead(A0);
  int light = sensor_reading/1024*100;
  
  // Prepare data to be logged
  String dataString = "";

  // Get time
  system("date '+%H:%M:%S' > /home/root/time.txt"); 
  FILE *fp;
  fp = fopen("/home/root/time.txt", "r");
  char buf[9];
  fgets(buf, 9, fp);
  fclose(fp);
  dataString += String(buf) + ",";
  
  // Add measurements
  dataString += String(temperature) + ",";
  dataString += String(humidity) + ",";
  dataString += String(light);
  
  // Log data
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // Check temperature range to avoid sensor errors
  if (temperature > -80 && temperature < 80){
    
    // If the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
    
      // Print to the serial port too:
      Serial.print("Logged data: ");
      Serial.println(dataString);
    }  
  
    // if the file isn't open, pop up an error:
    else {
      Serial.println("Error opening datalog.txt");
    } 
  }
  
  // Wait 10 seconds between measurements
  delay(10000);
 
}
