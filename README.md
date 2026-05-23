# BYU STEM Camp RC Car (ESP32-CAM)

A robust, low-cost, and zero-latency RC car software framework designed for educational STEM camps. This project turns a standard ESP32-CAM into a standalone web server, video streamer, and motor controller, all without requiring an external internet connection.

## Features

- **Zero-Latency Video:** Optimized firmware utilizing native QVGA resolution and an adjusted 10MHz clock speed for rock-solid MJPEG streaming over a local network.
- **WebSocket Nervous System:** Sub-millisecond response times for driving controls and camera tuning.
- **Frictionless Connectivity:** Auto-broadcasting, password-free Wi-Fi Access Points (e.g., `BYU-Car-1`). Students connect and drive instantly.
- **On-the-Fly Tuning:** A sleek, mobile-friendly web dashboard featuring a D-Pad and live sliders to control Headlight brightness, Camera Contrast, and Exposure.

## Hardware Requirements

- **Microcontroller:** ESP32-CAM (OV2640 or OV3660 sensor)
- **Motor Driver:** To be decided
- **Chassis:** To be decided
- **Power Supply:** To be decided

*Note: Do not power the motors directly from the ESP32!*

## Wiring Guide (Work in Progress)

The following is a reference wiring diagram for typical motor driver configurations. Specific hardware selections are still being finalized.

| ESP32-CAM Pin | Motor Driver Pin | Function |
| :--- | :--- | :--- |
| `GPIO 12` | `IN1` | Right Motor Forward |
| `GPIO 13` | `IN2` | Right Motor Reverse |
| `GPIO 14` | `IN3` | Left Motor Forward |
| `GPIO 15` | `IN4` | Left Motor Reverse |
| `5V` | `5V Out` | Power to ESP32 |
| `GND` | `GND` | Common Ground |

*Note: Ensure no MicroSD card is inserted, as the motors utilize the SD card data pins.*

## Setup & Installation

### 1. Configure the Car's Name

Open `CameraWebServer.ino` in the Arduino IDE. Locate this line near the top and change it to the physical car's designated name (e.g., `BYU-Car-2`):

```cpp
const char *carSSID = "BYU-Car-1";
```

### 2. Flash the Firmware

1. Connect your ESP32-CAM to your computer using the MB board or an FTDI programmer.
2. Select AI Thinker ESP32-CAM in the Arduino Board Manager.
3. Click Upload.

### 3. Drive!

1. Power on the car.
2. Open your smartphone or laptop Wi-Fi settings and connect to the car's open network (e.g., `BYU-Car-1`).
3. Open a web browser and navigate to: `http://192.168.4.1/`

## Architecture

This project was built to scale for classroom environments. By utilizing hardcoded unique SSIDs and isolating each car as its own Access Point, dozens of cars can be operated in the same room without IP routing conflicts.

## Credits

This project builds upon excellent educational resources from the community:

- [ESP32-CAM Streaming with Motor Control](https://www.youtube.com/watch?v=7I4SnUXxUR0&t=2s) by Jeevan Jee
- [Simple Circuits Tutorial](https://www.youtube.com/watch?v=Du1UvHnD-ZM) by Simple Circuits
- [ESP32-CAM Car Robot Web Server](https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/) by Random Nerd Tutorials
- [RoboArmy Project](https://youtu.be/YqQc_Sm9vlA) by RoboArmy

---

Developed for the BYU STEM Camp (2026).