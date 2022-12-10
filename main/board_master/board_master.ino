#include <esp_now.h>
#include <WiFi.h>

// Signals
#define SIGNAL_ERROR -1
#define SIGNAL_RESET 0
#define SIGNAL_START 1
#define SIGNAL_WIN 2
#define SIGNAL_FAIL 3

// Puzzle states
#define STATE_IDLE 0
#define STATE_START 1
#define STATE_COLORE 2
#define STATE_SIMON 3
#define STATE_ACCES3C 4
#define STATE_ENSEMBLEIA 5
#define STATE_HYDROLIQUE 6
#define STATE_WIN 7

// Puzzles
#define BOARD_TESTING 0
#define BOARD_COLORE 1
#define BOARD_SIMON 2
#define BOARD_ACCES3C 3
#define BOARD_ENSEMBLEIA 4
#define BOARD_HYDROLIQUE 5
#define BOARD_MASTER 42

// For reference
uint8_t boardTesting[]    = {0x7C, 0x9E, 0xBD, 0x49, 0x0C, 0xAC}; // 0
uint8_t boardColore[]     = {0x7C, 0x9E, 0xBD, 0x48, 0x75, 0xC4}; // 1
uint8_t boardSimon[]      = {0xE8, 0xDB, 0x84, 0x17, 0xB9, 0x20}; // 2
uint8_t boardAcces3c[]    = {0xC0, 0x49, 0xEF, 0xFA, 0x07, 0x8C}; // 3
uint8_t boardEnsembleIA[] = {0xE8, 0x68, 0xE7, 0x2B, 0x9C, 0x64}; // 4
uint8_t boardHydrolique[] = {0xE8, 0x68, 0xE7, 0x2B, 0x5B, 0xC0}; // 5
uint8_t boardMaster[]     = {0xE8, 0x68, 0xE7, 0x2E, 0x44, 0x94}; // 42

uint8_t* boards[6] = {boardTesting, boardColore, boardSimon, boardAcces3c, boardEnsembleIA, boardHydrolique};

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  int id;  
  int state;
  long timestamp;
} struct_message;

struct_message inData; // Data received
struct_message outData; // Data sent

struct_message boardTestingData;
struct_message boardColoreData;
struct_message boardSimonData;
struct_message boardAcces3cData;
struct_message boardEnsembleIAData;
struct_message boardHydroliqueData;

struct_message boardsDataStruct[6] = {boardTestingData, boardColoreData, boardSimonData, boardAcces3cData, boardEnsembleIAData, boardHydroliqueData};

esp_now_peer_info_t peerInfo;

esp_err_t result;

int state;

void sendOutData(const uint8_t * mac_addr, int state) {
  outData.state = state;
  
  char macStr[18];
  Serial.print("Packet sent to: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print("; ");
  
  result = esp_now_send(mac_addr, (uint8_t *) &outData, sizeof(outData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\tLast Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(macStr);
  
  memcpy(&inData, incomingData, sizeof(inData));
  Serial.print("\tBytes received: ");
  Serial.print(len);
  Serial.print(", Id: ");
  Serial.print(inData.id);
  Serial.print(", Value: ");
  Serial.println(inData.state);

  boardsDataStruct[inData.id].state = inData.state;
  boardsDataStruct[inData.id].timestamp = millis();
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // register peer
  memcpy(peerInfo.peer_addr, boardTesting, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: boardTesting");
    return;
  }
  // register peer
  memcpy(peerInfo.peer_addr, boardColore, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: boardColore");
    return;
  }
  // register peer
  memcpy(peerInfo.peer_addr, boardSimon, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: boardSimon");
    return;
  }
  // register peer
  memcpy(peerInfo.peer_addr, boardAcces3c, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: boardAcces3c");
    return;
  }
  // register peer
  memcpy(peerInfo.peer_addr, boardEnsembleIA, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: boardEnsembleIA");
    return;
  }
  // register peer
  memcpy(peerInfo.peer_addr, boardHydrolique, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: boardHydrolique");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  // Set ID
  outData.id = 42;
  
  // Send reset via ESP-NOW
  sendOutData(boardTesting, SIGNAL_RESET);
  sendOutData(boardColore, SIGNAL_RESET);
  sendOutData(boardSimon, SIGNAL_RESET);
  sendOutData(boardAcces3c, SIGNAL_RESET);
  sendOutData(boardEnsembleIA, SIGNAL_RESET);
  sendOutData(boardHydrolique, SIGNAL_RESET);

  state = STATE_IDLE;
}
 
void loop() {
//  int randm = random(1,20);
//  
//  // Send message via ESP-NOW
//  sendOutData(boardTesting, randm);

  switch(state) {
    case STATE_START:
      Serial.println("Current state: STATE_START");
      sendOutData(boardTesting, SIGNAL_START);
      sendOutData(boardColore, SIGNAL_START);
      state = STATE_COLORE;
      break;
    case STATE_COLORE:
      Serial.println("Current state: STATE_COLORE");
      if(boardsDataStruct[BOARD_COLORE].state == SIGNAL_WIN) {
        sendOutData(boardSimon, SIGNAL_START);
        state = STATE_SIMON;
      }
      break;
    case STATE_SIMON:
      Serial.println("Current state: STATE_SIMON");
      if(boardsDataStruct[BOARD_COLORE].state == SIGNAL_WIN) {
        sendOutData(boardSimon, SIGNAL_START);
        state = STATE_SIMON;
      }
      break;
    case STATE_ACCES3C:
      Serial.println("Current state: STATE_ACCES3C");
      if(boardsDataStruct[BOARD_COLORE].state == SIGNAL_WIN) {
        sendOutData(boardSimon, SIGNAL_START);
        state = STATE_SIMON;
      }
      break;
    case STATE_ENSEMBLEIA:
      Serial.println("Current state: STATE_ENSEMBLEIA");
      if(boardsDataStruct[BOARD_COLORE].state == SIGNAL_WIN) {
        sendOutData(boardSimon, SIGNAL_START);
        state = STATE_SIMON;
      }
      break;
    case STATE_HYDROLIQUE:
      Serial.println("Current state: STATE_HYDROLIQUE");
      if(boardsDataStruct[BOARD_COLORE].state == SIGNAL_WIN) {
        sendOutData(boardSimon, SIGNAL_START);
        state = STATE_SIMON;
      }
      break;
    case STATE_WIN:
      Serial.println("Current state: STATE_WIN");
      delay(5000);
      break;
  }
  
  delay(2000);
}
