#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() {
    
  const char* ssid = "ROSA_2G_Rep";
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

        //String data = "{\"idCard\":100,\"username\":\"esp_teste\"}";
        String data = "555";
        Serial.println(data);
        String url = "http://cinqbreak.herokuapp.com/api/User/VerifyUser";
        Serial.println(url);
        http.begin("http://cinqbreak.herokuapp.com/api/User/VerifyUser");
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
