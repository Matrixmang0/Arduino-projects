

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial nodemcu(18, 19) ;

void setup() {

  Serial.begin(9600);

  nodemcu.begin(9600);


}

void loop() {

  StaticJsonDocument<1000> doc;

  int raw0 = analogRead(A0) ;
  int raw1 = analogRead(A1) ;
  int raw2 = analogRead(A2) ;

  int A0 = map(raw0, 0, 1023, 0, 5000)  ;
  int A1 = map(raw1, 0, 1023, 0, 10000) ;
  int A2 = map(raw2, 0, 1023, 0, 50000) ;

  delay(1000) ;

  Serial.print("PM1 : "); Serial.println(A0);
  Serial.print("PM2 : "); Serial.println(A1);
  Serial.print("PM3 : "); Serial.println(A2);

  Serial.println("--------------------------------------------") ;

  doc["PM1"] = A0 ;
  doc["PM2"] = A1 ;
  doc["PM3"] = A2 ;

  serializeJson(doc, nodemcu) ;

  delay(1000) ;


}
