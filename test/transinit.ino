#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
#include<printf.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  radio.begin();
  Serial.println(radio.begin());
  radio.stopListening();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  // radio.setCRCLength(RF24_CRC_8);
  printf_begin();
  radio.printDetails();
}

void loop() {
  // put your main code here, to run repeatedly:
  const char text[] = "EMR WORKSHOP";
  radio.write(&text,sizeof(text));
  delay(100);
  Serial.println("Transmitting");
}
