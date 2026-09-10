#include <Wire.h>

#define ADXL345 0x53  // address of our ADXL345 module
float X_out, Y_out, Z_out;

void gyro_setup() {
  // Serial.println("hellol ");
  Wire.begin();  // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345);  // Start communicating with the
  // Serial.println("hellol 1");
  Wire.write(0x2D);  // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  // Serial.println("hellol 2 ");
  Wire.write(8);  // (8dec -> 0000 1000 binary) Bit D3 High for meas
 
 int status = Wire.endTransmission();
 Serial.println(status);
    // Serial.println("hellol before delay");
  delay(10);
  // Serial.println("hellol gyro end");
}

void reading_gyro_data() {

  //=== Reading acceleromter data === //
  // Serial.println("hellolol ");
  Wire.beginTransmission(0x53);
  Wire.write(0x32);  // Start with register 0x32 (ACCEL_XO
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);  // Read 6 registers
  X_out = (Wire.read() | Wire.read() << 8);  // X-axis value
  X_out = X_out / 256;  //For a range of +-2g, we need to divi
  Y_out = (Wire.read()| Wire.read() << 8);  // Y-axis value
  Y_out = Y_out / 256;
  Z_out = (Wire.read() | Wire.read() << 8);  // Z-axis value
  Z_out = Z_out / 256;
  
  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print(" Ya= ");
  Serial.print(Y_out);
  Serial.print(" Za= ");
  Serial.println(Z_out);
  delay(500);
// Serial.println("hellol end ");
}

void setup() {

  Serial.begin(9600);  // Initiate serial communication for printi
  gyro_setup();

}

void loop() {

  reading_gyro_data();
}

