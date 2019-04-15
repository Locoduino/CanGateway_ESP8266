/*


    Passerelle Wifi/CAN avec un ESP8266 et un module CAN MCP2515

    Passerelle entre un reseau WiFi et un bus CAN et communication avec un port série.

    http://www.locoduino.org - Christophe BOBILLE sept 2018 - mars 2019
    christophe.bobille@gmail.com

    Exemple de message echange avec les satellites  : unsigned char mInputMsg[]  = "0x25 0 3 0x93 0x00  0x9F";

    Pour une documentation detaillee sur les fonctions de l'ESP8266 :
    https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html

    Bibliotheques :
    - arduinoWebSockets @ https://github.com/Links2004/arduinoWebSockets
    - CAN Bus Shield @ https://github.com/Locoduino/CAN_BUS_Shield (Bibliotheque Seeed-Studio/CAN_BUS_Shield modifiee)

    Mapping @ http://www.locoduino.org/local/cache-vignettes/L438xH1000/nodemcu_niren-4b03c.jpg?1552261120
*/

#define VERSION  "2.4"
#define PROJECT  "WiFi_CAN_gateway"


#include <Arduino.h>
#include "Config.h"
#include "SerialCtrl.h"
#include "CanCtrl.h"
#include "Wifi.h"
#include "Files.h"
#include "WebSockets.h"
#include "WebServ.h"
#include <Wire.h>
#ifdef LCD
#include <LiquidCrystal_I2C.h>
#endif


// Selection des redirections souhaitees

const bool sendToSerial = false;
const bool sendToCan = true;
const bool sendToWifi = true;



GW_Can canCtrl;                     // Instance de GW_Can
GW_Serial serialCtrl(Serial);       // Instance de GW_Serial avec un objet Serial
Wifi wifi;                          // Instance de Wifi
Files files;                        // Instance de File

GW_WebServ webServer(80);           // Instance de WebServer sur le port 80
GW_WebSockets webSocketsCtrl(81);   // Instance de WebSocket sur le port 81


#ifdef LCD
LiquidCrystal_I2C lcd(0x3F, 20, 4);       // Instance de LiquidCrystal_I2C avec l'adresse 0x3F (20 chars and 4 line display)
#endif

/*__________________________________________________________SETUP__________________________________________________________*/

void setup() {

  // Port serie
  DBG_OUTPUT.begin(115200);
  //DBG_OUTPUT.setDebugOutput(true); // Debug + complet
  // Infos du projet
  DBG_OUTPUT.print("\n\n\n");
  DBG_OUTPUT.print("Project :      ");
  DBG_OUTPUT.print(PROJECT);
  DBG_OUTPUT.print("\nVersion :      ");
  DBG_OUTPUT.print(VERSION);
  DBG_OUTPUT.print("\nCompiled :     ");
  DBG_OUTPUT.print(__DATE__);
  DBG_OUTPUT.print(" ");
  DBG_OUTPUT.print(__TIME__);
  DBG_OUTPUT.print("\n\n");

  // Initialisations
#ifdef LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
#endif
  serialCtrl.begin(115200);
  wifi.begin();
  files.begin();
  webServer.start();
  webSocketsCtrl.begin();

  //Bus CAN
  int err = canCtrl.begin(CAN_BAUDRATE, CAN_CSPIN, CAN_INTERPIN);
  switch (err) {
    case 0 :
      DBG_OUTPUT.print("CAN ok !\n\n");
#ifdef LCD
      lcd.print("CAN ok !");
#endif
      break;
    case -1 :
      DBG_OUTPUT.print("Probleme de connexion CAN !\n");
      DBG_OUTPUT.print("Programme interrompu.");
#ifdef LCD
      lcd.print("Probleme de connexion CAN !\n");
      lcd.setCursor(0, 1);
      lcd.print("Programme interrompu.");
#endif
      return;
  }

#ifdef LCD
  // Retour de l'adresse IP sur LCD
  lcd.setCursor(0, 1);
  lcd.print("IP : ");
  lcd.print(WiFi.localIP());
  delay(100);
#endif

  DBG_OUTPUT.print("End of setup.\n\n");

} // End setup


/*__________________________________________________________LOOP__________________________________________________________*/

void loop() {

  static int err { 0 };

  webSocketsCtrl.loop();               // Ecoute du port 81
  webServer.handleClient();            // Ecoute du port 80


  // INCOMING messages sur le port Serial et envoi sur les bus CAN et wifi
  err = serialCtrl.msgRx();
  switch (err) {
    case 0 :  // Message sur port serie
#ifdef LCD
      lcd.setCursor(0, 2);
      lcd.print("Msg from Serial port");
#endif
      if (sendToCan)
        canCtrl.msgTx(serialCtrl.getInputMsg());    // Envoi sur le bus CAN
      if (sendToWifi)
        webSocketsCtrl.broadcastTXT(serialCtrl.getInputMsg()); // Envoi sur le réseau wifi
      break;
  }

  // INCOMING messages sur le bus CAN et envoi sur le port Serial et wifi
  err = canCtrl.msgRx();
  switch (err) {
    case 0 :
#ifdef LCD
      lcd.setCursor(0, 2);
      lcd.print("Message from CAN bus");
#endif
      if (sendToSerial)
        serialCtrl.msgTx(canCtrl.getInputMsg()); // Envoi sur le port serie
      if (sendToWifi)
        webSocketsCtrl.broadcastTXT(canCtrl.getInputMsg()); // Envoi sur le réseau wifi
      break;
  }

  // INCOMING messages en Wifi et envoi sur le port Serial et bus Can
  err = webSocketsCtrl.msgRx();
  switch (err) {
    case 0 :
#ifdef LCD
      lcd.setCursor(0, 2);
      lcd.print("Message from Wifi");
#endif
      if (sendToSerial)
        serialCtrl.msgTx(webSocketsCtrl.getInputMsg()); // Envoi sur le port serie
      if (sendToCan)
        canCtrl.msgTx(webSocketsCtrl.getInputMsg());    // Envoi sur le bus CAN
      break;
  }

  delay(10);
} // End loop
