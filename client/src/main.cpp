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


// ---[ CONFIGURABLES ]---
// Leave blank to get user input OR set a default value

// WiFi
const String ssid = "";
const String passwd = "";

// Server Info
String host = "";
uint16_t udp_port = 1337;
uint16_t tcp_port = 4269;


// ---[ System ]---

// Connection
WiFiClient tcp;
WiFiUDP udp;

// Operations
struct Operator {
  char symbol;
  String name;
};

Operator op;
float a, b, r;
String expression;

const Operator operators[] = {  // The inverse operator of I is last-I
  {'+', "sum"},
  {'*', "multiply"},
  {'v', "root"},
  {'^', "power"},
  {'/', "division"},
  {'-', "subtraction"},
};


#define NUM_OPERATORS (sizeof(operators) / sizeof(operators[0]))


void help();

bool isOperator(String str);
Operator getOperator(String str);
Operator getInverseOperator(Operator op);


void setup() {
  Serial.begin(9600);
  while (setupWiFi(ssid, passwd) != WL_CONNECTED) delay(1000);
  IPAddress ip;
  while (!ip.fromString(host)) host = input("\nHost Server IP: ");
  Serial.println("\nStarting Client...");
  Serial.println("Type 'h' for Help");
}


void loop() {
  expression = input("\nEnter an Expression\n> ");
  if (expression == "h") help();
  else {
    // TODO: Split expression terms

    // Testing Operators
    if (isOperator(expression)) {
      op = getOperator(expression);
      Serial.printf("Operator \"%s\", symbol '%c'\n", op.name, op.symbol);
      op = getInverseOperator(op);
      Serial.printf("Inverse  \"%s\", symbol '%c'\n", op.name, op.symbol);
    }
  }
}


void help() {
  Serial.println("\nExpression format: \"{float} {op} {float}\"");
  Serial.println("The operator 'op' can be a index, symbol or name, as listed:\nIndex\tSymbol\tName");
  for (int i = 0; i < NUM_OPERATORS; i++) Serial.printf("%d\t%c\t%s\n", i, operators[i].symbol, operators[i].name);
  Serial.println("\nThe operation will be sent to the Server by UDP, and its inverse operantion by TCP.");
  Serial.printf("[The inverse operator of I is %d-I]\n\n", NUM_OPERATORS-1);
}


bool isOperator(String str) {
  int i;
  if (isdigit(str[0])) {
    i = str.toInt();
    if (i >= 0 && i < NUM_OPERATORS) return true;
  }
  for (i = 0; i < NUM_OPERATORS; i++) {
    if (operators[i].symbol == str[0]) return true;
    if (operators[i].name == str) return true;
  }
  return false;
}

Operator getOperator(String str) {
  int i;
  if (isdigit(str[0])) {
    i = str.toInt();
    if (i >= 0 && i < NUM_OPERATORS) return operators[i];
  }
  for (i = 0; i < NUM_OPERATORS; i++) {
    if (operators[i].symbol == str[0]) return operators[i];
    if (operators[i].name == str) return operators[i];
  }
  return Operator {' ', "NOP"};
}

Operator getInverseOperator(Operator op) {
  int i;
  for (i = 0; i < NUM_OPERATORS; i++) if (operators[i].symbol == op.symbol) break;
  return operators[NUM_OPERATORS-1-i];
}