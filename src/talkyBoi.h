#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE6,0x79,0x9C}; //MAC-adress till den svarta
//uint8_t broadcastAdress[] = {0x7C,0x9E,0xBD,0x60,0xD1,0x8C}; //MAC till den med kondensatorn
//uint8_t broadcastAdress[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4}; //MAC till den med vit tejp

int recID = 0;
int error = 0;
int succ = 0;

typedef struct struct_message{
  float test1;
  float test2;
  float test3;
  float test4;
  float test5;
  float test6;
  float test7;
  float test8;
  float test9;
  float test10;
  float test11;
  float test12;
  float test13;
  float test14;
  float test15;
}struct_message;
 
struct_message msg_to_send;
struct_message testINC;

// Callback when data is sent, triggas när något skickas
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    if(status == ESP_NOW_SEND_FAIL ? error++ : succ++);
    Serial.println(error);
}

// Callback when data is received, triggas när något mottas (används ej)
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&testINC, incomingData, sizeof(testINC));
  //Serial.print("Bytes received: ");
  //Serial.println(len);
  //Serial.println(testINC.test1);
  recID++;
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

void send (float angle1, float angle2){
  msg_to_send.test1 = angle1;
  msg_to_send.test2 = angle2;
  msg_to_send.test3 = 3;
  msg_to_send.test4 = 4;
  msg_to_send.test5 = 5;
  msg_to_send.test6 = 6;
  msg_to_send.test7 = 7;
  msg_to_send.test8 = 8;
  msg_to_send.test9 = 9;
  msg_to_send.test10 = 10;
  msg_to_send.test11 = 11;
  esp_err_t result = esp_now_send(broadcastAdress, (uint8_t *) &msg_to_send, sizeof(msg_to_send));
 
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

void recieve () {

}

