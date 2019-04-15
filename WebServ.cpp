/*
   WebSockets.cpp

*/


#include "WebServ.h"

/****************************** Constructeur ******************************/

GW_WebServ::GW_WebServ(uint16_t port) {
  mPort = port;
}

/******************************** begin ********************************/

void GW_WebServ::start() { // Start WebSocket server
  
  ESP8266WebServer GW_WebServ(mPort);

  GW_WebServ::on("/" , [&]() {
    GW_WebServ::send(200, "text/plain", "this works as well");
  });

  GW_WebServ::onNotFound([&]() {
    !Files::handleFileRead(this);
  });

  GW_WebServ::begin();                             // start the HTTP server

  DBG_OUTPUT.printf("WebServer started on port %d.\n", mPort);
}
