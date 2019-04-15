/*
   WebSockets.cpp

*/


#include "WebSockets.h"

/****************************** Constructeur ******************************/

GW_WebSockets::GW_WebSockets(uint16_t port) {
  mPort = port;
  mInputMsg = NULL;
  ptWss = NULL;
}

/******************************** begin ********************************/

void GW_WebSockets::begin() { // Start WebSocket server
  ptWss = new WebSocketsServer(mPort);
  ptWss->begin();
  ptWss->onEvent([&](uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
      case WStype_DISCONNECTED:
        DBG_OUTPUT.printf("Wifi [%u] Disconnected!\n", num);
        break;
      case WStype_CONNECTED: {
          IPAddress ip = ptWss->remoteIP(num);
          DBG_OUTPUT.printf("Wifi [%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
          ptWss->sendTXT(num, "Connected");
        }
        break;
      case WStype_TEXT:
        DBG_OUTPUT.printf("Wifi [%u] get Text: %s\n", num, payload);
        mInputMsg = (char*)payload;
        mState = 0;
#ifdef LCD
        lcd.setCursor(0, 2);
        lcd.print("Message from WiFi   ");
#endif
        break;
    }
  });
  DBG_OUTPUT.printf("WebSocket started on port %d.\n", mPort);
}

/******************************** loop ********************************/

void GW_WebSockets::loop() {
  ptWss->loop();
}

/******************************** getInputMsg ********************************/

const char* GW_WebSockets::getInputMsg() {
  return mInputMsg;
}

/******************************** msgRx ********************************/

int GW_WebSockets::msgRx() {
  return mState;
}

/******************************** broadcastTXT ********************************/

bool GW_WebSockets::broadcastTXT(const char * text) {
  ptWss->broadcastTXT(text);
}
