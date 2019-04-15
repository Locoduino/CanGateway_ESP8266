/*
   WiFi.h

*/

#ifndef __gatewayWifi_H__
#define __gatewayWifi_H__

#include <Arduino.h>
#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
#ifdef ESP32
#include <ESPmDNS.h>
#endif
#include "config.h"

struct Wifi {

  static void begin();

};

#endif
