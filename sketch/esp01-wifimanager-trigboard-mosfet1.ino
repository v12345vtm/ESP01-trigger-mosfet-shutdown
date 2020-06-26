//schema https://youtu.be/nbMfb0dIvYc?t=265


#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library wifimanager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

//needed for webclient
#include <ESP8266HTTPClient.h>
HTTPClient http;


const int output = 2;    // ESP8266-01 the number of the pushbutton pin flash is ook D2
const int input = 0;// ESP8266-01  D0




void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);




  pinMode(output, OUTPUT); //
    pinMode(input, INPUT); //
     digitalWrite (output , LOW);// geen reset doen 
  
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
 
}

void loop() {
  // put your main code here, to run repeatedly:

//digitalWrite (output , LOW);// geen reset doen 
 Serial.println("trigger gezien ");

 
     http.begin("http://192.168.1.2:80/postEvent.html?action=input&STM=0&MOD=3&CHA=0&EVT=2"); //HTTP
 Serial.println("[HTTP] REQ url");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    digitalWrite (output , HIGH);// reset doen , reset is atief laag
//delay(9999); //in principe moeten we nu niks meer doen nooit

while(true){
 // digitalWrite (output , LOW);// reset doen , reset is atief laag
delay(1000);
   Serial.println("output  high, dus vrijgave om mosfet te resetteb");
}
    
//  const int out1 = 2;    // ESP8266-01 the number of the pushbutton pin flash is ook D0
//const int out2 = 0;//sd3 op de nodemcu
//const int ledinbouw = 1;//5 is D1 op nodemcu
 Serial.println(digitalRead (input ));
 if (digitalRead (input )== 1){
  
 // digitalWrite (output , LOW);
  }
  else 

  { 
  //  digitalWrite (output , HIGH);
    }
}
