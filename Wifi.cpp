/*
   WiFi.cpp

*/



#include "Wifi.h"

void Wifi::begin() {
  DBG_OUTPUT.print("Wifi connecting to AP\t");

  WiFi.begin(WIFI_SSID, WIFI_PSW);
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    DBG_OUTPUT.print('.');
  }

  DBG_OUTPUT.print('\n');
  DBG_OUTPUT.print("Wifi connection established !");
  DBG_OUTPUT.print('\n');
  DBG_OUTPUT.print("IP address :.....");
  DBG_OUTPUT.print(WiFi.localIP());
  DBG_OUTPUT.print('\n');
  DBG_OUTPUT.print("Netmask :........");
  DBG_OUTPUT.print(WiFi.subnetMask());
  DBG_OUTPUT.print('\n');
  DBG_OUTPUT.print("Gateway :........");
  DBG_OUTPUT.print(WiFi.gatewayIP());
  DBG_OUTPUT.print('\n');
  DBG_OUTPUT.print("Mac adress :.....");
  DBG_OUTPUT.print(WiFi.macAddress());
  DBG_OUTPUT.print('\n');



#ifdef ESP32
  if (MDNS.begin(HOST)) {
    DBG_OUTPUT.print("DNS http://");
    DBG_OUTPUT.print(HOST);
    DBG_OUTPUT.println(".local/\n");
  }
  else
    DBG_OUTPUT.print("Error setting up MDNS responder !\n");
#else // mDNS ne fonctionne pas avec l'ESP8266 (et Mac ?)
  WiFi.hostname(HOST); // Si le routeur l'autorise
  DBG_OUTPUT.print("DNS :............http://");
  DBG_OUTPUT.print(WiFi.hostname().c_str());
  DBG_OUTPUT.println("/\n");
#endif


  DBG_OUTPUT.print("\n\n");
}
