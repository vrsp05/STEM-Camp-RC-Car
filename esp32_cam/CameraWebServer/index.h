const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>BYU STEM Camp RC Car</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        :root { --byu-blue: #003478; --white: #ffffff; --light-gray: #f5f5f5; }
        body { background-color: var(--byu-blue); color: #333; font-family: sans-serif; display: flex; flex-direction: column; align-items: center; min-height: 100vh; }
        
        .header { background: var(--white); width: 100%; padding: 15px; text-align: center; border-bottom: 4px solid #0055B7; margin-bottom: 20px;}
        .header h1 { color: var(--byu-blue); font-size: 1.5em; }
        
        .container { background: var(--white); padding: 20px; border-radius: 12px; max-width: 600px; width: 95%; box-shadow: 0 4px 15px rgba(0,0,0,0.2); }
        
        .video-box { width: 100%; background: #000; border: 3px solid var(--byu-blue); border-radius: 8px; aspect-ratio: 4/3; overflow: hidden; margin-bottom: 20px;}
        img#stream { width: 100%; height: 100%; object-fit: cover; }
        
        /* The D-Pad Layout */
        .controls { display: grid; grid-template-columns: repeat(3, 1fr); gap: 10px; max-width: 300px; margin: 0 auto; }
        .controls button { padding: 20px 0; font-size: 1.2em; font-weight: bold; background: var(--byu-blue); color: white; border: none; border-radius: 8px; cursor: pointer; user-select: none; -webkit-user-select: none;}
        .controls button:active { background: #0055B7; transform: scale(0.95); }
        
        /* Grid Placement */
        #btn-fwd { grid-column: 2; }
        #btn-left { grid-column: 1; }
        #btn-stop { grid-column: 2; background: #dc2626; }
        #btn-right { grid-column: 3; }
        #btn-rev { grid-column: 2; }

        .status { text-align: center; margin-top: 15px; font-size: 0.9em; color: #666; font-weight: bold;}
    </style>
</head>
<body>

    <div class="header">
        <h1>RC Car Live Stream</h1>
        <p>BYU STEM Camp</p>
    </div>

    <div class="container">
        <div class="video-box">
            <img id="stream" src="" alt="Live Video">
        </div>

        <div class="controls">
            <div></div> <button id="btn-fwd">▲</button>
            <div></div> <button id="btn-left">◀</button>
            <button id="btn-stop">■</button>
            <button id="btn-right">▶</button>
            
            <div></div> <button id="btn-rev">▼</button>
            <div></div> </div>
        
        <div class="status" id="ws-status">Connecting to Car...</div>
    </div>

    <script>
        // Start the video stream
        window.onload = function() {
            var streamUrl = window.location.protocol + '//' + window.location.hostname + ':81/stream';
            document.getElementById('stream').src = streamUrl;
        };

        // --- WebSocket Setup ---
        var ws;
        var statusText = document.getElementById('ws-status');

        function connectWebSocket() {
            // Point the socket to Port 82
            ws = new WebSocket('ws://' + window.location.hostname + ':82/');
            
            ws.onopen = function() {
                statusText.innerText = "Car Connected & Ready!";
                statusText.style.color = "green";
            };
            
            ws.onclose = function() {
                statusText.innerText = "Connection Lost. Reconnecting...";
                statusText.style.color = "red";
                setTimeout(connectWebSocket, 2000); // Try to reconnect every 2s
            };
        }

        connectWebSocket();

        // --- Sending Commands ---
        function sendCommand(cmd) {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(cmd);
            }
        }

        // --- Button Listeners (Touch & Mouse) ---
        // Forward
        document.getElementById('btn-fwd').addEventListener('mousedown', () => sendCommand('forward'));
        document.getElementById('btn-fwd').addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand('forward'); });
        
        document.getElementById('btn-fwd').addEventListener('mouseup', () => sendCommand('stop'));
        document.getElementById('btn-fwd').addEventListener('touchend', (e) => { e.preventDefault(); sendCommand('stop'); });

        // Reverse
        document.getElementById('btn-rev').addEventListener('mousedown', () => sendCommand('backward'));
        document.getElementById('btn-rev').addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand('backward'); });
        
        document.getElementById('btn-rev').addEventListener('mouseup', () => sendCommand('stop'));
        document.getElementById('btn-rev').addEventListener('touchend', (e) => { e.preventDefault(); sendCommand('stop'); });

        // Left
        document.getElementById('btn-left').addEventListener('mousedown', () => sendCommand('left'));
        document.getElementById('btn-left').addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand('left'); });
        
        document.getElementById('btn-left').addEventListener('mouseup', () => sendCommand('stop'));
        document.getElementById('btn-left').addEventListener('touchend', (e) => { e.preventDefault(); sendCommand('stop'); });

        // Right
        document.getElementById('btn-right').addEventListener('mousedown', () => sendCommand('right'));
        document.getElementById('btn-right').addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand('right'); });
        
        document.getElementById('btn-right').addEventListener('mouseup', () => sendCommand('stop'));
        document.getElementById('btn-right').addEventListener('touchend', (e) => { e.preventDefault(); sendCommand('stop'); });

        // Stop (Emergency Brake)
        document.getElementById('btn-stop').addEventListener('click', () => sendCommand('stop'));
        document.getElementById('btn-stop').addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand('stop'); });
    </script>
</body>
</html>
)rawliteral";