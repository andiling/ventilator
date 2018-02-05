#include "Ventilator.h"

void setup()
{ 
    Serial.begin(115200);
    ScanAndConnect();
    webServer.begin();
    fan.begin();
}

void loop() {
    webServer.loop();
    fan.loop();
    delay(100);
}
