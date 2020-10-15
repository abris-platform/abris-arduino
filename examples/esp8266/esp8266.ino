#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <AbrisPlatform.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

#define NUM_ESP "1"
#define NUM_SENSOR_TEMP "1"

HTTPClient http;
int flag_connect_wifi=0;

const char * loginWiFi = "loginWIFI";
const char * passWiFi = "passwordWIFI";

const char * loginDB = "postgres";
const char * passDB = "1234567";
const char * addreServer = "server address";

AbrisPlatform abris(&http, addreServer);

OneWire oneWire(D1);
DallasTemperature DALLAS(&oneWire);

StaticJsonDocument<400> jsonDocument;

String updateSensorKey[2] = {"id","id_esp"};
String jsonKeyValue;
String jsonFieldsValue; 

void setup() {
  
  WiFi.persistent(false);
  flag_connect_wifi = wifi_client(loginWiFi, passWiFi);
  abris.authenticate(loginDB, passDB);

  DALLAS.begin();
  pinMode(2, OUTPUT); 

}

void loop() {
 if(flag_connect_wifi){
  
  jsonDocument.clear();
  jsonFieldsValue = "";
  jsonDocument["value"] = String(sensorTemp());
  serializeJson(jsonDocument, jsonFieldsValue);
  
  jsonDocument.clear(); 
  jsonKeyValue = "";
  jsonDocument[updateSensorKey[0]][0]= NUM_SENSOR_TEMP; 
  jsonDocument[updateSensorKey[1]][0]= NUM_ESP; 
  serializeJson(jsonDocument, jsonKeyValue);
  
  abris.update("public","sensor", jsonFieldsValue.c_str(), updateSensorKey, jsonKeyValue.c_str());

  digitalWrite(2, HIGH);
  delay(1000);  
  digitalWrite(2, LOW);
  delay(1000);     
 }
 else{
  flag_connect_wifi = wifi_client(loginWiFi, passWiFi);
  digitalWrite(2, HIGH);
  delay(5000);  
  digitalWrite(2, LOW);
  delay(5000); 
 }

 
}

int sensorTemp(){
  DALLAS.requestTemperatures(); 
  return DALLAS.getTempCByIndex(0);
}


int wifi_client(String wifiname, String wifipass){
  byte i=0;
  WiFi.disconnect(true);
  delay(1000);
  WiFi.begin(wifiname, wifipass);
  while((WiFi.status()!= WL_CONNECTED)&&(i<20))
  {  
    delay(500);
    i++;
  }
  flag_connect_wifi = (WiFi.status()==WL_CONNECTED);
  return flag_connect_wifi;
}
