#include <SimpleDHT.h>
int pinDHT11 = 14;
SimpleDHT11 dht11;

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "faheemtech-d7831.firebaseio.com"
#define WIFI_SSID "Connect Wifi" // Change the name of your WIFI
#define WIFI_PASSWORD "fah12345" // Change the password of your WIFI

void setup() {
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  float t =  (float)temperature;
  float h =  (float)humidity;
  
  Serial.print(t); Serial.print(" *C, "); 
  Serial.print(h); Serial.println(" H");
  
  // DHT11 sampling rate is 1HZ.
    
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  delay(500);
}
