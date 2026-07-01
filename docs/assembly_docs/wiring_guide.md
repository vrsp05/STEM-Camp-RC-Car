# Wiring Guide (Custom PCB Reference)

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