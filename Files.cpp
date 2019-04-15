/*
   Files.cpp

*/


#include "Files.h"

void Files::begin() {
  SPIFFS.begin();
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  DBG_OUTPUT.print("SPIFFS total :..........");
  DBG_OUTPUT.print(fs_info.totalBytes/1024);
  DBG_OUTPUT.print(" Ko\n");
  DBG_OUTPUT.print("SPIFFS used  :..........");
  DBG_OUTPUT.print(fs_info.usedBytes/1024);
  DBG_OUTPUT.print(" Ko\n");
  DBG_OUTPUT.print("SPIFFS free  :..........");
  DBG_OUTPUT.print((fs_info.totalBytes - fs_info.usedBytes)/1024);
  DBG_OUTPUT.print(" Ko\n\n");
}


bool Files::handleFileRead(ESP8266WebServer* webServer) { // send the right file to the client (if it exists)
  String path = webServer->uri();
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = Files::getContentType(path);     // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = webServer->streamFile(file, contentType); // And send it to the client
    file.close(); // Then close the file again
    return (1);
  }
  DBG_OUTPUT.println("File Not Found");
  webServer->send(404, "text/plain", "404: File Not Found");
  return (0);                                         // If the file doesn't exist, return false
}


String Files::getContentType(String filename) { // determine the filetype of a given filename, based on the extension
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
