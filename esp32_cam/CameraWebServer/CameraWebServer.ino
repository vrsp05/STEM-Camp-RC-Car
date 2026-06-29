#include <Arduino.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <index.h>

// Initiate WebSocketServer using Port #82
WebSocketsServer webSocket = WebSocketsServer(82);

// ===========================
// Select camera model in board_config.h
// ===========================
#include "board_config.h"

// ===========================
// Hardcoded Factory Credentials
// Change this number for each car before flashing! (e.g., BYU-Car-2, BYU-Car-3)
// ===========================
const char *carSSID = "SixSeven";

// ===========================
// Wi-Fi Channel Selection
// Use ONLY channels 1, 6, or 11 to prevent cars from lagging each other.
// Distribute evenly: e.g., Cars 1-3 on Ch 1, Cars 4-6 on Ch 6, Cars 7-10 on Ch 11.
// ===========================
const int wifiChannel = 1;

// ===========================
// Motor Driver Blueprint
// ===========================
struct MOTOR_PINS {
  int pinIN1;
  int pinIN2;
};

// ===========================
// Motor Pin Definitions
// ===========================

// Right Motor Channel (M1 & M2) -> Pins 13 & 12
MOTOR_PINS rightMotor = {13, 12}; 

// Left Motor Channel (M3 & M4) -> Pins 15 & 14
MOTOR_PINS leftMotor = {15, 14};

// ===========================
// Software Speed Governor
// ===========================
int maxSpeed = 150; // Scale from 0 (Stop) to 255 (Full Throttle). 150 is a safe indoor speed.

// ===========================
// Movement Functions (PWM Upgraded)
// ===========================
void stopCar() {
  ledcWrite(rightMotor.pinIN1, 0);
  ledcWrite(rightMotor.pinIN2, 0);
  ledcWrite(leftMotor.pinIN1, 0);
  ledcWrite(leftMotor.pinIN2, 0);
  Serial.println("Car: STOP");
}

void driveForward() {
  // Right side (M1 & M2) pushes forward
  ledcWrite(rightMotor.pinIN1, maxSpeed);
  ledcWrite(rightMotor.pinIN2, 0);
  
  // Left side (M3 & M4) pushes forward
  ledcWrite(leftMotor.pinIN1, maxSpeed);
  ledcWrite(leftMotor.pinIN2, 0);
  
  Serial.println("Car: FORWARD (Normal)");
}

void driveBackward() {
  ledcWrite(rightMotor.pinIN1, 0);
  ledcWrite(rightMotor.pinIN2, maxSpeed);
  ledcWrite(leftMotor.pinIN1, 0);
  ledcWrite(leftMotor.pinIN2, maxSpeed);
  Serial.println("Car: BACKWARD");
}

void turnRight() {
  ledcWrite(rightMotor.pinIN1, 0);
  ledcWrite(rightMotor.pinIN2, maxSpeed);
  ledcWrite(leftMotor.pinIN1, maxSpeed);
  ledcWrite(leftMotor.pinIN2, 0);
  Serial.println("Car: RIGHT");
}

void turnLeft() {
  ledcWrite(rightMotor.pinIN1, maxSpeed);
  ledcWrite(rightMotor.pinIN2, 0);
  ledcWrite(leftMotor.pinIN1, 0);
  ledcWrite(leftMotor.pinIN2, maxSpeed);
  Serial.println("Car: LEFT");
}

void startCameraServer();
void setupLedFlash();

// ===========================
// WebSocket Client Lock
// ===========================
int activeClient = -1; // -1 means the car is currently available

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  
  // 1. Handle Disconnections
  if (type == WStype_DISCONNECTED) {
    if (activeClient == num) {
      Serial.println("Driver disconnected. Car is now available.");
      activeClient = -1; // Free up the lock for the next student
      stopCar();         // SAFETY FEATURE: Hit the brakes if Wi-Fi drops!
    }
  } 
  
  // 2. Handle New Connections
  else if (type == WStype_CONNECTED) {
    if (activeClient == -1) {
      activeClient = num; // Claim the lock
      Serial.printf("Phone [%u] Connected! Car locked.\n", num);
    } else {
      Serial.printf("Phone [%u] rejected. Car is already in use.\n", num);
      // Send an alert string to the rejected phone before dropping them
      webSocket.sendTXT(num, "ERROR: Car is currently in use by another student.");
      webSocket.disconnect(num); // Kick the intruder off the server
    }
  } 
  
  // 3. Handle Driving Commands
  else if (type == WStype_TEXT) {
    // SECURITY CHECK: Ignore commands from anyone who isn't the active driver
    if (num != activeClient) return; 

    String command = String((char*)payload);
    Serial.print("Phone sent command: ");
    Serial.println(command);

    int sepIndex = command.indexOf(':');
    
    // ==========================================
    // TYPE 1: SLIDER COMMANDS (Contains a ':')
    // ==========================================
    if (sepIndex > 0) { 
      String cmdName = command.substring(0, sepIndex);
      int cmdValue = command.substring(sepIndex + 1).toInt();
      
      if (cmdName == "led") {
        int safeValue = map(cmdValue, 0, 255, 0, 40); 
        ledcWrite(4, safeValue); 
      }
      else if (cmdName == "bright") {
        sensor_t * s = esp_camera_sensor_get();
        s->set_brightness(s, cmdValue);
      }
      else if (cmdName == "contrast") {
        sensor_t * s = esp_camera_sensor_get();
        s->set_contrast(s, cmdValue);
      }
    }
    // ==========================================
    // TYPE 2: BUTTON COMMANDS (No ':')
    // ==========================================
    else { 
      if (command == "forward") {
        driveForward();
      }
      else if (command == "backward") {
        driveBackward();
      }
      else if (command == "left") {
        turnLeft();
      }
      else if (command == "right") {
        turnRight();
      }
      else if (command == "stop") {
        stopCar();
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  
  // --- STABILITY TUNE ---
  // 1. Clock Speed: Dropped from 20MHz to 10MHz to prevent hardware crashing
  config.xclk_freq_hz = 10000000; 
  
  // 2. Resolution: Bumped to CIF (400x296) for better quality without lagging the D-Pad
  config.frame_size = FRAMESIZE_CIF; 
  
  config.pixel_format = PIXFORMAT_JPEG;
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  
  // 3. JPEG Quality: Lowered to 12 for a sharper image (lower number = less compression)
  config.jpeg_quality = 12; 
  config.fb_count = 2;

  // Fallback if the chip has bad memory
  if (!psramFound()) {
    config.frame_size = FRAMESIZE_QVGA;
    config.fb_location = CAMERA_FB_IN_DRAM;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Initialize motor pins as PWM speed outputs (1000 Hz, 8-bit resolution)
  ledcAttach(rightMotor.pinIN1, 1000, 8);
  ledcAttach(rightMotor.pinIN2, 1000, 8);
  ledcAttach(leftMotor.pinIN1, 1000, 8);
  ledcAttach(leftMotor.pinIN2, 1000, 8);
  
  // Ensure the car starts in a parked state
  stopCar();

  sensor_t *s = esp_camera_sensor_get();

  // --- THE AUTO-PILOT TUNE ---
  s->set_exposure_ctrl(s, 1); // Auto-Exposure ON (adapts to shadows/sunlight)
  s->set_aec2(s, 1);          // Advanced Auto-Exposure DSP ON
  s->set_whitebal(s, 1);      // Auto-White Balance ON (removes weird color tints)
  s->set_awb_gain(s, 1);      // Auto-White Balance Gain ON
  s->set_wb_mode(s, 0);       // Set White Balance Mode to standard Auto

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
  setupLedFlash();
#endif

  // --- Open Access Point (No Password) ---
  // Using NULL creates an open network. wifiChannel locks the broadcast frequency.
  WiFi.softAP(carSSID, NULL, wifiChannel);
  Serial.println("");
  Serial.println("Car Wi-Fi Network Started!");

  // --- BOOT FLASH ---
  // Blink the LED 3 times quickly at a safe brightness to signal the car is ready
  for(int i = 0; i < 3; i++) {
    ledcWrite(4, 25); 
    delay(150);
    ledcWrite(4, 0);   
    delay(150);
  }

  startCameraServer();

  // Initialize the Flash LED (Pin 4) for smooth brightness control (ESP32 Core v3.x)
  ledcAttach(4, 1000, 8); // Attach Pin 4, 1000 Hz, 8-bit (0-255)
  ledcWrite(4, 0);        // Start with the headlights OFF
  
  // Initialize the webSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.softAPIP());
  Serial.println("' to connect");
}

void loop() {
  webSocket.loop(); // Constantly check for new commands
  delay(1);         // A tiny pause to keep the brain stable
}