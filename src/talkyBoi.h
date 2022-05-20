/**
 * This h file contains the funkction callbacks from ESPNOW 
 * that is used for WIFI communication peer to peer with the mechatronic hand.
 * Save values into the struct "msg_to_send" with the "send" function which can be
 * calld from the main method. 
 * to add more values to the struct change the structre of "struct message".
 * 
 * The callback "OnDataSent" can be used to get information about the message status, "success" or "failure" on sent.
 * The callback "OnDataRecv" can be used to get information on recieve, this can be used to print the strct that is recievd over WIFI.
 * "msg_incoming" is the incoming struct that can be used to print the values(angles) or save the values(angles) as variables.
 */
#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "Config.h"

uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE6,0x79,0x9C}; //MAC-adress black tape
//uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE5,0x31,0xD8}; //MAC-adress silver tape
//uint8_t broadcastAdress[] = {0x7C,0x9E,0xBD,0x60,0xD1,0x8C}; //MAC masking tape
//uint8_t broadcastAdressModel[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4}; //MAC white tape

int recID = 0;
int error = 0;
int succ = 0;

typedef struct struct_message{
  int sendID;
  float thumbIP;
  float thumbMCP;
  float finger1PIP;
  float finger1MCP;
  float finger2PIP;
  float finger2MCP;
  float finger3PIP;
  float finger3MCP;
  float finger4PIP;
  float finger4MCP;
  float thumbOpp;
  float finger1Pot;
  float finger2Po;
  float finger3Po;
  float finger4Po;
  float opposition;
  float pot1;
  float pot2;
  float pot3;
  float pot4;
}struct_message;
 
struct_message msg_to_send;
struct_message msg_incoming;

// Callback when data is sent, triggerd when message is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    if(status == ESP_NOW_SEND_FAIL){
      error++;
    }else{ 
      succ++;
    }
}


/**
 * Callback when data is received, triggerd when a message is recievd
 */
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&msg_incoming, incomingData, sizeof(msg_incoming));
  recID = msg_incoming.sendID;
  Serial.print(recID);
  Serial.print(",");
  Serial.print(recID);
  Serial.print(",");
  Serial.println(recID);
}
/**
 * Used to print the current ESP's MAC-adress which is used to for peer to peer communication with ESPNOW.'
 * This adress is added to the ESP that SENDS data, if you only reciev no MAC-adress is needed
 */
void getMACAdress(){
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}
/**
 * Used to print error messages if WIFI is not initializd.
 * Also inits the ESPNOW protocol with MAC-adresses and peerInfo.
 */
void init_wifi(){
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  esp_now_register_send_cb(OnDataSent);
 
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAdress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
 
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

/**
 * This function is used to send data over WIFI, takes arguments sendID(incremented value to keep track of the number of sent packages)
 * The rest of the arguments is values in the form of angles(already filterd and proccssed).
 * Call this function from main when a message over wifi should be sent.
 */
void send(float sendID, float thumbIP, float thumbMCP, float finger1PIP, float finger1MCP, float finger2PIP, float finger2MCP, float finger3PIP, float finger3MCP, float finger4PIP, float finger4MCP,float opposition,float pot1,float pot2,float pot3,float pot4){
  msg_to_send.sendID = sendID;
  msg_to_send.thumbIP = thumbIP;
  msg_to_send.thumbMCP = thumbMCP;
  msg_to_send.finger1PIP = finger1PIP;
  msg_to_send.finger1MCP = finger1MCP;
  msg_to_send.finger2PIP = finger2PIP;
  msg_to_send.finger2MCP = finger2MCP;
  msg_to_send.finger3PIP = finger3PIP;
  msg_to_send.finger3MCP = finger3MCP;
  msg_to_send.finger4PIP = finger4PIP;
  msg_to_send.finger4MCP = finger4MCP;
  msg_to_send.opposition = opposition;
  msg_to_send.pot1 = pot1;
  msg_to_send.pot2 = pot2;
  msg_to_send.pot3 = pot3;
  msg_to_send.pot4 = pot4;

  esp_err_t result = esp_now_send(broadcastAdress, (uint8_t *) &msg_to_send, sizeof(msg_to_send));
}
/**
 * This is not used.
 */
void sendToModel(int sendID, float thumbIP, float thumbMCP){
  Serial.println("Send to model : ");
  uint8_t broadcastAdress[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4};
  msg_to_send.sendID = sendID;
  esp_err_t result = esp_now_send(broadcastAdress,(uint8_t *) &msg_to_send, sizeof(msg_to_send));
}
/**
 * This is not used.
 */
void recieve() {
  
}