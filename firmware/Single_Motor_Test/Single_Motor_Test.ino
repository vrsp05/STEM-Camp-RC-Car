// --- Motor Hardware Isolation Test (Schematic Matched) ---

// Updated to match your coworker's schematic
const int pinIN1 = 13; 
const int pinIN2 = 12; 
const int testSpeed = 150; // Safe indoor testing speed (0-255)

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Motor Hardware Test...");

  // Initialize pins for PWM control (1000 Hz, 8-bit resolution)
  ledcAttach(pinIN1, 1000, 8);
  ledcAttach(pinIN2, 1000, 8);
  
  // Ensure motor starts stopped
  ledcWrite(pinIN1, 0);
  ledcWrite(pinIN2, 0);
  delay(2000); 
}

void loop() {
  // 1. Spin Direction A
  Serial.println("Spinning Direction A");
  ledcWrite(pinIN1, testSpeed);
  ledcWrite(pinIN2, 0);
  delay(2000);

  // 2. Hard Stop
  Serial.println("STOP");
  ledcWrite(pinIN1, 0);
  ledcWrite(pinIN2, 0);
  delay(1000);

  // 3. Spin Direction B (Reverse)
  Serial.println("Spinning Direction B");
  ledcWrite(pinIN1, 0);
  ledcWrite(pinIN2, testSpeed);
  delay(2000);

  // 4. Hard Stop
  Serial.println("STOP");
  ledcWrite(pinIN1, 0);
  ledcWrite(pinIN2, 0);
  delay(3000); 
}