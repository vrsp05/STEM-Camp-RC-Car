# BYU STEM Camp RC Car

## About This Project

Built by Victor Santana, Jaime Mejia, and Dan Barry as a proposed 2026 workshop for the BYU STEM Camp, this project delivers a robust, low-cost, and low-latency RC car framework. It transforms a standard ESP32-CAM into a standalone web server, video streamer, and motor controller, all without requiring an external internet connection. This interactive experience is designed to inspire students and provide hands-on learning in embedded systems, IoT technology, microcontrollers, and real-time wireless networking.

## Features

* **Low-Latency Video:** Optimized firmware utilizing CIF (400x296) resolution and an adjusted 10MHz clock speed for good MJPEG streaming over a local network.
* **WebSocket System:** Fast response times for driving controls and camera tuning, ensuring the car reacts to your steering instantly.
* **Frictionless Connectivity:** Auto-broadcasting, password-free Wi-Fi Access Points (e.g., `BYU-Car-1`). Students connect and drive instantly.
* **On-the-Fly Tuning:** A sleek, mobile-friendly web dashboard featuring a D-Pad and live sliders to control Headlight brightness, Camera Contrast, and Exposure.

## The Map (How is it organized?)

To make building your car as easy as possible, we separated all the files into four specific folders:

```text
STEM-CAMP-RC-CAR/
├── docs/             
├── firmware/         
├── hardware/         
└── web_interface/
```

- **docs/** (The Instruction Manuals): This is the library. It holds all the step-by-step guides that show you exactly how to snap the car together and set up the computer.
- **firmware/** (The Car's Brain): This is where the code lives. When we upload this folder to the microcontroller, it teaches the car how to drive, how to connect to Wi-Fi, and how to stream the video camera.
- **hardware/** (The Physical Parts): This is the toolbox. It holds the 3D-printer files needed to make the plastic car body, the printed circuit board (PCB), and the wiring diagrams that show where all the electronics plug in.
- **web_interface/** (The Remote Control): This is the steering wheel. It holds the files that will pop up on a phone screen so you can actually see the video and drive the car.

## The Shopping List (Hardware Requirements)

To build this car, you will need a mix of custom parts and standard robotics electronics. Here is the detailed breakdown:

| Component | Quantity | Purchase Link |
| :--- | :--- | :--- |
| **ESP32-CAM (OV2640 camera)** | 1 | [DigiKey](https://www.digikey.com/short/w14d0qp4) |
| **DRV8833 Motor Controller** | 1 | [Amazon](https://a.co/d/00hcKW4g) |
| **8-Pin Female-to-Male Headers** | 2 | [DigiKey](https://www.digikey.com/short/5r3mm5rb) |
| **6-Pin Male-to-Male Headers** | 1 | [DigiKey](https://www.digikey.com/short/bth0dmv4) |
| **TT DC Gearbox Motors** | 4 | [Amazon](https://a.co/d/0djxPo1a) |
| **Rubber Wheels (for TT Motors)** | 4 | [Amazon](https://a.co/d/0djxPo1a) |
| **T-Brackets** | 4 | [/3d_prints/](hardware/3d_prints/T-Bracket_Mount.stl) |
| **Camera Mount** | 1 | [/3d_prints/](hardware/3d_prints/Camera_Mount.stl) |
| **Headlight Mount** | 1 | [/3d_prints/](https://github.com/vrsp05/STEM-Camp-RC-Car/tree/main/hardware/3d_prints) |
| **6-32 x 1/4" Mounting Screws** | 8 | [Amazon](https://a.co/d/0h44JuEw) |
| **Custom PCB Chassis** | 1 | [/electronics/](https://github.com/vrsp05/STEM-Camp-RC-Car/tree/main/hardware/electronics) |
| **4-AA Battery Holder** | 1 | [DigiKey](https://www.digikey.com/short/vzvpw4tr) |
| **Power Switch (SLW-1276864-4A-D)** | 1 | [DigiKey](https://www.digikey.com/short/3592nqjh) |
| **AA Batteries** | 4 | [Amazon](https://www.digikey.com/short/3592nqjh) |
| **Zip Tie** | 1 | [Amazon](https://www.digikey.com/short/3592nqjh) |
| **Small Foam / Cardboard Rectangle** | 1 | [Amazon](https://a.co/d/09obGXU5) |

**Total estimated price:** $[Insert Total Here]

## The Instructions (How do I build it?)

To build, program, and drive your car, you just need to download this repository and follow the step-by-step guides. You do not need to figure out how to build it from scratch, everything is already mapped out for you:

**Step 1: Download the Files (Fork and Clone)**

Before doing anything, you need to save a copy of all these project files to your own computer.

   * Click the **Fork** button at the top right of this GitHub page. This creates a safe copy in your own account so you can make changes without breaking the original project.
   * Open your computer's terminal and clone your new copy by typing:
      ```bash
      git clone https://github.com/vrsp05/STEM-Camp-RC-Car.git

      cd STEM-Camp-RC-Car
      ```

**Step 2: Set Up Your Computer**

   * **File:** [environment_setup.md](docs/environment_setup.md)
   * **What it does:** This guide shows you exactly how to install the Arduino IDE on your computer, add the ESP32 chip definitions, and make sure your computer can talk to the car's brain over a USB cable.

**Step 3: Assemble the Hardware**

   * **File:** [assembly_guide.pdf](docs/assembly_guide.pdf)
   * **What it does:** This is your physical instruction manual. It has clear pictures and step-by-step directions showing you how to solder the electronics to the custom PCB chassis, mount the four yellow gearbox motors using your screws, and attach the wheels.

**Step 4: Program the Brain**

   * **File:** [programming_guide.md](docs/programming_guide.md)
   * **What it does:** This guide teaches you how to open the code, give your car a unique Wi-Fi network name, and safely flash the firmware onto the ESP32-CAM using the correct settings so it is ready to drive.

## Troubleshooting & Pro-Tips

**1. The "Hidden" Upload Speed**
If the Arduino IDE hides the "Upload Speed" option when you select the AI Thinker board, you can outsmart it! Change your board to **ESP32 Dev Module**. This generic profile unlocks the hidden menu. Set your Upload Speed to **115200**, change **PSRAM** to **Enabled**, and hit upload. This prevents the high-speed crashing issue.

**2. The Antenna Effect (Flashing Crash)**
If your upload crashes with an `exit status 2` error, your car's body is causing interference. You must completely remove the ESP32-CAM from the custom car PCB before flashing. If it is plugged in, the copper lines on the board act like antennas and scramble the data transfer. 

**3. Motor Speeds**
Not all yellow TT motors are created equal! If one of your cars is much faster than the others, check the motor colors. Dull yellow motors typically have a **1:48 gear ratio** (built for high speed). Brighter yellow motors often have a **1:120 gear ratio** (built for heavy pushing power). Always try to match the motor gear rations when building a car so it drives straight!

**4. The Missing COM Port**
If you connect your board but do not see a COM port listed, you are likely using a "charge-only" USB cable. Swap it out for a cable that supports data transfer to fix the issue.

**5. The "Upload Fails" Timeout**
If your upload hangs or fails to connect, ensure you have the "AI Thinker ESP32-CAM" selected as your board. If it still fails, you can physically force the connection by pressing and holding the **I0O** button on your programmer board while the code is uploading.

**6. Camera Not Working (Blank Screen)**
If the dashboard loads but you have no video, first verify that the tiny OV2640 camera ribbon is snapped completely into its connector. Second, ensure there is absolutely no MicroSD card inserted into the board.

**7. Video Freezing or Losing Control**
If the video feed suddenly stops or the car stops responding to your controls, you have likely driven out of the ESP32's Wi-Fi range. Walk closer to the car, turn your device's Wi-Fi off and back on to reconnect, and refresh the web page.

## Credits

**Hardware & Custom PCB Design:**
- **Dan Barry** and **Jaime Mejia** for engineering the custom PCB and assembling the physical hardware of the car.

**Software & Inspiration:**
This project builds upon excellent educational resources from the community:
- [ESP32-CAM Streaming with Motor Control](https://www.youtube.com/watch?v=7I4SnUXxUR0&t=2s) by Jeevan Jee
- [Simple Circuits Tutorial](https://www.youtube.com/watch?v=Du1UvHnD-ZM) by Simple Circuits
- [ESP32-CAM Car Robot Web Server](https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/) by Random Nerd Tutorials
- [RoboArmy Project](https://youtu.be/YqQc_Sm9vlA) by RoboArmy

---

Developed for the BYU STEM Camp (2026).