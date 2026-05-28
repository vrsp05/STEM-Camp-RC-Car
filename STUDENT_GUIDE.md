# BYU STEM Camp Smart RC Car: Student Guide

Welcome to your RC Car project. The core of your vehicle is the ESP32-CAM, a small microcontroller that acts as both the car's brain and a standalone Wi-Fi router. 

When powered on, the ESP32-CAM broadcasts its own private Wi-Fi network. By connecting your phone or computer directly to this network, you communicate with a web server hosted entirely on the microchip. This direct connection allows you to view a live video feed and control the motors with zero latency, without needing an external internet connection.

## Step-by-Step Setup

### 1. Name Your Car

After you finish physically building your car, take it to a lab assistant. They will help you select a unique network name for your vehicle (like "BYU-Car-1" or "Victor-Car") and program it into the `CameraWebServer.ino` file using the Arduino IDE.

### 2. Flash the Firmware

The lab assistant will then connect your ESP32-CAM to a computer and click "Upload" in the Arduino IDE to flash your customized code onto the microcontroller. Once this is done, your car's brain is ready.

### 3. Power On and Connect

Disconnect the car from the computer and power it using the onboard battery pack (3 AAA batteries). Flip the power switch to the ON position. Open the Wi-Fi settings on your smartphone or computer, look for your custom network name, and connect to it. It is an open network, so no password is required.

### 4. Launch the Dashboard

Open a standard web browser (like Chrome or Safari). Type the following IP address into the URL bar and press enter:

```
http://192.168.4.1/
```

## Using the Web Interface

Once the dashboard loads, you will have full control over the car's hardware. Here is what each section of the interface does:

- **Live Video Feed:** The screen at the top displays the real-time camera stream.
- **Directional Pad (D-Pad):** These are your driving controls. Press the top, bottom, left, and right arrows to move the car. The square button in the center acts as the brake to stop the motors.
- **Headlights Slider:** This controls the physical LED flash on the front of the ESP32-CAM. Sliding it to the right increases the brightness so you can navigate in dark environments.
- **Brightness Slider:** This is a software control that adjusts the camera sensor's exposure. If your video feed is too dark or washed out by the sun, adjust this slider to let more or less digital light into the lens.
- **Contrast Slider:** This modifies the difference between the light and dark areas of the video feed. Increasing the contrast can help make edges and obstacles look sharper and more defined on your screen.

## Troubleshooting Your Connection

If the live video freezes or you lose control of the car, you have likely driven out of Wi-Fi range. Try these steps to fix it:

1. **Get Closer:** Walk back toward the car so your phone is within a clear line of sight, and refresh the web page.
2. **Restart the Wi-Fi:** Turn the Wi-Fi off and then back on in your phone or computer settings, then reconnect to your car's network.
3. **Restart the Car:** Turn the car's power off, wait a few seconds, and turn it back on. Reconnect your phone to the network and reload the dashboard.

## Keep Hacking at Home

The best part of engineering is breaking things and making them your own. If you want to see exactly how this code works or start modifying the dashboard and motor controls yourself, you can find the complete source code online.

Go to [https://github.com/vrsp05/STEM-Camp-RC-Car.git](https://github.com/vrsp05/STEM-Camp-RC-Car.git) to view the project. Be sure to Fork the repository to your own account so you can start making your own changes and improvements!

## Packaging and Storage

When you're done testing and need to pack up your car for storage or transport (especially in a suitcase), follow these steps:

1. **Retract the Motors:** Use the retractable motor mechanism to fold the motors into the chassis for compact storage.
2. **Remove the Wheels:** Detach the wheels from the motor shafts to prevent damage during transport.
3. **Pack Carefully:** Once the motors are retracted and wheels are removed, your car should fit easily in a suitcase or storage container.
