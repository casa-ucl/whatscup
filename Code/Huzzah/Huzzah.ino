//LCD imports
#include <SPI.h>
#include "LCD_Driver.h"
#include "LCD_GUI_Paint.h"
#include "LCD_Images.h"

//Connectivity imports
#include <ESP8266WiFi.h>
#include "arduino_secrets.h" // Wifi and MQTT secrets 

//TimeZone import
#include <ezTime.h>

//Constants
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;   
const char* mqtt_server = "mqtt.cetools.org";

//Internal fields
WiFiClient espClient;

char msg[50];
int currentMood = -1;
Timezone GB;

void setup() {
  initialiseLCDScreen();
  
  Serial.println("Hi");
  drawMoodOnScreen(1);

  //Connect to an SSID and print local IP address, taken from CASA plant monitoring class
  Serial.print("Connecting to ");
  Serial.println(SECRET_SSID);
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //Initialise time settings
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());  

  pinMode(BUILTIN_LED, OUTPUT);     
  digitalWrite(BUILTIN_LED, HIGH);  
}


void loop() {

}


//Preparing & clearing LCD screen
void initialiseLCDScreen(){
  Config_Init();
  LCD_Init();
  
  LCD_SetBacklight(100);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, BLACK);
  Paint_Clear(BLACK);
}

//LCD screen output
void drawMoodOnScreen(int mood){

  if(mood == 0 && currentMood != 0)
  {
    currentMood = 0;
    Serial.println("Drawing sad face");
    Paint_Clear(BLACK);
    Paint_DrawImage(gImage_sad, 5, 5, 165, 160); 
  }

  if(mood == 1 && currentMood != 1)
  {
    currentMood = 1;
    Serial.println("Drawing happy face");
    Paint_Clear(BLACK);
    Paint_DrawImage(gImage_happy, 5, 4, 165, 164); 
  } 
}
