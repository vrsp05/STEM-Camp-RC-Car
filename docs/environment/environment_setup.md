# Setting Up Your Computer (Arduino IDE)

Before we can teach the car how to drive, we need to teach your computer how to talk to the car's brain. To do this, we use a free program called the **Arduino IDE**.

## What You Need (Prerequisites)

Before opening any programs, make sure you have these items ready on your desk:

* **The Free Software:** Download and install the [Arduino IDE](https://www.arduino.cc/en/software) on your computer.
* **The Car's Brain:** Your ESP32-CAM board with the tiny camera attached.
* **The USB Adapter:** The ESP32-CAM cannot plug directly into a computer! You must plug it into the small USB programmer board (the motherboard "MB" adapter shield) first.
* **A Data-Sync USB Cable:** This is incredibly important. Many phone charger cables only provide power and cannot send data. You *must* use a cable that supports data transfer, or your computer will never see the ESP32.

## Step 1: Install ESP32 Board Support

1. Open the **Arduino IDE**.
2. Go to **Tools → Board → Boards Manager**.
3. Search for `ESP32` in the search box.
4. Find **"esp32 by Espressif Systems"** and select the **latest version**.
5. Click the **Install** button and wait for the installation to complete.

## Step 2: Download the Remote Control Dictionary (WebSockets)

The ESP32 dictionary we just installed knows how to use basic Wi-Fi, but it doesn't know how to connect to our custom digital steering wheel. We need to download one tiny dictionary called a "Library" to fix that!

1. **Open the Library Manager:** In the Arduino IDE, click on **Sketch** at the top of the screen, hover over **Include Library**, and click **Manage Libraries...** (You can also just click the little icon that looks like a stack of books on the left side of your screen).
2. **Search for WebSockets:** In the search bar of the new menu, type in exactly `WebSockets` and hit Enter.
3. **Find the Right Author:** Scroll through the list until you find the library named exactly **WebSockets**. Look closely at the small text underneath the title—it **must** say **by Markus Sattler**.
4. **Install It:** Click the **Install** button next to it. Once it says "Installed," you can close the Library Manager menu!

## Step 3: Tell the Computer Which Brain You Have

The dictionary we just downloaded is huge. It contains instructions for hundreds of different ESP32 chips! We need to tell the computer exactly which one you are holding in your hand.

1. **Open the Board Menu:** At the top of your screen, click on **Tools**, hover over **Board**, and then hover over the new **esp32** folder you just installed.
2. **Find the AI Thinker:** A massive list of boards will pop out. Scroll down through this list until you find the one named exactly **"AI Thinker ESP32-CAM"**.
3. **Select It:** Click on it! 

*Pro-Tip: You can double-check that you did it right by looking at the bottom right corner of your Arduino window. It should now say "AI Thinker ESP32-CAM".*

## Step 4: Pick the Right USB Door (Select the COM Port)

Your computer has several USB plugs, and it doesn't automatically know which one is holding the car's brain. We need to point it to the right "door" so they can talk.

1. **Plug It In:** Connect your ESP32-CAM (attached to its small programmer board) to your computer using your data-sync USB cable.
2. **Open the Menu:** In the Arduino program, click on **Tools** at the top of the screen.
3. **Find the Port:** Look down the menu list and hover over **Port**. 
4. **Select the Connection:** You should see an option pop up. If you are on Windows, it will look like `COM3` (or a higher number). If you are on a Mac, it will look like `/dev/cu.usbserial-....`. Click on it! 

*Pro-Tip: If you have a bunch of different ports listed and don't know which one is your car, or if the "Port" button is completely grayed out, don't panic! Check the **How to Find Your Port** section right below this to play detective.*

---

### How to Find Your Port (Windows & Mac)

If you are completely stuck on Step 3, you can use your computer's built-in tools to figure out exactly which port your car is plugged into.

**For Windows (Device Manager):**
1. Click the Windows Start button at the bottom of your screen, type **Device Manager**, and hit Enter.
2. Look down the list for a category called **Ports (COM & LPT)** and click the little arrow next to it to open it up.
3. You are looking for a device that says **USB-SERIAL CH340** or **CP210x**.
4. Look at the number right next to it in parentheses (for example, `COM4`). That is your magic number! Go back to the Arduino IDE and select that exact port.

**For Mac (System Report):**
1. Click the **Apple logo** in the very top left corner of your screen.
2. Click **About This Mac**, then click **More Info...**, and finally scroll down and click **System Report...**.
3. On the left side of the new window, look under the "Hardware" section and click on **USB**.
4. Look through the USB Device Tree for something named **USB to UART Bridge** or **CH340**. If you see it there, your computer successfully sees the car! Go back to the Arduino program and select the port that starts with `/dev/cu.usbserial`.

*(Note: If you do not see the device in your Windows Device Manager or your Mac System Report, your USB cable is likely a "charge-only" cable. Swap it out for a real data cable and try again!)*

---

**You Did It!**
Your computer is now fully set up and ready to code. You can close this guide, return to the **[main README](../README.md)**, and follow the next steps to flash the brain and start driving!

## Troubleshooting (What if it doesn't work?)

Don't panic! Even professional engineers run into errors. Here is how to fix the most common computer bugs:

### 1. "My Port is Not Showing Up!"
* **The Cable Test:** 99% of the time, this happens because you are using a "charge-only" USB cable instead of a "data" cable. Try swapping out the cable!
* **The Connection Test:** Make sure the ESP32-CAM is pushed down firmly into the small programmer board.

### 2. "The Upload Keeps Failing!"
* **Check Your Brain:** Go back to **Tools > Board** and make absolutely sure you selected **"AI Thinker ESP32-CAM"**. 
* **The BOOT Button Trick:** Sometimes the brain is stubborn and won't accept the new code. While the code is uploading, physically press and hold the **BOOT** (or **IO0**) button on the small programmer board. This forces the chip to wake up and listen to the computer!

### 3. "My Camera Screen is Blank!"
* **The Ribbon Snap:** Check the tiny ribbon cable connecting the camera to the board. It needs to be pushed all the way in and locked down safely.
* **The MicroSD Trap:** If you have a little memory card (MicroSD card) plugged into the back of the ESP32-CAM, take it out! It completely blocks the live video from working.

### 4. "fatal error: WebSocketsServer.h: No such file or directory"
* **The Missing Library Error:** The computer is trying to build the remote control connection, but it doesn't have the instructions! Go back to **Step 2** and make absolutely sure you installed the **WebSockets by Markus Sattler** library using the Library Manager.

### 5. "The Upload Keeps Crashing / Hidden Baud Rate"
* **The Dev Module Trick:** Sometimes the computer tries to send the code too fast, which causes a crash. If you need to lower the upload speed (baud rate) but the Arduino IDE hides that option when you select the AI Thinker board, you can outsmart it! Change your board to **"ESP32 Dev Module"**. This is a generic profile that unlocks the hidden menus. Change your **Upload Speed** to **115200**, make sure **PSRAM** is **Enabled**, and try uploading again.

### 6. Still Stuck?
* **Ask an AI Helper:** If the Arduino program spits out a crazy red error message, you can copy that text and paste it into ChatGPT, Claude, or GitHub Copilot. Just ask the AI, "How do I fix this Arduino error?" and it will help translate the computer gibberish for you!