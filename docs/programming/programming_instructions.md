# BYU STEM Camp RC Car: Programming Guide

Welcome to the final step of your RC Car build! Right now, your car is just plastic, motors, and wires. In this guide, we are going to give it a brain.

The tiny computer on your car (called the ESP32-CAM) is incredibly special. It does not just hold code, it actually creates its very own invisible Wi-Fi network! 

Here is how the magic works:
1. **The Code:** We will upload a file that teaches the brain how to drive.
2. **The Wi-Fi:** The brain will create a private Wi-Fi network just for your car.
3. **The Connection:** You will connect your phone to that network, turning your phone into the steering wheel and the video screen.

Let's get your car programmed and ready to race!

## Step-by-Step Setup

### 1. Name Your Car & Pick a Wi-Fi Channel

Before we put the brain into the car, we need to give it a unique identity. If all the cars in the room have the exact same Wi-Fi name, your phone will not know which one is yours, and you might accidentally connect to your friend's car! 

We also need to pick a Wi-Fi **Channel**. Think of a channel like a lane on an invisible highway. If every single car in the camp tries to drive in the exact same lane, there will be a massive traffic jam and your live video will freeze. 

Here is exactly how to change your car's name and pick your highway lane in the code:

1. **Open the Code:** Open the Arduino IDE on your computer. Click **File > Open**, and open the main code file located inside your `firmware/rc_car_main` folder called `rc_car_main.ino`. 
2. **Find the Wi-Fi Name:** Scroll down near the top of the code until you see a line that sets the network name. It will look something like this:
   `const char *carSSID = "BYU-Car-0";`
3. **Change the Name:** Delete the words inside the quotation marks and type in your own custom name (for example: `"BYU-Car-1"` or `"Lightning"`). *Warning: Make sure you do not delete the quotation marks!*
4. **Find the Channel:** Right below your name, look for the line that sets the Wi-Fi channel. It will look something like this:
   `const int wifiChannel = 1;`
5. **Pick Your Lane:** Change that number to **1**, **6**, or **11**. These three numbers are the best "fast lanes" for Wi-Fi. *(Pro-Tip: Ask the students sitting next to you which number they picked, and try to choose a different one so your cars do not share the same lane!)*

### 2. Flash the Firmware (Upload the Brain)

Now that you have chosen a name and a lane, it is time to transfer the code from your computer into the ESP32-CAM. We call this "flashing" the firmware. 

1. **Remove the Brain:** Before you plug anything in, you MUST unplug the ESP32-CAM from the car's main circuit board.
2. **Plug it In:** Connect the ESP32-CAM to its motherboard and then to your computer using a USB cable. 
3. **Pick the Right Brain:** In the Arduino program, click on **Tools > Board** and select **"AI Thinker ESP32-CAM"**.
4. **Pick the Right Cable:** Click on **Tools > Port** and select the COM port that shows up (this tells the computer which USB plug you are using).
5. **Click Upload:** Click the round **Right Arrow (Upload)** button at the top left of your screen. 

Watch the black box at the bottom of the screen. When the text stops moving and it says **"Done Uploading,"** your car's brain is officially programmed!

### 3. Power On and Connect (Wake Up the Car)

Now that the brain is programmed, it is time to cut the cord and let the car wake up on its own!

1. **Unplug the Cable:** Carefully unplug the USB cable from the car's brain. You don't need the computer anymore! Now plug the ESP32 back into the car.
2. **Turn on the Batteries:** Make sure you have 4 AA batteries in the holder, and flip the main power switch on the car to the **ON** position. 
3. **Find Your Network:** Open the Wi-Fi settings on your smartphone (or a tablet).
4. **Connect to Your Car:** Look at the list of Wi-Fi networks and tap on the custom name you created in Step 1 (like "BYU-Car-1"). 

*Note: Your car's network does not have a password, so it will connect instantly. Your phone might pop up a warning saying "No Internet Connection." Do not worry—that is exactly what is supposed to happen because your car is not a normal Wi-Fi router!*

### 4. Launch the Dashboard (Take the Wheel)

You are connected! Now it is time to open your digital steering wheel and see through the car's eyes.

1. **Open a Browser:** Open a web browser on your phone or computer (like Safari, Chrome, or Edge).
2. **Type the Secret Address:** Tap on the search bar at the very top of your screen, type in exactly **192.168.4.1**, and hit Enter. 
3. **Start Driving:** The screen will load your custom dashboard! You should immediately see a live video feed from the front of your car. Use the D-pad buttons to steer, and play with the sliders to turn on your headlights!

## Using the Web Interface

Once the dashboard loads, you will have full control over the car's hardware. Here is what each section of the interface does:

- **Live Video Feed:** The screen at the top displays the real-time camera stream.
- **Directional Pad (D-Pad):** These are your driving controls. Press the top, bottom, left, and right arrows to move the car. The square button in the center acts as the brake to stop the motors.
- **Headlights Slider:** This controls the physical LED flash on the front of the ESP32-CAM. Sliding it to the right increases the brightness so you can navigate in dark environments.
- **Brightness Slider:** This is a software control that adjusts the camera sensor's exposure. If your video feed is too dark or washed out by the sun, adjust this slider to let more or less digital light into the lens.
- **Contrast Slider:** This modifies the difference between the light and dark areas of the video feed. Increasing the contrast can help make edges and obstacles look sharper and more defined on your screen.

## Keep Hacking at Home

The best part of engineering is breaking things and making them your own. If you want to see exactly how this code works or start modifying the dashboard and motor controls yourself, you can find the complete source code online.

Go to the [firmware/rc_car_main](/firmware/rc_car_main/) folder to view the code. Be sure to fork the repository to your own account so you can start making your own changes and improvements!

## Troubleshooting & Pro-Tips

### 1. Code Upload Issues

* **The Missing COM Port:** If you connect your board to the computer but do not see a COM port listed, you are likely using a "charge-only" USB cable. Swap it out for a cable that supports data transfer to fix the issue.
* **The Antenna Effect (Flashing Crash):** If your upload crashes with an `exit status 2` error, your car's body is causing interference. You must completely remove the ESP32-CAM from the custom car PCB before flashing. If it is plugged in, the copper lines on the board act like antennas and scramble the data transfer.
* **The "Hidden" Upload Speed:** If the Arduino IDE hides the "Upload Speed" option when you select the AI Thinker board, you can outsmart it! Change your board to **ESP32 Dev Module**. This generic profile unlocks the hidden menu. Set your Upload Speed to **115200**, change **PSRAM** to **Enabled**, and hit upload. This prevents the high-speed crashing issue.
* **The "Upload Fails" Timeout:** If your upload hangs or fails to connect, ensure you have the "AI Thinker ESP32-CAM" selected as your board. If it still fails, you can physically force the connection by pressing and holding the **I0O** button on your programmer board while the code is uploading.

### 2. Video & Camera Issues

* **Camera Not Working (Blank Screen):** If the dashboard loads but you have no video, first verify that the tiny OV2640 camera ribbon is snapped completely into its connector. Second, ensure there is absolutely no MicroSD card inserted into the board.
* **Hardware Warning (The "Blind Car"):** Sometimes, cheap or low-quality ESP32-CAM boards will connect and drive perfectly, but the video will just refuse to show up no matter what you do. To prevent this, we highly recommend buying your ESP32-CAM boards from trusted, high-quality manufacturers!

### 3. Wi-Fi & Driving Connection (Phone to Car)

* **Video Freezing or Losing Control:** If the live video feed suddenly stops or the car stops responding to your controls, you have likely driven out of the ESP32's Wi-Fi range. Try these steps to fix it:
  1. **Get Closer:** Walk back toward the car so your phone is within a clear line of sight, and refresh the web page.
  2. **Restart the Wi-Fi:** Turn the Wi-Fi off and then back on in your phone or computer settings, then reconnect to your car's network.
  3. **Restart the Car:** Turn the car's power off, wait a few seconds, and turn it back on. Reconnect your phone to the network and reload the dashboard.