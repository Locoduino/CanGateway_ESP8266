/*
   Can.h

*/

#ifndef _gatewayCan_H_
#define _gatewayCan_H_

#include <Arduino.h>
#include <SPI.h>                      // bus SPI
#include <mcp_can.h>                  // bus CAN
#include "Config.h"


/****************************************************************/
/*                            CAN                               */
/****************************************************************/

// PINS:  CS=D2, INT=D4, SCK=D5, SO=D6, SI=D7

class GW_Can {

  private:
    uint8_t mBaudRate;
    uint8_t mSPIpin;
    uint8_t mInterPin;
    /***       Variables CAN        ***/
    uint64_t mTxId;
    uint8_t mTxIdType;
    uint8_t mTxLen;
    uint8_t mTxStmp[8];

    char mInputMsg[255];

    uint64_t mRxId;
    uint8_t mRxLen;
    char mRxBuf[8];

    MCP_CAN *ptCan; 
  public:
    GW_Can();                     // Constructor
    int begin(uint8_t, uint8_t, uint8_t);
    int msgRx();
    void msgTx(const char*);
    void parseMsg(const char*);
    const char* getInputMsg();
    void loop();

};

#endif
