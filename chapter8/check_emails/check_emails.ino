// Libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <Ethernet.h>

// LCD Screen
LiquidCrystal_I2C lcd(0x27,20,4);

// Ethernet MAC
byte mac[] = {0x98, 0x4F, 0xEE, 0x01, 0x90, 0xC5};

// Email-Checking variables
const int emailUpdateRate = 10000; // Update rate in ms (10 s)
long emailLastMillis = 0; // Stores our last email check time
int emailCount = 0; // Stores the last email count

void setup() 
{

  // Serial monitor is used for debug
  Serial.begin(115200); 

  // Init SD card
  initSDCard();

  // Init LCD
  initDisplay(); 
  
  // Connect Ethernet
  initEthernet()
}

void loop() 
{
  // Only check email if emailUpdateRate ms have passed
  if (millis() > emailLastMillis + emailUpdateRate)
  {
    emailLastMillis = millis(); // update emailLastMillis
    
    // Get unread email count, and print it on the LCD
    int tempCount = getEmailCount(); 
    lcd.print("You have ");
    lcd.print(tempCount);
    lcd.println(" unread mail.");

    if (tempCount != emailCount) // If it's a new value, update
    { // Do this to prevent blinking the same #
      emailCount = tempCount; // update emailCount variable
      printEmailCount(emailCount); // print the unread count
    }
  }
  
  // Bit of protection in case millis overruns:
  if (millis() < emailLastMillis)
    emailLastMillis = 0;
}

// Get email count by executing the Python script
int getEmailCount()
{
  int digits = 0;
  int temp[10];
  int emailCnt = 0;

  // Send a system call to run our python script and route the
  // output of the script to a file.
  system("python /home/root/emails.py > /media/card/emails.txt");
  
  File emailsFile = SD.open("emails"); // open emails for reading

  // read from emails until we hit the end or a newline
  while ((emailsFile.peek() != '\n') && (emailsFile.available()))
    temp[digits++] = emailsFile.read() - 48; // Convert from ASCII to a number

  emailsFile.close(); // close the emails file
  system("rm /media/realroot/emails"); // remove the emails file

  // Turn the inidividual digits into a single integer:
  for (int i=0; i<digits; i++)
    emailCnt += temp[i] * pow(10, digits - 1 - i);
  
  return emailCnt;
}

// Init LCD display
void initDisplay()
{
  lcd.init();      
  lcd.backlight();
  lcd.clear();
}

// Init SD card
void initSDCard()
{
  SD.begin();
}

// Init Ethernet connection
uint8_t initEthernet()
{
  if (Ethernet.begin(mac) == 0)
    return 0;
  else
    return 1;
}
