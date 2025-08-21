#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define RFM95_CS 10      // NSS → D10
#define RFM95_RST 3      // RESET → D3
#define RFM95_INT 2      // DIO0 → D2

#define SSR_SWITCH_PIN 4

String LoRaData;
String moduleId = "exampleID"; // Module ID

void setup() {
  Serial.begin(9600);
  Serial.println("Irrigation System Starting...");
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT); // Set LoRa module pins: SS, RST, DIO0
    
  if (!LoRa.begin(420E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  // Menzil max settings
  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.setCodingRate4(8);

  pinMode(SSR_SWITCH_PIN, OUTPUT);  // Set SSR_SWITCH_PIN as output
  digitalWrite(SSR_SWITCH_PIN, HIGH); // Set SSR to off initially
  
  Serial.println("Irrigation System Started");
}

void loop() {
 
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
    }
    Serial.print("Received packet: ");
    Serial.println(LoRaData);
    if (LoRaData == moduleId + ":" + "ON") {
      Serial.println("SSR open");
      digitalWrite(SSR_SWITCH_PIN, LOW); // open SSR
      // send feedback
      delay(1000); // wait 1 second
      Serial.println("sending feedback");
      LoRa.beginPacket();
      LoRa.print("ON"); // set message to "ON"
      LoRa.endPacket();
      Serial.println("feedback sended");
    } else if (LoRaData == moduleId + ":" + "OFF") {
      Serial.println("SSR close");
      digitalWrite(SSR_SWITCH_PIN, HIGH); // close SSR
      // send feedback
      delay(1000); // wait 1 second
      Serial.println("Sending feedback");
      LoRa.beginPacket();
      LoRa.print("OFF"); // set message to "OFF"
      LoRa.endPacket();
      Serial.println("feedback sended");
    }
    // print RSSI and SNR
    int rssi = LoRa.packetRssi();
    float snr = LoRa.packetSnr();
    
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");
    Serial.print("SNR: ");
    Serial.println(snr);
  }
}