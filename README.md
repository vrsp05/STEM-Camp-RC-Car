# BYU STEM Camp RC Car (ESP32-CAM)

A robust, low-cost, and zero-latency RC car software framework designed for educational STEM camps. This project turns a standard ESP32-CAM into a standalone web server, video streamer, and motor controller, all without requiring an external internet connection.

## Features

- **Zero-Latency Video:** Optimized firmware utilizing native QVGA resolution and an adjusted 10MHz clock speed for rock-solid MJPEG streaming over a local network.
- **WebSocket Nervous System:** Sub-millisecond response times for driving controls and camera tuning.
- **Frictionless Connectivity:** Auto-broadcasting, password-free Wi-Fi Access Points (e.g., `BYU-Car-1`). Students connect and drive instantly.
- **On-the-Fly Tuning:** A sleek, mobile-friendly web dashboard featuring a D-Pad and live sliders to control Headlight brightness, Camera Contrast, and Exposure.

## Hardware Requirements

- **Microcontroller:** ESP32-CAM with OV2640 sensor (recommended). OV3660 is compatible but may not perform as well.
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

### 1. Fork and Clone the Repository

1. **Fork the repository** by clicking the "Fork" button on GitHub (top-right corner).
   - This creates your own copy of the project, so you won't accidentally modify the original repository.

2. **Clone your forked repository** to your local machine:

```bash
git clone https://github.com/vrsp05/STEM-Camp-RC-Car.git
cd STEM-Camp-RC-Car
```

### 2. Set Up Arduino IDE

Configure your Arduino IDE to support the ESP32-CAM board and install the necessary libraries. Follow the detailed guide:

**[Complete Arduino IDE Setup Guide →](ARDUINO_IDE_ESP32_SETUP.md)**

This includes:
- Installing the latest ESP32 libraries by Espressif via Boards Manager
- Selecting the correct board (AI Thinker ESP32-CAM)
- Selecting the correct COM port
- Troubleshooting common issues

### 3. Connect Your ESP32-CAM to Your Computer

1. Connect your ESP32-CAM to your computer using the USB cable connected to the MB board or an FTDI programmer.
2. Open the Arduino IDE and ensure the correct COM port is selected (**Tools → Port**).

### 4. Configure the Car's Name

1. In the Arduino IDE, open the `CameraWebServer.ino` file from the `esp32_cam/CameraWebServer/` directory.
2. Locate this line near the top of the file and change it to your car's designated name (e.g., `BYU-Car-2`):

```cpp
const char *carSSID = "BYU-Car-1";
```

### 5. Flash the Firmware

1. In the Arduino IDE, click **Sketch → Upload** (or press `Ctrl+U` / `Cmd+U`).
2. Wait for the upload to complete. You should see "Done uploading" in the console.
3. Once complete, the MB board is no longer needed (you can disconnect it).

### 6. Drive!

1. Power on the car.
2. Open your smartphone or laptop Wi-Fi settings and connect to the car's open network (e.g., `BYU-Car-1`).
3. Open a web browser and navigate to: `http://192.168.4.1/`
4. Use the web dashboard to control the car and adjust camera settings.

## Architecture

This project was built to scale for classroom environments. By utilizing hardcoded unique SSIDs and isolating each car as its own Access Point, dozens of cars can be operated in the same room without IP routing conflicts.

## Credits

This project builds upon excellent educational resources from the community:

- [ESP32-CAM Streaming with Motor Control](https://www.youtube.com/watch?v=7I4SnUXxUR0&t=2s) by Jeevan Jee
- [Simple Circuits Tutorial](https://www.youtube.com/watch?v=Du1UvHnD-ZM) by Simple Circuits
- [ESP32-CAM Car Robot Web Server](https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/) by Random Nerd Tutorials
- [RoboArmy Project](https://youtu.be/YqQc_Sm9vlA) by RoboArmy

## About This Project

This is a demonstration project built by Victor Rafael Santana for the BYU STEM Camp (2026). It showcases how embedded systems and IoT technology can be integrated into a fun, interactive workshop experience. The goal is to provide students with hands-on experience building and controlling robot cars, while learning about microcontrollers, wireless networking, web servers, and real-time systems.

This project is proposed as a potential new workshop offering for the BYU STEM Camp to enhance the educational experience and inspire students interested in robotics and embedded systems.

---

Developed for the BYU STEM Camp (2026).