#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <SoftwareSerial.h>
#include <RDM6300.h>

SoftwareSerial RFID(2, 0);

int Led = 0;
uint8_t Payload[6];

RDM6300 RDM6300(Payload);
  
void setup() {
  
  pinMode(Led, OUTPUT);
  RFID.begin(9600);
  
  const char* ssid = "ROSA_2G_Rep";
  const char* password = "";
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
  }

}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    while (RFID.available() > 0)
    {
        digitalWrite(Led, HIGH);
        uint8_t c = RFID.read();
        if(RDM6300.decode(c))
        {
            String code = "";
            for (int i = 0; i < 5; i++)
            {
                code = code + String(Payload[i]);
            }
            
            http.begin("http://cinqbreak.herokuapp.com/api/User/VerifyUser");
            http.addHeader("Content-Type", "application/json");
            String data = code;
            int httpCode = http.POST(data);

            http.end();
        }        
    }
    digitalWrite(Led, LOW);
    delay(100);
  }

}
