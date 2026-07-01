# Hardware & Wiring Notes

If you are building the car using the custom STEM Camp PCB, this guide explains exactly how the electronics connect and the number one physical mistake to avoid when building your drivetrain!

## Wiring Guide

The custom PCB handles all the complicated power routing for you, but it is helpful to know exactly how the car's brain talks to the wheels. The ESP32-CAM sends signals to the motor controller using these specific pins:

* **Left Motors (Channel A):** Controlled by GPIO 14 and GPIO 15
* **Right Motors (Channel B):** Controlled by GPIO 13 and GPIO 12
* **Camera LED Flashlight:** Controlled by GPIO 4

## Crucial Assembly Warning: The "Mirror Effect"

When you build a 4-wheel drive car, you have front motors and back motors. Because of how they fit into the plastic frame, the front and back motors are physically facing opposite directions. They are "mirrored."

**The Problem:** If you solder the wires to the front motors and the back motors exactly the same way, the front wheels will spin forward, but the back wheels will spin backward. The car will fight against itself and will not move properly!

**The Fix:** You must solder the wires on the back motors "backwards" compared to the front motors so all four wheels push in the exact same direction. 

* If your **Front** motors (M1 & M3) have the **Red** wire on the + pin and the **Black** wire on the - pin.
* Your **Back** motors (M2 & M4) must have the **Black** wire on the + pin and the **Red** wire on the - pin. 

Always double-check your motor wiring before you screw the chassis completely together!