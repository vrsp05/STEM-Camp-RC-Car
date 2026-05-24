# Engineering & Development Log
## BYU STEM Camp RC Car Project (Spring 2026)

**Project Lead:** Victor Santana  
**Advising:** Dr. Lloyd  

This document serves as the official engineering log for the ESP32-CAM RC Car framework. It details the hardware quirks, software pivots, and scale considerations encountered during the prototype phase. It should be used as a reference guide for future iterations and bulk hardware ordering.

---

### 1. Network Architecture & The "Setup Page" Pivot

**Initial Approach:**
The original software design featured a dynamic "Setup Webpage" and a "Traffic Cop" redirect system. Students would connect to a default factory network, hit a captive portal, and set a custom SSID and password that was saved to the ESP32's non-volatile memory (EEPROM/Preferences).

**The Pivot:**
After reviewing hardware constraints with Dr. Lloyd, the complex setup flow was completely removed in favor of **hardcoded, open networks**. 

**Reasons for the Pivot:**
* **No Physical Reset Button:** The final car design eliminates the ESP32-CAM-MB (the sub-board with the USB port and buttons) to save cost and weight. Without a physical "BOOT/RST" button, a student who forgot their custom password would be permanently locked out of their car. 
* **Frictionless UX:** Hardcoding the SSIDs (`BYU-Car-1`, `BYU-Car-2`) directly in the Arduino IDE before flashing guarantees that students can simply power on the car, connect without a password, and drive.

**Addressing the IP Address Concern:**
A major concern was raised regarding all 10 cars using the exact same default IP address (`http://192.168.4.1/`). Testing confirmed this **does not** cause network conflicts. Because each ESP32 broadcasts its own independent Wi-Fi Access Point (SoftAP mode), it creates a physically isolated network bubble. Multiple phones can connect to `192.168.4.1` simultaneously because they are routing to entirely different hardware routers.

---

### 2. Wi-Fi Stability and Scaling Constraints

**Testing Observations:**
The native internal PCB antenna on the ESP32-CAM is adequate for line-of-sight operation in a standard room. However, walls and physical obstructions degrade the video stream rapidly. Furthermore, running multiple MJPEG video streams simultaneously in the same room slightly degrades overall network performance due to 2.4GHz spectrum noise.

**Future Scaling Recommendations (100+ Cars):**
While the internal antenna is sufficient for the 10-car prototype beta, scaling this to hundreds of students in a gymnasium will saturate the 2.4GHz Wi-Fi channels. For the final camp:
1. **External Antennas:** Bulk orders must include ESP32-CAM modules with U.FL connectors and external wire antennas.
2. **Channel Management:** The firmware will need to be updated to manually assign different Wi-Fi channels (1, 6, 11) across the fleet to distribute the radio frequency load.

---

### 3. Firmware Stability Tuning

**The Issue:**
During testing, some ESP32-CAM modules exhibited severe latency, lagging, and spontaneous crashing when attempting to stream video.

**The Fix:**
The `camera_config_t` initialization sequence was heavily optimized to prevent overheating and buffer overflows. 
* **Clock Speed:** The XCLK was throttled from 20MHz down to `10MHz`.
* **Native Resolution:** The camera was forced to boot natively in `FRAMESIZE_QVGA` (320x240) rather than booting in UXGA and downsizing later.
* **JPEG Compression:** Quality was increased (value set to `15`) to reduce packet size and speed up transmission. 

---

### 4. The Camera Sensor Dilemma: OV2640 vs. OV3660

**The Issue:**
Testing revealed a massive discrepancy in video quality depending on the USB board type used.
* **MicroUSB Boards (OV2640 Sensor):** Output perfect, accurate daylight colors.
* **USB-C Boards (OV3660 Sensor):** Output blown-out exposures with a severe pink/purple tint across foliage and reflective surfaces.

**Engineering Triage:**
Initial hypothesis pointed to the OV3660 being a "Night Vision" variant lacking a physical IR-cut filter. Upon physical inspection, an IR-reflective coating was visible on the lens, pointing to a software mismatch. We attempted to implement deep Digital Signal Processor (DSP) calibrations:
* Forced "Sunny" White Balance Mode (`s->set_wb_mode(s, 1)`)
* Enabled Lens Correction (`s->set_lenc(s, 1)`)
* Enabled Raw Gamma Correction (`s->set_raw_gma(s, 1)`)

**Final Conclusion:**
While the DSP calibration successfully fixed the overexposure (brightness) issue, the pink tint remained. A physical lens swap between the two boards conclusively proved that the OV3660 lens batch utilized an extremely weak or defective IR-cut filter. 

**Mandatory Hardware Requirement:**
For all future bulk orders, we must explicitly verify with the supplier that the boards ship with **OV2640 Daylight Sensors**. Relying on mixed batches will result in a poor visual experience for the students.
