/*
   Config.h

*/


#ifndef __config_H__
#define __config_H__


#define DEBUG                           // Ne pas oublier de commenter en production
#define DBG_OUTPUT           Serial1    // Debug sur le port Serial1 sur GPIO2 (D4)
//#define LCD                           // Dans le cas ou il y a un ecran LCD

// WIFI
#define WIFI_SSID          "your_SSID"
#define WIFI_PSW           "your_PSW"

#define HOST                 "cangw"


// SERIAL
#define SERIAL_BAUDRATE    115200

// CAN
/* PINS:  CS=D0, INT=D4, SCK=D5, SO=D6, SI=D7 */
#define CAN_CSPIN              16   // Set CS to pin 16 (D0)
#define CAN_INTERPIN            2   // Set INT to pin 2 (D4)

#define CAN_BAUDRATE           18

/*
  Value  | Speed (define name)
    ------ | -------------------
    1    | CAN_5KBPS
    2    | CAN_10KBPS
    3    | CAN_20KBPS
    4    | CAN_25KBPS
    5    | CAN_31K25BPS
    6    | CAN_33KBPS
    7    | CAN_40KBPS
    8    | CAN_50KBPS
    9    | CAN_80KBPS
    10     | CAN_83K3BPS
    11     | CAN_95KBPS
    12     | CAN_100KBPS
    13     | CAN_125KBPS
    14     | CAN_200KBPS
    15     | CAN_250KBPS
    16     | CAN_500KBPS
    17     | CAN_666KBPS
    18     | CAN_1000KBPS
*/

/*
Pins
*/
// D0 = 16;
// D1 = 5;
// D2 = 4;
// D3 = 0;
// D4 = 2;
// D5 = 14;
// D6 = 12;
// D7 = 13;
// D8 = 15;
// D9 = 3;
// D10 = 1;


#endif
