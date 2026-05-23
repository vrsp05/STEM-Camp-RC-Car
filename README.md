# BYU STEM Camp RC Car (ESP32-CAM)

A robust, low-cost, and zero-latency RC car software framework designed for educational STEM camps. This project turns a standard ESP32-CAM into a standalone web server, video streamer, and motor controller—all without requiring an external internet connection.

## Features
* **Zero-Latency Video:** Optimized firmware utilizing native QVGA resolution and an adjusted 10MHz clock speed for rock-solid MJPEG streaming over a local network.
* **WebSocket Nervous System:** Sub-millisecond response times for driving controls and camera tuning.
* **Frictionless Connectivity:** Auto-broadcasting, password-free Wi-Fi Access Points (e.g., `BYU-Car-1`). Students connect and drive instantly.
* **On-the-Fly Tuning:** A sleek, mobile-friendly web dashboard featuring a D-Pad and live sliders to control Headlight brightness, Camera Contrast, and Exposure.

## Hardware Requirements
* **Microcontroller:** ESP32-CAM (OV2640 or OV3660 sensor)
* **Motor Driver:** Not yet decided.
* **Chassis:** Not yet decided
* **Power:** Not yet decided. 
*(Do not power the motors directly from the ESP32!)*

## ⚡ Wiring Guide

| ESP32-CAM Pin | Motor Driver Pin | Function |
| :--- | :--- | :--- |
| `GPIO 12` | `IN1` | Right Motor Forward |
| `GPIO 13` | `IN2` | Right Motor Reverse |
| `GPIO 14` | `IN3` | Left Motor Forward |
| `GPIO 15` | `IN4` | Left Motor Reverse |
| `5V` | `5V Out` | Power to ESP32 |
| `GND` | `GND` | Common Ground |

*(Note: Ensure no MicroSD card is inserted, as the motors utilize the SD card data pins).*

## Setup & Installation

**1. Configure the Car's Name**
Open `CameraWebServer.ino` in the Arduino IDE. Locate this line near the top and change it to the physical car's designated name (e.g., `BYU-Car-2`):
```cpp
const char *carSSID = "BYU-Car-1";