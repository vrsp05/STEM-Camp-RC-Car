#!/usr/bin/env python3
"""
ESP32-CAM Proxy Server
Serves a local web interface and proxies video streams from ESP32 cameras
Supports multiple interface versions: web_interface (official) and test_interface (beta)
"""

from http.server import HTTPServer, SimpleHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
import urllib.request
import os
import sys

# Get the directory containing this script
script_dir = os.path.dirname(os.path.abspath(__file__))

class ProxyHandler(SimpleHTTPRequestHandler):
    def translate_path(self, path):
        """Override to serve files from the project root with web_interface as default"""
        # Parse path
        parsed_path = urlparse(path)
        request_path = parsed_path.path
        
        # If root is requested, redirect to web_interface
        if request_path == '/':
            request_path = '/web_interface/index.html'
        
        # Convert URL path to filesystem path
        if request_path.startswith('/test_interface/'):
            # Serve from test_interface folder
            filepath = os.path.join(script_dir, 'test_interface', request_path[len('/test_interface/'):])
        elif request_path.startswith('/web_interface/'):
            # Serve from web_interface folder
            filepath = os.path.join(script_dir, 'web_interface', request_path[len('/web_interface/'):])
        else:
            # Default to web_interface for root and index
            if request_path.endswith('/'):
                filepath = os.path.join(script_dir, 'web_interface', 'index.html')
            else:
                filepath = os.path.join(script_dir, 'web_interface', request_path)
        
        return filepath

    def do_GET(self):
        """Handle GET requests - serve files or proxy stream"""
        
        # Parse the request URL
        parsed_path = urlparse(self.path)
        path = parsed_path.path
        query = parse_qs(parsed_path.query)
        
        # Handle stream proxy requests
        if path == '/stream':
            # Get ESP32 IP and port from query parameters
            esp32_ip = query.get('ip', ['172.20.10.4'])[0]
            esp32_port = query.get('port', ['81'])[0]
            
            stream_url = f'http://{esp32_ip}:{esp32_port}/stream'
            
            try:
                print(f"[STREAM] Proxying to {stream_url}", file=sys.stderr)
                
                # Open connection to ESP32 stream
                response = urllib.request.urlopen(stream_url, timeout=10)
                
                # Send response headers
                self.send_response(200)
                self.send_header('Content-Type', response.headers.get('Content-Type', 'image/jpeg'))
                self.send_header('Connection', 'keep-alive')
                self.send_header('Access-Control-Allow-Origin', '*')
                self.end_headers()
                
                # Stream the video data
                while True:
                    chunk = response.read(4096)
                    if not chunk:
                        break
                    self.wfile.write(chunk)
                    
            except urllib.error.URLError as e:
                print(f"[ERROR] Failed to connect to {stream_url}: {e}", file=sys.stderr)
                self.send_error(503, f"Cannot connect to ESP32 at {esp32_ip}:{esp32_port}")
            except Exception as e:
                print(f"[ERROR] Stream error: {e}", file=sys.stderr)
                self.send_error(500, str(e))
        else:
            # Serve static files (HTML, CSS, JS)
            super().do_GET()
    
    def end_headers(self):
        """Add CORS headers to all responses"""
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, OPTIONS')
        super().end_headers()
    
    def log_message(self, format, *args):
        """Custom logging"""
        print(f"[{self.client_address[0]}] {format % args}", file=sys.stderr)


if __name__ == '__main__':
    port = 8000
    server_address = ('localhost', port)
    httpd = HTTPServer(server_address, ProxyHandler)
    
    print(f"🎯 ESP32-CAM Proxy Server running on http://localhost:{port}")
    print(f"\n📚 Available Versions:")
    print(f"  Official:  http://localhost:{port}/web_interface/")
    print(f"  Beta/Test: http://localhost:{port}/test_interface/")
    print(f"\n🔗 With custom ESP32 IPs:")
    print(f"  Official:  http://localhost:{port}/web_interface/?ip=192.168.1.100&port=81")
    print(f"  Beta/Test: http://localhost:{port}/test_interface/?ip=192.168.1.100&port=81")
    print(f"\n⚡ Default (opens official): http://localhost:{port}")
    print(f"\nPress Ctrl+C to stop...")
    
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n✋ Server stopped")
        sys.exit(0)
