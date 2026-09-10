#include "SPI.h"
#include "RF24.h"
#include "nRF24L01.h"

#define CE_PIN 7
#define CSN_PIN 8

RF24 receiver (CE_PIN, CSN_PIN);

// motor driver part
int ENA = 3;
int ENB = 10;
int IN1 = 2;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;

const byte address [6] = "00001";

//NRF24L01 buffer limit is 32 bytes (max struct size)
struct payload {
  float xAxis;
  float yAxis;
};

payload payload;

void motor_driver_setup() {
  pinMode(ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
}

void receiver_setup() {
  receiver.begin();
  
  //Setting Power amplifier level to minimum receiver.setPALevel (RF24_PA_MIN);
  //Default value is the maximum 32 bytes1
  receiver.setPayloadSize (sizeof(payload));
  //Act as receiver
  receiver.openReadingPipe (0, address);
  receiver.startListening();
}

void setup(){
  Serial.begin(9600);

  motor_driver_setup();

  receiver_setup();
}

void loop()
{
  if (receiver.available() > 0) {
    // reading data received from transmitter
    receiver.read(&payload, sizeof(payload));
    float X = payload.xAxis;
    float Y = payload.yAxis;

    Serial.println("Received");
    Serial.print("X value:");
    Serial.println(X);
    Serial.print("Y value:");
    Serial.println(Y);

    if(Y > 0.3)
    {
      // right();
      analogWrite(ENA, 130);
      analogWrite(ENB, 130);
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
    }
    else if(Y < -0.3)
    {
      // left();
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
    }
    else if(X > 0.5)
    {
      // back();
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
    }
    else if(X < -0.5)
    { 
      // forward();
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
    }
    else
    {
      // stop();
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
    }
  }
  // delay(500);
}