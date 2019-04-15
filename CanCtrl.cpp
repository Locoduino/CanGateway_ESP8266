/*
   Can.cpp

*/
#include "CanCtrl.h"



/*********************** Interruption pour CAN ****************************/
volatile bool flagCanRx {
  false
};      // pour IRQ



/****************************** Constructeur ******************************/

GW_Can::GW_Can() {
  mBaudRate = 0;
  mSPIpin = 255;
  mInterPin = 255;
  ptCan = NULL;
}

/********************************* begin *********************************/

int GW_Can::begin(uint8_t baudrate, uint8_t canCS, uint8_t interPin) {
  mBaudRate = baudrate;
  mInterPin = interPin;
  mSPIpin = canCS;
  pinMode(mSPIpin, INPUT);
  ptCan = new MCP_CAN(mSPIpin);
  ptCan->start();
  int repeat = 10;
  while (repeat >= 0) {
    if (CAN_OK == ptCan->begin(mBaudRate)) {
      pinMode(mInterPin, INPUT);
      attachInterrupt(digitalPinToInterrupt(interPin), [](){flagCanRx = true;}, FALLING);
      return 0;
    }
    else {
      repeat--;
      if (repeat < 0) {
        delete ptCan;
        ptCan = NULL;
        return repeat;
      }
    }
    delay(500);
  }
}

/******************************* parseMsg *******************************/

void GW_Can::parseMsg(const char* msg) {
  char * ptEnd;
  mTxId = strtol (msg, &ptEnd, 16);
  mTxIdType = strtol (ptEnd, &ptEnd, 10);
  mTxLen = strtol (ptEnd, &ptEnd, 10);
  for ( int i = 0; i < mTxLen; i++)
    mTxStmp[i] = strtol (ptEnd, &ptEnd, 16);
}


/******************************** msgTx ********************************/

void GW_Can::msgTx(const char* msg) {

  parseMsg(msg); // Parsing du message

#ifdef DEBUG
  DBG_OUTPUT.print("\nEnvoi d'un message sur le bus CAN\n");
  DBG_OUTPUT.print("mTxId      : 0x"); DBG_OUTPUT.println((char)mTxId, HEX);
  DBG_OUTPUT.print("mTxIdType  : "); DBG_OUTPUT.println(mTxIdType, DEC);
  DBG_OUTPUT.print("mTxLen     : "); DBG_OUTPUT.println(mTxLen, DEC);
  for (byte i = 0; i < mTxLen; i++) {
    DBG_OUTPUT.print("mTxStmp["); DBG_OUTPUT.print(i); DBG_OUTPUT.print("] : "); DBG_OUTPUT.println(mTxStmp[i], HEX);
  }
  DBG_OUTPUT.print("\n");
#endif

  ptCan->sendMsgBuf(mTxId, mTxIdType, mTxLen, mTxStmp);
}

/******************************** msgRx ********************************/

int GW_Can::msgRx() {
  if (flagCanRx)  {

    while (CAN_MSGAVAIL == ptCan->checkReceive())  {
      ptCan->readMsgBuf(&mRxLen, (byte*)mRxBuf);
      mRxId = ptCan->getCanId();
      sprintf(mInputMsg, "%d %d %d", mRxId, mRxBuf[0], mRxBuf[1]);
#ifdef DEBUG
      DBG_OUTPUT.print("Reception d'un message sur le bus CAN : ");
      DBG_OUTPUT.print("Id: 0x"); DBG_OUTPUT.print((char)mRxId, HEX);
      for (uint8_t i = 0; i < mRxLen; i++) {
        DBG_OUTPUT.print(" 0x"); DBG_OUTPUT.print(mRxBuf[i], HEX);
      }
      DBG_OUTPUT.print("\n");
#endif
    }
    flagCanRx = false;
    return 0;
  }
  else
    return 1;
}

const char* GW_Can::getInputMsg() {
  return mInputMsg;
}
