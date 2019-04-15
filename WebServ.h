
/*
   WebServ.h

*/

#ifndef _WebServ_H_
#define _WebServ_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "Config.h"
#include "Files.h"


class GW_WebServ : public ESP8266WebServer {

  private:
    uint16_t mPort;

  public:
    GW_WebServ (uint16_t);
    void start();
};



#endif
