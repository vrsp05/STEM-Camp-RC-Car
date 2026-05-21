const char SETUP_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Car Setup - BYU STEM Camp</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        :root { --byu-blue: #003478; --white: #ffffff; }
        body { background-color: var(--byu-blue); color: #333; font-family: sans-serif; display: flex; justify-content: center; align-items: center; height: 100vh; }
        
        .card { background: var(--white); padding: 30px; border-radius: 12px; width: 90%; max-width: 400px; text-align: center; box-shadow: 0 4px 15px rgba(0,0,0,0.3); }
        .card h2 { color: var(--byu-blue); margin-bottom: 10px; }
        .card p { font-size: 0.9em; color: #666; margin-bottom: 20px; }
        
        input { width: 100%; padding: 12px; margin: 10px 0; border: 2px solid var(--byu-blue); border-radius: 6px; font-size: 1em; }
        input:focus { outline: none; box-shadow: 0 0 5px rgba(0, 52, 120, 0.5); }
        
        button { background: var(--byu-blue); color: var(--white); padding: 15px; border: none; border-radius: 6px; width: 100%; cursor: pointer; font-weight: bold; font-size: 1.1em; margin-top: 10px; transition: background 0.3s; }
        button:hover { background: #0055B7; }
    </style>
</head>
<body>

    <div class="card">
        <h2>Name Your Car</h2>
        <p>Give your RC car a unique Wi-Fi name and a secure password.</p>
        
        <input type="text" id="ssid" placeholder="Car Name (e.g., BYU-Car-Victor)" maxlength="32">
        <input type="text" id="pass" placeholder="Password (minimum 8 characters)" minlength="8">
        
        <button id="save-btn" onclick="saveSettings()">Save & Restart</button>
    </div>

    <script>
        function saveSettings() {
            var s = document.getElementById('ssid').value.trim();
            var p = document.getElementById('pass').value.trim();
            
            // Safety check!
            if(s === "" || p.length < 8) { 
                alert("Please enter a name and a password (must be at least 8 characters)."); 
                return; 
            }
            
            // Change button to show it is working
            var btn = document.getElementById('save-btn');
            btn.innerText = "Saving & Restarting...";
            btn.style.background = "#22c55e"; // Success green
            
            // Open the WebSocket window and fire the data to the ESP32
            var ws = new WebSocket('ws://' + window.location.hostname + ':82/');
            ws.onopen = function() {
                // Formats it like: "config:BYU-Car-Victor,camp2026"
                ws.send("config:" + s + "," + p); 
            };
        }
    </script>
</body>
</html>
)rawliteral";