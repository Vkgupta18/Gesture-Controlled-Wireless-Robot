#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

// void receiverSetup() {
  
// }

void setup() {
  
  Serial.begin(9600);
  radio.begin();

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  // radio.setCRCLength(RF24_CRC_8);
  // receiverSetup();
  printf_begin();
  radio.printDetails();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(radio.available());
  if(radio.available()){
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
  }
}
