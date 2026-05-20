const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>BYU STEM Camp RC Car - Live Stream</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        :root { --byu-blue: #003478; --byu-light-blue: #0055B7; --white: #ffffff; --light-gray: #f5f5f5; --dark-gray: #333333; }
        body { background-color: var(--byu-blue); color: var(--dark-gray); font-family: sans-serif; min-height: 100vh; display: flex; flex-direction: column; }
        header { background-color: var(--white); padding: 15px 20px; border-bottom: 4px solid var(--byu-blue); text-align: center; }
        .header-text h1 { font-size: 1.8em; color: var(--byu-blue); font-weight: 700; }
        .header-text p { font-size: 0.9em; color: #666; margin-top: 2px; }
        .container { flex: 1; display: flex; flex-direction: column; align-items: center; padding: 30px 20px; width: 100%; max-width: 800px; margin: 0 auto; }
        .stream-section { background-color: var(--white); border-radius: 12px; padding: 25px; width: 100%; box-shadow: 0 4px 16px rgba(0,0,0,0.15); }
        .stream-title { font-size: 1.3em; color: var(--byu-blue); margin-bottom: 15px; font-weight: 600; text-align: center; }
        .stream-container { background: #000; border: 3px solid var(--byu-blue); border-radius: 10px; overflow: hidden; display: flex; justify-content: center; align-items: center; aspect-ratio: 4/3; }
        img#stream { max-width: 100%; max-height: 100%; display: block; }
        .config-section { background-color: var(--light-gray); padding: 20px; border-radius: 10px; border-left: 4px solid var(--byu-blue); margin-top: 15px; display: flex; justify-content: center; gap: 15px; }
        button { padding: 10px 20px; background-color: var(--byu-blue); color: var(--white); border: none; border-radius: 6px; font-weight: 600; cursor: pointer; font-size: 1em; }
        button:hover { background-color: var(--byu-light-blue); }
        footer { background-color: var(--byu-blue); color: var(--white); text-align: center; padding: 20px; margin-top: auto; font-size: 0.9em; }
    </style>
</head>
<body>
    <header>
        <div class="header-text">
            <h1>RC Car Live Stream</h1>
            <p>BYU STEM Camp 2026</p>
        </div>
    </header>

    <div class="container">
        <div class="stream-section">
            <h2 class="stream-title">Live Video Feed</h2>
            <div class="stream-container">
                <img id="stream" src="" alt="Stream will appear here">
            </div>
            
            <div class="config-section">
                <button onclick="startStream()">Start Stream</button>
                <button onclick="stopStream()" style="background-color: #dc2626;">Stop Stream</button>
            </div>
        </div>
    </div>

    <footer>
        <p>&copy; 2026 Brigham Young University STEM Camp</p>
    </footer>

    <script>
        function startStream() {
            // This grabs the exact IP address the ESP32 is currently using
            var streamUrl = window.location.protocol + '//' + window.location.hostname + ':81/stream';
            document.getElementById('stream').src = streamUrl;
        }

        function stopStream() {
            document.getElementById('stream').src = "";
        }
        
        // Auto-start when page loads
        window.onload = startStream;
    </script>
</body>
</html>
)rawliteral";