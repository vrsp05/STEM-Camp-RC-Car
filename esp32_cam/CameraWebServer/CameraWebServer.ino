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

// Left Motor Channel (M3 & M4) -> Pins 14 & 15
MOTOR_PINS leftMotor = {14, 15};

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
  ledcWrite(rightMotor.pinIN1, maxSpeed);
  ledcWrite(rightMotor.pinIN2, 0);
  ledcWrite(leftMotor.pinIN1, maxSpeed);
  ledcWrite(leftMotor.pinIN2, 0);
  Serial.println("Car: FORWARD");
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

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_TEXT) {
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

  // Initialize motor pins as PWM speed outputs (1000 Hz, 8-bit resolution)
  ledcAttach(rightMotor.pinIN1, 1000, 8);
  ledcAttach(rightMotor.pinIN2, 1000, 8);
  ledcAttach(leftMotor.pinIN1, 1000, 8);
  ledcAttach(leftMotor.pinIN2, 1000, 8);
  
  // Ensure the car starts in a parked state
  stopCar();

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

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t *s = esp_camera_sensor_get();
  
if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);        
    
    // 1. Brightness & Saturation
    s->set_brightness(s, 0);   // Reset to 0. It is already overexposing, don't force it higher!
    s->set_saturation(s, -2);  // Keep this low to suppress the red bleed
    
    // 2. White Balance
    s->set_whitebal(s, 1);     // Auto White Balance ON
    s->set_awb_gain(s, 1);     // AWB Gain ON
    s->set_wb_mode(s, 0);      // Set back to Auto for now to let the DSP work

    // 3. THE DEEP CALIBRATION (The Missing Pieces)
    s->set_lenc(s, 1);         // Lens Correction ON (Fixes pink color fringing)
    s->set_raw_gma(s, 1);      // Raw Gamma ON (Fixes the blown-out, overly bright exposure)
    s->set_dcw(s, 1);          // Downsize Center Weight ON (Helps the camera meter light correctly)
    s->set_bpc(s, 1);          // Black Pixel Correction ON
    s->set_wpc(s, 1);          // White Pixel Correction ON
  }

  // --- THE AUTO-PILOT TUNE ---
  s->set_exposure_ctrl(s, 1); // Auto-Exposure ON (adapts to shadows/sunlight)
  s->set_aec2(s, 1);          // Advanced Auto-Exposure DSP ON
  s->set_whitebal(s, 1);      // Auto-White Balance ON (removes weird color tints)
  s->set_awb_gain(s, 1);      // Auto-White Balance Gain ON
  s->set_wb_mode(s, 0);       // Set White Balance Mode to standard Auto

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
  setupLedFlash();
#endif

  // --- Open Access Point (No Password) ---
  WiFi.softAP(carSSID, NULL); // Using NULL creates an open network
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