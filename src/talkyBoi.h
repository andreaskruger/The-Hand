#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE4,0x84,0x34}; //MAC-adress till den svarta
//uint8_t broadcastAdress[] = {0x7C,0x9E,0xBD,0x60,0xD1,0x8C}; //MAC till den med kondensatorn
//uint8_t broadcastAdress[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4}; //MAC till den med vit tejp

typedef struct struct_message{
  int test1;
  int test2;
  int test3;
  int test4;
  int test5;
  int test6;
  int test7;
  int test8;
  int test9;
  int test10;
  int test11;
}struct_message;
 
struct_message msg_to_send;
struct_message testINC;

// Callback when data is sent, triggas när något skickas
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received, triggas när något mottas (används ej)
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&testINC, incomingData, sizeof(testINC));
  Serial.print("Bytes received: ");
  Serial.println(len);
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

void send (){
  msg_to_send.test1 = 1;
  msg_to_send.test2 = 2;
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
  delay(1000);

}

void recieve () {

}