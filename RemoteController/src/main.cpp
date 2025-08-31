#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#include "segDrive.h"

#define RFM95_CS   10   // NSS → D10
#define RFM95_RST  0    // RESET → D0
#define RFM95_INT 2    // DIO0 → D2

#define SSR_SWITCH_PIN 1

int ssrPinState; // SSR Switch state

String moduleId = "exampleID"; // Module ID
// Function Prototypes
int getSSRState();
int sendMessage();
// Function Prototypes End

void setup() {
  //Serial.begin(9600);
  //while (!Serial);

  //Serial.println("LoRa Sender");

  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT); // Set LoRa module pins: SS, RST, DIO0

  if (!LoRa.begin(420E6)) {
    //Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  // Menzil max settings
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.setCodingRate4(8);


  pinMode(SSR_SWITCH_PIN, INPUT);  // set SSR_SWITCH_PIN as input


  initSegment(); // Initialize the 7-segment display

  close();
  int loop_times = 0;
  while(1) {
    int result = sendMessage();
    if (result == -1)  // if no data received for 5 seconds
    {
      writeError(loop_times);
      loop_times++;      
      if (loop_times == 3) {
      loop_times = 0; // reset after showing error 3 times
      }
    }
    else
    {
      break;
    }   
  }
}

void loop() {
  if (ssrPinState != digitalRead(SSR_SWITCH_PIN))
  {
    close();
    int loop_times = 0;
    while(1) {
      int result = sendMessage();
      if (result == -1)  // if no data received for 5 seconds
      {
        writeError(loop_times);
        loop_times++;      
        if (loop_times == 3) {
        loop_times = 0; // reset after showing error 3 times
        }
      }
      else
      {
        break;
      }   
    }
  }
  
  if (ssrPinState == LOW)
  {
    writeON();
  } else {
    writeOFF();
  }
}


int getSSRState() {
  unsigned long millis_ = millis(); // current time in milliseconds
  while (1)
  {
    String LoRaData = ""; // reset LoRaData for each loop iteration
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      // received a packet

      // read packet
      while (LoRa.available()) {
        LoRaData = LoRa.readString();
      }
      
         
      if (LoRaData == "ON") {
        return 1;
      } else if (LoRaData == "OFF") {
        return 0;
      }
    }if (millis() - millis_ > 5000) {
      return -1; // return -1 if no data received for 5 seconds
    }
  }
}

int sendMessage() {
  ssrPinState = digitalRead(SSR_SWITCH_PIN);  // read SSR state
  if (ssrPinState == HIGH) {
    //Serial.println("SSR Opening...");
    // Paket gönder
    LoRa.beginPacket();
    LoRa.print(moduleId + ":" + "OFF"); // set message to "OFF"
    LoRa.endPacket();
  } else {
    //Serial.println("SSR Closing...");
    // Paket gönder
    LoRa.beginPacket();
    LoRa.print(moduleId + ":" + "ON"); // set message to "ON"
    LoRa.endPacket();
  }
  return getSSRState(); // get SSR state
}
