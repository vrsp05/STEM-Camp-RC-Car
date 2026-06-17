# BYU STEM Camp RC Car (ESP32-CAM)

A robust, low-cost, and low-latency RC car software framework designed for educational STEM camps. This project turns a standard ESP32-CAM into a standalone web server, video streamer, and motor controller, all without requiring an external internet connection.

## Features

- **Low-Latency Video:** Optimized firmware utilizing CIF (400x296) resolution and an adjusted 10MHz clock speed for rock-solid MJPEG streaming over a local network.
- **WebSocket Nervous System:** Sub-millisecond response times for driving controls and camera tuning.
- **Frictionless Connectivity:** Auto-broadcasting, password-free Wi-Fi Access Points (e.g., `BYU-Car-1`). Students connect and drive instantly.
- **On-the-Fly Tuning:** A sleek, mobile-friendly web dashboard featuring a D-Pad and live sliders to control Headlight brightness, Camera Contrast, and Exposure.

## Hardware Requirements

- **Microcontroller:** ESP32-CAM with OV2640 sensor (recommended). OV3660 is compatible but may not perform as well. [[Link](https://www.aliexpress.us/item/3256806346200289.html?src=google&snps=y&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en3256806346200289&ds_e_product_merchant_id=5352158365&ds_e_product_country=US&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=20542171667&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=18545443176&gbraid=0AAAAAD6I-hHSnJe8F4dPsfukiDXsjnCPU&gclid=CjwKCAjwuanRBhBSEiwAY5y6V101Z4Zg7qYjB7jEohQEXXXkJtaJuUl7Fb8nahwqdjlZUxWY4VXrlRoCbLwQAvD_BwE&gatewayAdapt=glo2usa)]
- **Motors:** Four TT DC gearbox motors with retractable design for easy suitcase storage. [[Link](https://www.aliexpress.us/item/3256809725271346.html?src=google&snps=y&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en3256809725271346&ds_e_product_merchant_id=5640842084&ds_e_product_country=US&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=20542171667&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=18545443176&gbraid=0AAAAAD6I-hHSnJe8F4dPsfukiDXsjnCPU&gclid=CjwKCAjwuanRBhBSEiwAY5y6V23h5dibXUOXUa0smJ8FFr1nYl_yUjkY2SpRhDMMLlLAYPJRrs-16hoCsjcQAvD_BwE&gatewayAdapt=glo2usa)]
- **Wheels:** Four compatible TT motor rubber wheels. [[Link](https://www.aliexpress.us/item/3256809725271346.html?src=google&snps=y&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en3256809725271346&ds_e_product_merchant_id=5640842084&ds_e_product_country=US&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=20542171667&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=18545443176&gbraid=0AAAAAD6I-hHSnJe8F4dPsfukiDXsjnCPU&gclid=CjwKCAjwuanRBhBSEiwAY5y6V23h5dibXUOXUa0smJ8FFr1nYl_yUjkY2SpRhDMMLlLAYPJRrs-16hoCsjcQAvD_BwE&gatewayAdapt=glo2usa)]
- **Motor Driver:** DRV8833. [[Link](https://www.aliexpress.us/item/3256808512860623.html?src=google&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en3256808512860623&ds_e_product_merchant_id=5560538802&ds_e_product_country=US&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=19558607238&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=19566915268&gbraid=0AAAAAD6I-hHcVpRLmtsNOLYqdC36jl_6Q&gclid=CjwKCAjwuanRBhBSEiwAY5y6VxsEeO_oh6zBLbQ3QillTrRul9A80BLu5ZrUFSNyDJvnp-FDlmZOYBoCc3YQAvD_BwE&gatewayAdapt=glo2usa)]
- **Chassis:** Custom PCB. [[Link]()]
- **Power Supply:** 4 AA battery pack [[Link](https://www.aliexpress.us/item/2255799895517935.html?src=google&snps=y&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en2255799895517935&ds_e_product_merchant_id=109204739&ds_e_product_country=US&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=20542171667&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=18545443176&gbraid=0AAAAAD6I-hHSnJe8F4dPsfukiDXsjnCPU&gclid=CjwKCAjwuanRBhBSEiwAY5y6V6zV6XEK94hojw_-oD1P6xNap2T9IkF80AHEtQx7qn7wH8S5d1uNaBoC5PEQAvD_BwE&gatewayAdapt=glo2usa)]. *(Note: You will need to provide 4 of your own good quality AA batteries).*
- **Power Switch:** SLW-1276864-4A-D switch for car control. [[Link](https://www.digikey.com/en/products/detail/same-sky-formerly-cui-devices-/SLW-1276864-4A-D/21259972?gclsrc=aw.ds&gad_source=1&gad_campaignid=20243136172&gbraid=0AAAAADrbLlj1fOpVS-J9OCclJDTSNeTLj&gclid=CjwKCAjwuanRBhBSEiwAY5y6V0a4BwxcfrwDMveePxhBp6Lb_C-T54p6c8k-7GsEpx2MxBAeGH0KEhoCDD4QAvD_BwE)]

*Note: Do not power the motors directly from the ESP32!*

## Wiring Guide (Custom PCB Reference)

The following is the internal wiring reference for the Custom PCB, connecting the ESP32-CAM to the onboard DRV8833 motor driver. 

| ESP32-CAM Pin | DRV8833 Pin | Function |
| :--- | :--- | :--- |
| `GPIO 13` | `IN1` | Right Motors (M3 & M4) PWM |
| `GPIO 12` | `IN2` | Right Motors (M3 & M4) PWM |
| `GPIO 15` | `IN3` | Left Motors (M1 & M2) PWM |
| `GPIO 14` | `IN4` | Left Motors (M1 & M2) PWM |
| `5V` | `VCC` | Power to ESP32 |
| `GND` | `GND` | Common Ground |

*Note: Ensure no MicroSD card is inserted, as the motors utilize the SD card data pins. The left motor logic (Pins 14 & 15) is intentionally inverted in the software to account for the physical motor orientation.*

### Crucial Assembly Warning: The "Mirror Effect"

When assembling the chassis, be aware that the front and back motors on each side (e.g., M1 and M2) share the exact same electrical channel on the custom PCB. They will always receive the exact same "forward" or "backward" signal from the code. 

However, because the back motors are physically mounted facing the opposite direction of the front motors on standard TT chassis kits, sending a "forward" signal will cause the back wheels to mechanically spin backward. The car will fight itself and refuse to drive.

**To fix this, you must do ONE of the following to the two BACK motors (M2 and M4) before testing:**
* **Option A (Recommended):** Unclip the back motors from the plastic chassis, physically flip them upside down (180 degrees), and clip them back in. This reverses their mechanical rotation to match the front wheels.
* **Option B (If motors cannot be removed):** Desolder and swap the two wires directly at the copper tabs on the motor casing itself. This reverses their electrical polarity to bypass the PCB's parallel wiring.

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
4. Upon successful boot, the onboard LED will flash three times to indicate the board was successfully flashed.

> ** Crucial Flashing Warning: ** > You MUST completely remove the ESP32-CAM from the custom car PCB before flashing. If you attempt to flash the code while the ESP32 is plugged into the car, the copper traces on the PCB will act as antennas, pick up electrical noise, and cause a `Packet content transfer stopped` fatal error. 
> 
> *Tip: Ensure your Arduino IDE upload speed is set to `115200` for the most stable data transfer.*
### 6. Drive!

1. Power on the car.
2. Open your smartphone or laptop Wi-Fi settings and connect to the car's open network (e.g., `BYU-Car-1`).
3. Open a web browser and navigate to: `http://192.168.4.1/`
4. Use the web dashboard to control the car and adjust camera settings.

## Architecture

This project was built to scale for classroom environments. By utilizing hardcoded unique SSIDs and isolating each car as its own Access Point, dozens of cars can be operated in the same room without IP routing conflicts.

## Credits

**Hardware & Custom PCB Design:**
- **Dan Barry** and **Jaime Mejia** for engineering the custom PCB and assembling the physical hardware of the car.

**Software & Inspiration:**
This project builds upon excellent educational resources from the community:
- [ESP32-CAM Streaming with Motor Control](https://www.youtube.com/watch?v=7I4SnUXxUR0&t=2s) by Jeevan Jee
- [Simple Circuits Tutorial](https://www.youtube.com/watch?v=Du1UvHnD-ZM) by Simple Circuits
- [ESP32-CAM Car Robot Web Server](https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/) by Random Nerd Tutorials
- [RoboArmy Project](https://youtu.be/YqQc_Sm9vlA) by RoboArmy

## About This Project

This is a demonstration project built by Victor Santana, Jaime Mejia, and Dan Barry for the BYU STEM Camp (2026). It showcases how embedded systems and IoT technology can be integrated into a fun, interactive workshop experience. The goal is to provide students with hands-on experience building and controlling robot cars, while learning about microcontrollers, wireless networking, web servers, and real-time systems.

This project is proposed as a potential new workshop offering for the BYU STEM Camp to enhance the educational experience and inspire students interested in robotics and embedded systems.

---

Developed for the BYU STEM Camp (2026).