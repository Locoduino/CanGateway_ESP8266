/*
   Files.h

*/

#ifndef __Files_H__
#define __Files_H__


#include "FS.h"
#include <Arduino.h>
#include "WebServ.h"
#include "Config.h"


struct Files {

  //static ESP8266WebServer *webServer;
  static void begin();
  static bool handleFileRead(ESP8266WebServer *);
  static String getContentType(String);

};

#endif
