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
        
        .header { background: var(--white); width: 100%; padding: 15px; text-align: center; border-bottom: 4px solid #0055B7; margin-bottom: 10px;}
        .header h1 { color: var(--byu-blue); font-size: 1.5em; }
        
        .container { background: var(--white); padding: 20px; border-radius: 12px; max-width: 600px; width: 95%; box-shadow: 0 4px 15px rgba(0,0,0,0.2); margin-bottom: 20px; }
        
        .video-box { width: 100%; background: #000; border: 3px solid var(--byu-blue); border-radius: 8px; aspect-ratio: 4/3; overflow: hidden; margin-bottom: 20px;}
        img#stream { width: 100%; height: 100%; object-fit: cover; }
        
        /* The D-Pad Layout */
        .controls { display: grid; grid-template-columns: repeat(3, 1fr); gap: 10px; max-width: 300px; margin: 0 auto 20px auto; }
        .controls button { padding: 20px 0; font-size: 1.2em; font-weight: bold; background: var(--byu-blue); color: white; border: none; border-radius: 8px; cursor: pointer; user-select: none; -webkit-user-select: none;}
        .controls button:active { background: #0055B7; transform: scale(0.95); }
        
        #btn-fwd { grid-column: 2; }
        #btn-left { grid-column: 1; }
        #btn-stop { grid-column: 2; background: #dc2626; }
        #btn-right { grid-column: 3; }
        #btn-rev { grid-column: 2; }

        /* Sliders Layout */
        .slider-group { background: var(--light-gray); padding: 15px; border-radius: 8px; margin-bottom: 15px; border-left: 4px solid var(--byu-blue); }
        .slider-row { display: flex; justify-content: space-between; align-items: center; margin-bottom: 10px; }
        .slider-row:last-child { margin-bottom: 0; }
        .slider-label { font-weight: bold; font-size: 0.9em; width: 100px; }
        input[type="range"] { flex-grow: 1; margin: 0 10px; cursor: pointer; }
        .slider-val { width: 30px; text-align: right; font-size: 0.9em; font-family: monospace; color: var(--byu-blue); font-weight: bold;}

        .status { text-align: center; font-size: 0.9em; color: #666; font-weight: bold; margin-top: 10px;}
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
            <div></div>
            <button id="btn-fwd">▲</button>
            <div></div>
            <button id="btn-left">◀</button>
            <button id="btn-stop">■</button>
            <button id="btn-right">▶</button>
            <div></div>
            <button id="btn-rev">▼</button>
            <div></div>
        </div>

        <div class="slider-group">
            <div class="slider-row">
                <span class="slider-label">Headlights</span>
                <input type="range" id="led-slider" min="0" max="40" value="0">
                <span class="slider-val" id="led-val">0</span>
            </div>
            <div class="slider-row">
                <span class="slider-label">Brightness</span>
                <input type="range" id="bright-slider" min="-2" max="2" value="0">
                <span class="slider-val" id="bright-val">0</span>
            </div>
            <div class="slider-row">
                <span class="slider-label">Contrast</span>
                <input type="range" id="contrast-slider" min="-2" max="2" value="0">
                <span class="slider-val" id="contrast-val">0</span>
            </div>
        </div>
        
        <div class="status" id="ws-status">Connecting to Car...</div>
    </div>

    <script>
        window.onload = function() {
            var streamUrl = window.location.protocol + '//' + window.location.hostname + ':81/stream';
            document.getElementById('stream').src = streamUrl;
        };

        var ws;
        var statusText = document.getElementById('ws-status');

        function connectWebSocket() {
            ws = new WebSocket('ws://' + window.location.hostname + ':82/');
            ws.onopen = function() {
                statusText.innerText = "Car Connected & Ready!";
                statusText.style.color = "green";
            };
            ws.onclose = function() {
                statusText.innerText = "Connection Lost. Reconnecting...";
                statusText.style.color = "red";
                setTimeout(connectWebSocket, 2000);
            };
        }
        connectWebSocket();

        function sendCommand(cmd) {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(cmd);
            }
        }

        // D-Pad Listeners
        const btns = ['fwd', 'rev', 'left', 'right'];
        const actions = ['forward', 'backward', 'left', 'right'];
        
        btns.forEach((id, index) => {
            let el = document.getElementById('btn-' + id);
            let action = actions[index];
            el.addEventListener('mousedown', () => sendCommand(action));
            el.addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand(action); });
            el.addEventListener('mouseup', () => sendCommand('stop'));
            el.addEventListener('touchend', (e) => { e.preventDefault(); sendCommand('stop'); });
        });

        let stopBtn = document.getElementById('btn-stop');
        stopBtn.addEventListener('click', () => sendCommand('stop'));
        stopBtn.addEventListener('touchstart', (e) => { e.preventDefault(); sendCommand('stop'); });

        // Slider Listeners
        function setupSlider(id, cmdPrefix) {
            let slider = document.getElementById(id + '-slider');
            let display = document.getElementById(id + '-val');
            slider.addEventListener('input', function() {
                display.innerText = this.value;
                sendCommand(cmdPrefix + ':' + this.value);
            });
        }

        setupSlider('led', 'led');
        setupSlider('bright', 'bright');
        setupSlider('contrast', 'contrast');
    </script>
</body>
</html>
)rawliteral";