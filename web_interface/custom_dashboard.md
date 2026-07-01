# Customizing the Dashboard

If you want to customize the look of your car's driving dashboard (change colors, adjust button sizes, or add new controls), do **not** edit the C++ files directly right away!

Inside this repository, you will find a folder called `web_interface` containing an `index.html` file. This is your **UI Sandbox**. Because the structure (HTML) and the styling (CSS) are both inside this single file, testing new designs is incredibly easy.

## How to Test and Save Your Changes

1. **Open the Sandbox:** Double-click `index.html` to open it in your web browser. 
2. **Edit the Code:** Open the exact same file in any text editor (like VS Code or Notepad) and make your changes.
3. **Test Instantly:** Refresh your web browser to see your changes instantly. *(Note: You will not see the live video feed yet, but you will see all your new colors and buttons!)*
4. **Copy Your Work:** Once your new dashboard looks perfect, select everything and copy the entire contents of your customized `index.html` file.
5. **Flash to the Car:** Open `firmware/rc_car_main/index.h` and carefully paste your new code inside the raw string literal to permanently flash it to the car.

## 3 Fun Challenges to Try

Before you copy your final code over to the car, try completing these three challenges inside your `index.html` file!

### Challenge 1: Change the Background Color
Right now, the dashboard has a dark blue background. Let's make it your favorite color!
* Look inside the `<style>` section near the top of the file.
* Find the line that starts with `body { background-color: var(--byu-blue);`. 
* Change `var(--byu-blue)` to a simple color name like `black`, `green`, or `orange`. Save the file and refresh your browser!

### Challenge 2: Change the Button Symbols to Words
Right now, the driving buttons use shapes like ▲ and ■. Want to make them say words instead? 
* Scroll down past the styles until you find the HTML code for the buttons (look for lines like `<button id="btn-fwd">▲</button>`).
* Delete the ▲ symbol and type in a word like "FORWARD" or "GAS". Save the file and refresh your browser.

### Challenge 3: Make the D-Pad Bigger
If the steering buttons are too small for your thumbs, you can scale them up!
* Go back up to the `<style>` section and look for the `.controls button {` line. 
* Find `padding: 20px 0;` and change the `20` to `35`.
* Find `font-size: 1.2em;` and change the `1.2` to `2.0`. 
* Save your file, and see how your giant buttons look on the screen!