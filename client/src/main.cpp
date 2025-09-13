// Multithread ESP32 Communication - Client


/* ─                     · ─ +
 |  Enzo Zavorski Delevatti  |
 .  @Zvorky                  ·
             ___,
          .~´    `-,
         /  _    _ \.        .
        ,\`|_|''|_|´\
 .       /          /)       |
        (\  ,    , .\`
 |       `) ;`,; `,^,)
         ´,´  `,  `  `
        
 |__ _  September 2025    _  |
/                           */


#include <Arduino.h>
#include <WiFi.h>
#include "utils.h"


// Leave blank to get user input OR set a default wifi
const String ssid = "";
const String passwd = "";

WiFiClient tcp;
WiFiUDP udp;

String host = "";
uint16_t udp_port = 1337;
uint16_t tcp_port = 4269;


void setup() {
  Serial.begin(9600);
  while (setupWiFi(ssid, passwd) != WL_CONNECTED) delay(1000);
  Serial.println("\nStarting Client...");
}


void loop() {
  Serial.println("TODO");
  delay(1000);
}