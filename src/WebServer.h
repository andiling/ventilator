#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "Ventilator.h"

class WebServer {
    public:
        WebServer(int port);
        void begin();
        void loop();
    private:
      ESP8266WebServer *_server;
      ESP8266HTTPUpdateServer *_httpUpdater;
      
      void handle_root();
      void handle_reset();
      void handle_setLoad();
      void handle_getRPM();
};

extern WebServer webServer;

#endif
