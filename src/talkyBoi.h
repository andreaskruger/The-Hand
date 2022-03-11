#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

//uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE6,0x79,0x9C}; //MAC-adress till den svarta
uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE5,0x31,0xD8}; //MAC-adress till den silver
//uint8_t broadcastAdress[] = {0x7C,0x9E,0xBD,0x60,0xD1,0x8C}; //MAC till den med maskering
//uint8_t broadcastAdressModel[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4}; //MAC till den med vit tejp

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
  float test12;
  float test13;
  float test14;
  float test15;
}struct_message;
 
struct_message msg_to_send;
struct_message msg_incoming;

// Callback when data is sent, triggas när något skickas
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    //Serial.write((String)mac_addr));
    Serial.print(mac_addr[0], HEX);
    Serial.print(",");
    Serial.print(mac_addr[1], HEX);
    Serial.print(",");
    Serial.print(mac_addr[2], HEX);
    Serial.print(",");
    Serial.print(mac_addr[3], HEX);
    Serial.print(",");
    Serial.print(mac_addr[4], HEX);
    Serial.print(",");
    Serial.println(mac_addr[5], HEX);
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    if(status == ESP_NOW_SEND_FAIL){
      error++;
    }else{ 
      succ++;
    }
}

// Callback when data is received, triggas när något mottas (används ej)
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&msg_incoming, incomingData, sizeof(msg_incoming));
  recID = msg_incoming.sendID;
  Serial.print(recID);
  Serial.print(",");
  Serial.print(recID);
  Serial.print(",");
  Serial.println(recID);
  
}

void getMACAdress(){
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}

void init_wifi (){
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

void send (float sendID, float thumbIP, float thumbMCP, float finger1PIP, float finger1MCP, float finger2PIP, float finger2MCP, float finger3PIP, float finger3MCP, float finger4PIP, float finger4MCP){
  uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE5,0x31,0xD8};
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

  esp_err_t result = esp_now_send(broadcastAdress, (uint8_t *) &msg_to_send, sizeof(msg_to_send));
}
void sendToModel(int sendID, float thumbIP, float thumbMCP){
  Serial.println("Send to model : ");
  uint8_t broadcastAdress[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4};
  msg_to_send.sendID = sendID;
  esp_err_t result = esp_now_send(broadcastAdress,(uint8_t *) &msg_to_send, sizeof(msg_to_send));
}
void recieve () {
  
}