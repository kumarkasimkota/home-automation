/*
 * ESP32 Light Control - Simple On/Off
 * 
 * This code controls a light (LED/relay) connected to ESP32
 * Press button to toggle light on/off
 */

// Pin definitions
const int LED_PIN = 2;        // Built-in LED or connect external light/relay here
const int BUTTON_PIN = 4;     // Connect button to GPIO 4

// Variables
bool lightState = false;      // Current state of light (false = off, true = on)
bool lastButtonState = HIGH;  // Previous button state
bool currentButtonState;      // Current button reading
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // Debounce time in milliseconds

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
  
  // Initialize light to OFF
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("ESP32 Light Control Ready!");
  Serial.println("Press button to toggle light");
}

void loop() {
  // Read the button state
  int reading = digitalRead(BUTTON_PIN);
  
  // Check if button state changed (with debouncing)
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If button state has been stable for debounce period
    if (reading != currentButtonState) {
      currentButtonState = reading;
      
      // If button is pressed (LOW because of INPUT_PULLUP)
      if (currentButtonState == LOW) {
        // Toggle light state
        lightState = !lightState;
        digitalWrite(LED_PIN, lightState ? HIGH : LOW);
        
        // Print status to serial monitor
        Serial.print("Light turned ");
        Serial.println(lightState ? "ON" : "OFF");
      }
    }
  }
  
  lastButtonState = reading;
}
