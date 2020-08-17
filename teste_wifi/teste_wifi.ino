#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
const char fingerprint[] PROGMEM =  "31 B5 D0 C3 74 CC 25 98 7F 67 32 9D DE FE 5149 E9 AD 8C D1";
char json[400] = {0};
StaticJsonDocument<256> doc;

void setup() {
    
  const char* ssid = "Repetidor-Multilaser";
  const char* password = "";

  Serial.begin(115200);
  int i = 0;
  while (i < 11) {
    delay(1000);
    i = i + 1;
  }
  Serial.println("hello world");
  Serial.println();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting...");
  }
  Serial.println("funcionou");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED){
        HTTPClient http;

        String data = "{\"idCard\":1001,\"username\":\"esp\"}";
        Serial.println(data);
        String url = "http://cinqbreak.herokuapp.com/api/User/Create";
        Serial.println(url);
        http.begin("http://cinqbreak.herokuapp.com/api/User/Create");
        //int httpCode = http.GET();
        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(data);

        Serial.println(url);

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println(payload);
        }
        else {
            Serial.println("httpCode >= 0");
        }

        http.end();
    }

    delay(10000);
}
