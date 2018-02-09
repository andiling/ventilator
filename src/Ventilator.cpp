#include "Ventilator.h"

void setup()
{ 
    Serial.begin(115200);
    while (! Serial) {
        delay(1);
    }
    ScanAndConnect();
    webServer.begin();
    fan.begin();
}

void loop() {
    webServer.loop();
    fan.loop();
    delay(100);
}
