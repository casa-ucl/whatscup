#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

ESP8266WebServer server(80);
const char* mqtt_server = "mqtt.cetools.org";
WiFiClient espClient;//handle wifi messages
PubSubClient client(espClient);//handle MQTT messages, pass wificlient to connect
StaticJsonDocument<200> doc;// Allocate the JSON document

void setup() {
  Serial.begin(115200);
  delay(100);

  startWifi(); 
  startWebserver(); 

  // start MQTT server
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);

}  

void loop() {
  // handler for receiving requests to webserver
  server.handleClient(); //?
  if (!client.connected()) {//check if connected to MQTT
    reconnect();
  }

  client.loop();

  /*char json[] = "{\"home_score\": 1,\"away_score\": 0,\"home_team_en\": \"England\",\"away_team_en\": \"France\",\"finished\": \"false\",\"datetime\": \"2022-11-21 13:01\"}";
  
  ///////////////payload; //"{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}


  DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  int home_score = doc["home_score"];
  int away_score = doc["away_score"];  
  const char* home_team_en = doc["home_team_en"];
  const char* away_team_en = doc["away_team_en"];  
  const char* finished = doc["finished"];
  const char* datatime = doc["datetime"];

  // Print values.
  Serial.println(home_score);
  Serial.println(away_score);
  Serial.println(home_team_en);
  Serial.println(away_team_en);
  Serial.println(finished);
  Serial.println(datatime);*/
  
}

void startWifi() {
  // connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // when not connected keep trying until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  
  //Exit the while loop means have a connection
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //IP address of Huzzah
}

void startWebserver() {
  // when connected and IP address obtained start HTTP server
  server.begin();
  Serial.println("HTTP server started");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  StaticJsonDocument<1024> doc;// Allocate the JSON document
  String myString = String((char*)payload);
  //String myString = String((char*)payload);
  //const char* a = myString.c_str();
  //char json[length] = myString;
  //json = myString;  
  //  = myString; //"{\"home_score\": 1,\"away_score\": 0,\"home_team_en\": \"England\",\"away_team_en\": \"France\",\"finished\": \"false\",\"datetime\": \"2022-11-21 13:01\"}";
  
  ///////////////payload; //"{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}


  deserializeJson(doc, myString); // Deserialize the JSON document

  // Test if parsing succeeds.
  //if (error) {
    //Serial.print(F("deserializeJson() failed: "));
    //Serial.println(error.f_str());
  ///  return;
 // }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  String home_team_en = doc["home_team_en"];
  //int away_score = doc["away_score"];  
  //const char* home_team_en = doc["home_team_en"];
  //const char* away_team_en = doc["away_team_en"];  
  //const char* finished = doc["finished"];
  //const char* datatime = doc["datetime"];

  // Print values.
  //Serial.println(home_score);
  //Serial.println(away_score);
  Serial.println(home_team_en);
  //Serial.println(away_team_en);
  //Serial.println(finished);
  //Serial.println(datatime);
  

 /* // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }*/

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect with clientID, username and password
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      client.subscribe("student/ucfnnbx/whatscup/match");//subscribe to the topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}