#include "Ventilator.h"

WebServer::WebServer(int port) {

    _server = new ESP8266WebServer(port);
    _server->on("/", std::bind(&WebServer::handle_root, this));
    _server->on("/set", std::bind(&WebServer::handle_setLoad, this));
    _server->on("/reset", std::bind(&WebServer::handle_reset, this));
    _server->on("/rpm", std::bind(&WebServer::handle_getRPM, this));

    _httpUpdater = new ESP8266HTTPUpdateServer(true);
    _httpUpdater->setup(_server);

    MDNS.begin(HOSTNAME);
    MDNS.addService("http", "tcp", 80);

}

void WebServer::begin() {
    _server->begin();
}

void WebServer::loop() {
    _server->handleClient();
}

void WebServer::handle_root() {
    _server->send(
        200,
        "text/plain",
        "AC ventilator.\nExposed endpoints are:\n *...");
}

void WebServer::handle_reset() {
    _server->send(200);
    delay(1000);
    ESP.reset();
}

void WebServer::handle_setLoad() {
    if (_server->arg("load") == "") {
        _server->send(400, "Missing 'load' query argument.");
        return;
    }

    String load = _server->arg("load");
    
    if (load.length() < 1 || load.length() > 3) {
        _server->send(400, "Invalid 'load' value. Supported values are from 0 to 100.");
    }

    for (int i = 0; i < load.length(); i++) {
        if (load.charAt(i) < '0' || load.charAt(i) > '9') {
            _server->send(400, "Invalid 'load' value. Supported values are from 0 to 100.");
        }
    }

    int loadInt = atoi(load.c_str());
    fan.setSpeed(loadInt);
    _server->send(200);
}

void WebServer::handle_getRPM() {
    int rpm = fan.getRPM();

    char response[16];
    response[0]=0;
    sprintf(response,"{\"rpm\": %d}", rpm);

    _server->send(200, "application/json", response);
}

WebServer webServer = WebServer(HTTP_PORT);
