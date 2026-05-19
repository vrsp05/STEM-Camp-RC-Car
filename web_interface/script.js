const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const ipInput = document.getElementById('ipInput');
const portInput = document.getElementById('portInput');
const statusIndicator = document.getElementById('statusIndicator');
const statusText = document.getElementById('statusText');
const errorMessage = document.getElementById('errorMessage');

let streamController = null;
let isConnecting = false;
let isConnected = false;
let reconnectAttempts = 0;
const MAX_RECONNECT_ATTEMPTS = 5;
const RECONNECT_DELAY = 2000;

// Load saved settings from localStorage and URL parameters
window.addEventListener('DOMContentLoaded', () => {
    // Check URL parameters first (for proxy server)
    const urlParams = new URLSearchParams(window.location.search);
    const paramIP = urlParams.get('ip');
    const paramPort = urlParams.get('port');
    
    // Fall back to localStorage, then defaults
    const savedIP = paramIP || localStorage.getItem('rcCarIP') || '172.20.10.4';
    const savedPort = paramPort || localStorage.getItem('rcCarPort') || '81';
    
    ipInput.value = savedIP;
    portInput.value = savedPort;
    
    // Save to localStorage for next visit
    localStorage.setItem('rcCarIP', savedIP);
    localStorage.setItem('rcCarPort', savedPort);
    
    // Set canvas resolution
    canvas.width = 640;
    canvas.height = 480;
    
    // Draw initial message
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = '#666';
    ctx.font = '20px sans-serif';
    ctx.textAlign = 'center';
    ctx.fillText('Ready to connect', canvas.width / 2, canvas.height / 2);
    
    // Auto-connect on page load
    setTimeout(() => connectStream(), 500);
});

// Save settings when changed
ipInput.addEventListener('change', () => {
    localStorage.setItem('rcCarIP', ipInput.value);
});
portInput.addEventListener('change', () => {
    localStorage.setItem('rcCarPort', portInput.value);
});

function setStatus(status, message) {
    statusIndicator.className = 'status-indicator ' + status;
    statusText.textContent = message;
    isConnected = status === 'connected';
}

function showError(message) {
    errorMessage.textContent = '⚠️ ' + message;
    errorMessage.classList.add('show');
    setTimeout(() => {
        errorMessage.classList.remove('show');
    }, 5000);
}

function connectStream() {
    if (isConnecting) return;
    
    const ip = ipInput.value.trim();
    const port = portInput.value.trim();
    
    if (!ip) {
        showError('Please enter ESP32 IP address');
        return;
    }
    
    disconnectStream();
    
    isConnecting = true;
    reconnectAttempts = 0;
    setStatus('connecting', 'Connecting...');
    
    // Use proxy server (passes IP/port as query params)
    const streamURL = `/stream?ip=${encodeURIComponent(ip)}&port=${encodeURIComponent(port)}`;
    
    streamController = new AbortController();
    
    // Use a timeout to handle hung connections
    const timeoutId = setTimeout(() => {
        if (isConnecting) {
            console.warn('Connection timeout, retrying...');
            handleStreamDisconnect();
        }
    }, 5000);
    
    fetch(streamURL, {
        signal: streamController.signal
    })
    .then(response => {
        clearTimeout(timeoutId);
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.body.getReader();
    })
    .then(reader => {
        isConnecting = false;
        setStatus('connected', 'Connected');
        reconnectAttempts = 0;
        
        processMJPEG(reader);
    })
    .catch(err => {
        clearTimeout(timeoutId);
        if (err.name !== 'AbortError') {
            console.error('Stream error:', err);
            handleStreamDisconnect();
        }
    });
}

function processMJPEG(reader) {
    let buffer = new Uint8Array(0);
    
    function read() {
        reader.read().then(({ done, value }) => {
            if (done) {
                handleStreamDisconnect();
                return;
            }
            
            // Append new chunk to buffer
            buffer = new Uint8Array([...buffer, ...value]);
            
            // Try to extract and display frames
            while (buffer.length > 0) {
                // Look for the start of a frame (FFD8 = JPEG SOI marker)
                let jpegStart = -1;
                for (let i = 0; i < buffer.length - 1; i++) {
                    if (buffer[i] === 0xFF && buffer[i + 1] === 0xD8) {
                        jpegStart = i;
                        break;
                    }
                }
                
                if (jpegStart === -1) {
                    // No JPEG start found, keep last 2 bytes in case boundary is split
                    buffer = buffer.slice(Math.max(0, buffer.length - 2));
                    break;
                }
                
                // Look for end of JPEG (FFD9 = JPEG EOI marker)
                let jpegEnd = -1;
                for (let i = jpegStart + 2; i < buffer.length - 1; i++) {
                    if (buffer[i] === 0xFF && buffer[i + 1] === 0xD9) {
                        jpegEnd = i + 2;
                        break;
                    }
                }
                
                if (jpegEnd === -1) {
                    // Incomplete frame, wait for more data
                    buffer = buffer.slice(jpegStart);
                    break;
                }
                
                // Extract and display the complete JPEG frame
                const jpegData = buffer.slice(jpegStart, jpegEnd);
                displayFrame(jpegData);
                
                // Remove processed data from buffer
                buffer = buffer.slice(jpegEnd);
            }
            
            // Continue reading
            read();
        }).catch(err => {
            if (err.name !== 'AbortError') {
                console.error('Read error:', err);
                handleStreamDisconnect();
            }
        });
    }
    
    read();
}

function displayFrame(jpegData) {
    const blob = new Blob([jpegData], { type: 'image/jpeg' });
    const url = URL.createObjectURL(blob);
    
    const img = new Image();
    img.onload = () => {
        ctx.drawImage(img, 0, 0, canvas.width, canvas.height);
        URL.revokeObjectURL(url);
    };
    img.onerror = () => {
        console.error('Failed to decode frame');
        URL.revokeObjectURL(url);
    };
    img.src = url;
}

function handleStreamDisconnect() {
    isConnecting = false;
    
    if (reconnectAttempts < MAX_RECONNECT_ATTEMPTS) {
        reconnectAttempts++;
        setStatus('connecting', `Reconnecting (${reconnectAttempts}/${MAX_RECONNECT_ATTEMPTS})...`);
        setTimeout(() => {
            if (isConnected || isConnecting) return;
            connectStream();
        }, RECONNECT_DELAY);
    } else {
        setStatus('disconnected', 'Disconnected');
        showError('Failed to connect after ' + MAX_RECONNECT_ATTEMPTS + ' attempts. Check ESP32 IP address and ensure it\'s online.');
        
        // Clear canvas
        ctx.fillStyle = '#000';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = '#666';
        ctx.font = '20px sans-serif';
        ctx.textAlign = 'center';
        ctx.fillText('Connection Failed', canvas.width / 2, canvas.height / 2 - 20);
        ctx.font = '14px sans-serif';
        ctx.fillText('Check IP address and try again', canvas.width / 2, canvas.height / 2 + 20);
    }
}

function disconnectStream() {
    isConnecting = false;
    isConnected = false;
    if (streamController) {
        streamController.abort();
        streamController = null;
    }
    setStatus('disconnected', 'Disconnected');
    
    // Clear canvas
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = '#666';
    ctx.font = '20px sans-serif';
    ctx.textAlign = 'center';
    ctx.fillText('Disconnected', canvas.width / 2, canvas.height / 2);
}
