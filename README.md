# Gesture-Controlled Wireless Robot

A wireless robot control system that uses an **ADXL345 accelerometer** to detect hand movements and an **nRF24L01 RF transceiver** to transmit the motion data to a receiver. The receiver processes the X- and Y-axis acceleration values and controls a motor driver to move the robot.

## Features

* Gesture-based wireless robot control
* ADXL345 accelerometer for motion sensing
* nRF24L01 for wireless communication
* Dual DC motor control
* PWM-based motor speed control
* Four-direction movement:

  * Forward
  * Backward
  * Left
  * Right
* Automatic stop when the detected movement is within the defined threshold

## System Architecture

```text
        TRANSMITTER
┌─────────────────────┐
│      ADXL345        │
│   Accelerometer     │
└─────────┬───────────┘
          │ I2C
          ▼
┌─────────────────────┐
│    Microcontroller  │
│  Read X/Y Accel.    │
└─────────┬───────────┘
          │
          │ nRF24L01
          │ Wireless
          ▼
┌─────────────────────┐
│    Microcontroller  │
│      Receiver       │
└─────────┬───────────┘
          │
          ▼
┌─────────────────────┐
│    Motor Driver     │
└─────────┬───────────┘
          │
     ┌────┴────┐
     ▼         ▼
  Motor 1    Motor 2
```

## Hardware Components

* ADXL345 accelerometer
* nRF24L01 wireless transceiver modules
* Arduino-compatible microcontroller boards
* DC motors
* Dual-channel motor driver
* Robot chassis
* Power supply
* Connecting wires

## Software Requirements

* Arduino IDE
* SPI library
* Wire library
* RF24 library

## Repository Structure

```text
Gesture-Controlled-Wireless-Robot/
│
├── README.md
├── LICENSE
│
├── src/
│   ├── transmitter/
│   │   └── transmitter.ino
│   │
│   └── receiver/
│       └── receiver.ino
│
└── docs/
    ├── block_diagram.png
    ├── circuit_diagram.png
    └── demo.jpg
```

## Transmitter

The transmitter reads acceleration data from the ADXL345 over I2C.

The X- and Y-axis values are stored in a structure:

```cpp
struct data {
  float xAxis;
  float yAxis;
};
```

The structure is transmitted wirelessly using the nRF24L01 module.

The transmitter uses:

```text
ADXL345 I2C Address: 0x53
nRF24 Address: 00001
```

## Receiver

The receiver continuously checks for incoming wireless data.

The received X- and Y-axis acceleration values are compared against predefined thresholds to determine the required robot movement.

### Motion Mapping

| Sensor Condition | Robot Movement |
| ---------------- | -------------- |
| `Y > 0.3`        | Right          |
| `Y < -0.3`       | Left           |
| `X > 0.5`        | Backward       |
| `X < -0.5`       | Forward        |
| Otherwise        | Stop           |

The receiver controls motor speed using PWM through the ENA and ENB pins.

## Pin Configuration

### Transmitter

| Component | Pin |
| --------- | --- |
| nRF24 CE  | D7  |
| nRF24 CSN | D8  |
| ADXL345   | I2C |

### Receiver

| Motor Driver Signal | Arduino Pin |
| ------------------- | ----------: |
| ENA                 |          D3 |
| ENB                 |         D10 |
| IN1                 |          D2 |
| IN2                 |          D4 |
| IN3                 |          D5 |
| IN4                 |          D6 |
| nRF24 CE            |          D7 |
| nRF24 CSN           |          D8 |

## How It Works

1. The ADXL345 measures acceleration along the X and Y axes.
2. The transmitter reads the sensor values through I2C.
3. The X and Y values are packed into a data structure.
4. The nRF24L01 transmits the data wirelessly.
5. The receiver receives the data.
6. The receiver compares the sensor values with predefined thresholds.
7. According to the detected gesture, the motor driver controls the two DC motors.
8. When no gesture crosses the threshold, the robot stops.

## Getting Started

### 1. Install Required Library

Install the **RF24** library through the Arduino IDE Library Manager.

### 2. Upload Transmitter Code

Open:

```text
src/transmitter/transmitter.ino
```

Connect the ADXL345 and nRF24L01 to the transmitter board and upload the code.

### 3. Upload Receiver Code

Open:

```text
src/receiver/receiver.ino
```

Connect the nRF24L01 and motor driver to the receiver board and upload the code.

### 4. Test the Robot

Open the Serial Monitor at:

```text
9600 baud
```

Move the accelerometer and observe the transmitted/received X and Y values.

## Communication

The transmitter and receiver use the same nRF24L01 communication address:

```cpp
const byte address[6] = "00001";
```

The transmitted payload contains two floating-point values:

```text
X-axis acceleration
Y-axis acceleration
```

## Future Improvements

* Add communication-loss safety timeout
* Add sensor calibration
* Add configurable gesture thresholds
* Improve motor speed control
* Add battery monitoring
* Add obstacle detection
* Improve error handling for wireless communication

## Author

**Vinit K. Gupta**

Electronics and Communication Engineering

---

## License

This project is intended for educational and development purposes. Add an appropriate open-source license before distributing the project publicly.
