# CanGateway_ESP8266
Gateway CAN/WiFi/Serial with ESP8266

<h1>Passerelle CAN/WiFI/Serial sur ESP8266</h1>
<p>Cette passerelle permet d'interconnecter un bus CAN avec un réseau en Ethernet et/ou WiFi mais également en utilisant le port série de l'ESP8266.</p>
<p><img src="http://www.locoduino.org/local/cache-vignettes/L500xH326/locoduino_wifi_can-gatewayesp8266_nirenmcp2515_dsc6798-33ae1.jpg?1548598275"  height="398" width="610"></p>></p>
<p>Ce projet est compatible avec la norme CAN V2.0B et permet d'utiliser des identifiants standards à 11 bits ou étendus à 29 bits.</p>
<p>La bibliothèque utilisée est CAN_BUS_Shield de Seeed-Studio <strong>modifiée par Locoduino</strong> et disponible ici : <a href="https://github.com/Locoduino/CAN_BUS_Shield">https://github.com/Locoduino/CAN_BUS_Shield</a></p>
<p>Le projet est encore en cours de développement mais néanmoins opérationnel.</p>
<p>Un schéma de câblage avec un module NiRen est disponible ici : <a href="http://www.locoduino.org/local/cache-vignettes/L438xH1000/nodemcu_niren-4b03c.jpg?1552261120" rel="nofollow">http://www.locoduino.org/local/cache-vignettes/L438xH1000/nodemcu_niren-4b03c.jpg?1552261120</a></p>
<p>Le dossier data contient une application HTML/JavaScript de démo qui doit être copié dans la mémoire SPIFF de l'ESP pour être utilisé.</p>

<p><img src="http://www.locoduino.org/local/cache-vignettes/L610xH596/ecran_reglage_satellites_01-1-43103.png?1548598657" height="596" width="610"></p>


<p>Les réglages sont à faire dans le fichier « Config.h » en renseignant l'identifiant de votre réseau (SSID) et le mot de passe (PSW)</p>
<p>
<code>
// WIFI<br>
  #define WIFI_SSID "your_SSID"<br>
#define WIFI_PSW  "your_PSW"
</code></p>
<p>Le mapping des pins avec un controleur CAN est renseigné également dans ce fichier :</p>
<p>
<code>
/* PINS: CS=D0, INT=D4, SCK=D5, SO=D6, SI=D7 */<br>
  #define CAN_CSPIN 16   // Set CS to pin 16 (D0)<br>
  #define CAN_INTERPIN 2 // Set INT to pin 2 (D4)
</code></p>
  
<p>Ainsi que la vitesse du bus CAN</p>
<p><code>
#define CAN_BAUDRATE 18
</code></p>

<p>Un debug peut être affiché en utilisant le port Serial1 de l'ESP dont le TX est disponible sur la pin D4.</p>

<p>
<code>
#define DBG_OUTPUT Serial1 // Debug sur le port Serial1 sur GPIO2 (D4)
</code>
</p>
<p>Vous pouvez modifier <strong>#define DBG_OUTPUT Serial</strong> pour afficher le debug sur le moniteur série relié au port USB de l'ESP8266.</p>
<p>Le programme est configuré pour pouvoir fournir une adresse DNS qui est cangw (modifiable).</p>
<p>#define HOST "cangw"</p>
<p>Après lancement du programme, l'application est normalement disponible à l'adresse : http://cangw/satellite.html</p>
<p>En cas de problème avec l'adresse DNS, l'adresse IP du serveur s'affiche dans le moniteur du debug :</p>
<blockquote>
<p>Serial port ok !<br>
  Wifi connecting to AP....<br>
  Wifi connection established !<br>
  IP address :.....192.168.86.38<br>
  Netmask :........255.255.255.0<br>
  Gateway :........192.168.86.1<br>
  Mac adress :.....84:F3:EB:18:76:2C<br>
  DNS :............http://cangw/</p>
</blockquote>
<p>P address : 192.168.86.38. L'application devra alors être appelée sur l'URL : http://192.168.86.38/satellite.html</p>
<p>En manipulant les boutons et sliders, les informations de positions sont envoyées en temps réel et seront visibles dans la fenêtre du moniteur sous cette forme :</p>
<p>Wifi [0] get Text: 0x1FFFFF21 1 3 0x1 0x12 0x73</p>
<p>Il s'agit  d'un message CAN avec un identifiant sur 11 bits (0x1FFFFF21) avec 3 octets de données (0x1 0x12 0x73).</p>
<p>Notez que ce même message : 0x1FFFFF21 1 3 0x1 0x12 0x73 pourrait être directement saisie dans une application gérant des communications	série ou plus simplement dans la zone de saisie de la fenêtre moniteur de l'IDE Arduino si vous utilisez cette application.</p>
