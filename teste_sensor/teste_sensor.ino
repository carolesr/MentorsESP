#include <SoftwareSerial.h>
#include <RDM6300.h>

SoftwareSerial RFID(2, 0);

int Led = 0;
uint8_t Payload[6];

RDM6300 RDM6300(Payload);

void setup() {
    pinMode(Led, OUTPUT);
    RFID.begin(9600);
    Serial.begin(9600);
    Serial.println("Leitor RFID RDM6300n");
}

void loop() {
    while (RFID.available() > 0)
    {
        digitalWrite(Led, HIGH);
        uint8_t c = RFID.read();
        if(RDM6300.decode(c))
        {
            Serial.print("ID TAG: ");
            for (int i = 0; i < 5; i++)
            {
                Serial.print(Payload[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
        }        
    }
    digitalWrite(Led, LOW);
    delay(100);
}
