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

const char * networkName = "WiFi";
const char * networkPassword = "123456";

const char * loginDB = "postgres";
const char * passwordDB = "123456";
const char * serverAddress = "192.168.0.1";

AbrisPlatform abris(&http, serverAddress);

OneWire oneWire(D1);
DallasTemperature DALLAS(&oneWire);

StaticJsonDocument<400> jsonDocument;

String jsonKeyValue;
String jsonFieldsValue; 

void setup() {
  WiFi.persistent(false);
  flag_connect_wifi = wifi_client(networkName, networkPassword);
  abris.authenticate(loginDB, passwordDB);

  DALLAS.begin();
  pinMode(2, OUTPUT); 
  
  if(flag_connect_wifi){
     jsonDocument["ip"] = WiFi.localIP().toString();
     serializeJson(jsonDocument, jsonFieldsValue);   
     abris.update("public", "esp", jsonFieldsValue.c_str(), "{\"id\":\"1\"}"); ///< IP address update
  }

  jsonDocument.clear(); 
  jsonKeyValue = "";
  jsonDocument["id"][0] = NUM_SENSOR_TEMP; 
  jsonDocument["id_esp"][0] = NUM_ESP; 
  serializeJson(jsonDocument, jsonKeyValue);  ///< "jsonKeyValue" initialization
}

void loop() {
  if(flag_connect_wifi){
    jsonFieldsValue = "";
    jsonDocument["value"] = String(sensorTemp());
    serializeJson(jsonDocument, jsonFieldsValue);
    abris.update("public","sensor", jsonFieldsValue.c_str(), jsonKeyValue.c_str());

    LEDFlashing(1000); 
  }
  else{
    flag_connect_wifi = wifi_client(networkName, networkPassword);
    LEDFlashing(5000);
  }
}

void LEDFlashing(int flashTime){
  digitalWrite(2, HIGH);
  delay(flashTime);  
  digitalWrite(2, LOW);
  delay(flashTime); 
}

int sensorTemp(){
  DALLAS.requestTemperatures(); 
  return DALLAS.getTempCByIndex(0);
}

int wifi_client(String wifiname, String wifipass){
  byte i = 0;
  WiFi.disconnect(true);
  delay(1000);
  WiFi.begin(wifiname, wifipass);
  while((WiFi.status() != WL_CONNECTED) && (i < 20))
  {  
    delay(500);
    i++;
  }
  flag_connect_wifi = (WiFi.status() == WL_CONNECTED);
  return flag_connect_wifi;
}