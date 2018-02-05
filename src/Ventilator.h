#ifndef _VENTILATOR_H_
#define _VENTILATOR_H_

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "WiFi.h"
#include "Fan.h"
#include "WebServer.h"

#define HTTP_PORT 80
#define HOSTNAME "br-sp-ventilator"

#define FAN_PIN D2

#endif
