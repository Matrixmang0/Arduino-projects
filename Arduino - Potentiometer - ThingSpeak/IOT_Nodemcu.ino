
#include <ESP8266WiFi.h>     
#define WIFI_SSID "SSN" 
#define WIFI_PASSWORD "Ssn1!Som2@Sase3#"  
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ThingSpeak.h>

WiFiClient client;

long myChannelNumber = 1698082 ;
const char myWriteAPIKey[] = "LDQFBGZ9DIK2RY7K" ;

SoftwareSerial nodemcu(D5, D6);


void setup() 
{
  
  Serial.begin(9600);
  nodemcu.begin(9600);
  WiFi.begin("SSN", "Ssn1!Som2@Sase3#");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
    }
  Serial.println();
  Serial.println("NodeMCU is connected !");
  Serial.println(WiFi.localIP()) ;

  ThingSpeak.begin(client);
  while (!Serial) continue;
}

void loop() {
  
  StaticJsonDocument<1000> doc;
 
  deserializeJson(doc, nodemcu) ;

  int A0 = doc["PM1"] ;
  int A1 = doc["PM2"] ;
  int A2 = doc["PM3"] ;  

  Serial.print("PM1 : "); Serial.println(A0);
  Serial.print("PM2 : "); Serial.println(A1);
  Serial.print("PM3 : "); Serial.println(A2);

  Serial.println("--------------------------------------------") ;

  ThingSpeak.writeField(myChannelNumber, 1, A0, myWriteAPIKey) ;
  ThingSpeak.writeField(myChannelNumber, 2, A1, myWriteAPIKey) ;
  ThingSpeak.writeField(myChannelNumber, 3, A2, myWriteAPIKey) ;
}
