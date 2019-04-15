
/*
   WebSockets.h

*/

#ifndef _webSockets_H_
#define _webSockets_H_

#include <Arduino.h>
#include <WebSocketsServer.h> 
#include "Config.h"
 


class GW_WebSockets {

  private:
    uint16_t mPort;
    String   mOrigin;
    String   mProtocol;
    char*    mInputMsg;
    int      mState = 0;

  public:
    GW_WebSockets(uint16_t port);
    WebSocketsServer* ptWss;

    void begin();
    const char* getInputMsg();
    int msgRx();
    void loop();
    bool broadcastTXT(const char *);
    void onWsEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
};



#endif
