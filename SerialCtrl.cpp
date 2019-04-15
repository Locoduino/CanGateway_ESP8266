/*
   DBG_OUTPUT.cpp

*/

#include "SerialCtrl.h"

/******************** Interruption pour SERIAL *************************/

volatile bool flagSerialRx {
  true
};      // pour IRQ

void serialEvent() {
  flagSerialRx = true;
}

/****************************** Constructeur ******************************/

GW_Serial::GW_Serial(HardwareSerial &serial) : serialControl(serial) {
  mBaudRate = 0;
}


/******************************** begin ********************************/

void GW_Serial::begin(uint64_t baudRate) {
  mBaudRate = baudRate;
  serialControl.begin(baudRate);
  DBG_OUTPUT.print("\nSerial port ok !\n");
}


/******************************** print ********************************/

void GW_Serial::print(const char* text) {
  serialControl.print(text);
}


/******************************** msgTx ********************************/

void GW_Serial::msgTx(const char* text) {
  serialControl.println(text);
}

/******************************** msgRx ********************************/

int GW_Serial::msgRx() {
  int err = -1;
  byte i = 0;
  while (serialControl.available()) {
    char inChar = (char)serialControl.read();
    mInputMsg[i] = inChar;
    i++;
    if (inChar == '\n') {
      err = 0;
#ifdef DEBUG
      DBG_OUTPUT.print("Serial get Text: ");
      DBG_OUTPUT.print(mInputMsg);
#endif
    }
    delay(1);
  }
  return err;
}

/******************************** getInputMsg ********************************/

const char* GW_Serial::getInputMsg() {
  return mInputMsg;
}
