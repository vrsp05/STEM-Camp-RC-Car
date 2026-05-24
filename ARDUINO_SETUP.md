# Arduino IDE Setup Guide for ESP32-CAM

This guide walks you through setting up the Arduino IDE to program the ESP32-CAM with the necessary board definitions and libraries.

## Prerequisites

- Arduino IDE installed on your computer ([Download here](https://www.arduino.cc/en/software))
- USB cable for connecting the ESP32-CAM to your computer
- ESP32-CAM development board with OV2640 camera sensor

## Step 1: Add ESP32 Board Support

1. Open the **Arduino IDE**.
2. Go to **File → Preferences** (or **Arduino IDE → Settings** on macOS).
3. In the "Additional Boards Manager URLs" field, paste the following URL:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Click **OK** to save.

## Step 2: Install ESP32 Board Package

1. Go to **Tools → Board → Boards Manager**.
2. Search for `ESP32` in the search box.
3. Find **"esp32 by Espressif Systems"** and click the **Install** button.
4. Select the **latest version** and wait for the installation to complete.

## Step 3: Select the Correct Board

1. Go to **Tools → Board** and look for the ESP32 section.
2. Select **"AI Thinker ESP32-CAM"** from the dropdown menu.

## Step 4: Configure Upload Settings

These settings are required for the CameraWebServer sketch to fit on the board and perform optimally:

1. Go to **Tools** and configure the following:
   - **Upload Speed:** 921600 (faster uploads)
   - **CPU Frequency:** 240 MHz (standard performance)
   - **Flash Frequency:** 80 MHz (optimized for stability)
   - **Flash Mode:** DIO (required for this board)
   - **Partition Scheme:** Huge APP (3MB No OTA / 1MB SPIFFS) - **Critical:** The CameraWebServer sketch is large and requires this partition scheme to fit. Using the default partition will cause upload failures.
   - **Core Debug Level:** None

If you skip these settings, the sketch upload will likely fail due to insufficient space.

## Step 5: Select the COM Port

1. Connect your ESP32-CAM to your computer using the USB cable.
2. Go to **Tools → Port** and select the COM port corresponding to your device (typically `COM3` or higher on Windows).

## Troubleshooting

### Port Not Showing Up
- Verify that the USB cable supports data transfer (not just power).
- Check that your ESP32-CAM is properly connected to the MB board or FTDI programmer.

### Upload Fails
- Ensure the board is set to **"AI Thinker ESP32-CAM"** in **Tools → Board**.
- Verify that the **Partition Scheme** is set to **"Huge APP (3MB No OTA / 1MB SPIFFS)"** - this is critical for the CameraWebServer sketch.
- Try holding the **BOOT** button on the development board while uploading.
- Check that you're using the latest version of the ESP32 libraries (from Boards Manager).

### Camera Not Working
- Verify that the OV2640 camera is properly seated in the ESP32-CAM camera connector.
- Ensure no MicroSD card is inserted in the board.

### Other Issues
- **Ask an AI Assistant:** Use ChatGPT, Claude, GitHub Copilot, or similar tools to troubleshoot specific error messages.
- **Contact the Developer:** Reach out to `victorrafaelsantana@hotmail.es` with a detailed explanation of the issue, including error messages and the steps you've already tried.

---

Once your Arduino IDE is configured, return to the [main README](README.md) and follow the Setup & Installation section to flash your ESP32-CAM.
