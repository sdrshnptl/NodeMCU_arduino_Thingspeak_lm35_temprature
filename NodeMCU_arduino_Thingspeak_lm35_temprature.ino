/*
 * 
 *
 * 
*/
#include <ESP8266WiFi.h>
 

String apiKey = "insert API key here";
const char* ssid = "AIRTEL_E5172_6534";
const char* password = "2316DDA1653";
 
const char* server = "api.thingspeak.com";
WiFiClient client;
   
 
void setup() {                
  Serial.begin(115200);
  delay(10);
  
  
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
}
 
 
void loop() {
   
  //float temp = analogRead(A0);
  float h = (3.3 * analogRead(A0) * 100.0) / 1024;
 
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(h);
           /*postStr +="&field2=";
           postStr += String(h);*/
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     Serial.print("Temperature: ");
     Serial.print(h);
     Serial.println(" degrees Celcius"); 
     
  }
  client.stop();
   
  Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  delay(20000);  
}

