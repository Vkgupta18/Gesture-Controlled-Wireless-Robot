#include <SPI.h>

#define CS_PIN 10   // Chip Select pin for ADXL345

float X_out, Y_out, Z_out;

void writeRegister(byte reg, byte value) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(reg);
  SPI.transfer(value);
  digitalWrite(CS_PIN, HIGH);
}

byte readRegister(byte reg) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x80 | reg);  // read flag
  byte value = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  return value;
}

void readMultipleRegisters(byte reg, byte count, byte* dest) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0xC0 | reg);  // read flag + multibyte flag
  for (byte i = 0; i < count; i++) {
    dest[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS_PIN, HIGH);
}

void gyro_setup() {
  SPI.begin();
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  // Put ADXL345 into measurement mode
  writeRegister(0x2D, 0x08); // POWER_CTL: Measure mode
}

void reading_gyro_data() {
  byte buffer[6];
  readMultipleRegisters(0x32, 6, buffer);

  // Combine bytes into integers
  int16_t x = (int16_t)(buffer[1] << 8 | buffer[0]);
  int16_t y = (int16_t)(buffer[3] << 8 | buffer[2]);
  int16_t z = (int16_t)(buffer[5] << 8 | buffer[4]);

  // Convert to g (for ±2g range)
  X_out = x / 256.0;
  Y_out = y / 256.0;
  Z_out = z / 256.0;

  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print(" Ya= ");
  Serial.print(Y_out);
  Serial.print(" Za= ");
  Serial.println(Z_out);

  delay(500);
}

void setup() {
  Serial.begin(9600);
  gyro_setup();
}

void loop() {
  reading_gyro_data();
}
