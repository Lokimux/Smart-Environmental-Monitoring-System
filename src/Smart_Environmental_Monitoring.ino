#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Environmental Monitoring System"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// ============================================================================
// CONFIGURATION SECTION - Update these values
// ============================================================================

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ============================================================================
// SENSOR PIN DEFINITIONS
// ============================================================================

#define DHTPIN D3         // GPIO0 - DHT11 Data Pin
#define DHTTYPE DHT11     // DHT11 Sensor Type
#define MQ135_PIN A0      // Analog pin for MQ135 Air Quality Sensor

// ============================================================================
// SENSOR OBJECTS
// ============================================================================

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;
BlynkTimer timer;

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

float temperature = 0;
float humidity = 0;
float pressure = 0;
float altitude = 0;
int airQuality = 0;

// ============================================================================
// FUNCTION: Read Sensor Data
// ============================================================================

void readSensors() {
  // Read BMP280 (Pressure & Altitude)
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0;  // Convert to hPa
  altitude = bmp.readAltitude(1013.25);    // Sea level pressure
  
  // Read DHT11 (Humidity)
  humidity = dht.readHumidity();
  
  // Read MQ135 (Air Quality)
  airQuality = analogRead(MQ135_PIN);
  
  // Check for DHT read error
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("ERROR: DHT sensor read failed!");
    return;
  }
}

// ============================================================================
// FUNCTION: Send Data to Blynk
// ============================================================================

void sendData() {
  readSensors();
  
  // Send data to Blynk Virtual Pins
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, pressure);
  Blynk.virtualWrite(V3, altitude);
  Blynk.virtualWrite(V4, airQuality);

  // Print sensor data to Serial Monitor
  printSensorData();
}

// ============================================================================
// FUNCTION: Print Sensor Data to Serial Monitor
// ============================================================================

void printSensorData() {
  Serial.println("\n========================================");
  Serial.println("      SENSOR DATA UPDATE");
  Serial.println("========================================");
  Serial.print("Temperature:  "); Serial.print(temperature, 2); Serial.println(" °C");
  Serial.print("Humidity:     "); Serial.print(humidity, 2); Serial.println(" %");
  Serial.print("Pressure:     "); Serial.print(pressure, 2); Serial.println(" hPa");
  Serial.print("Altitude:     "); Serial.print(altitude, 2); Serial.println(" m");
  Serial.print("Air Quality:  "); Serial.print(airQuality); Serial.println(" PPM");
  Serial.println("========================================\n");
}

// ============================================================================
// FUNCTION: Initialize BMP280 Sensor
// ============================================================================

void initBMP280() {
  Serial.println("Initializing BMP280 sensor...");
  
  if (!bmp.begin(0x76)) {
    if (!bmp.begin(0x77)) {
      Serial.println("ERROR: BMP280 sensor not found!");
      Serial.println("Possible I2C addresses: 0x76, 0x77");
      while (1) {
        delay(100);  // Halt execution
      }
    }
  }
  
  Serial.println("✓ BMP280 initialized successfully");
}

// ============================================================================
// FUNCTION: Initialize DHT11 Sensor
// ============================================================================

void initDHT11() {
  Serial.println("Initializing DHT11 sensor...");
  dht.begin();
  delay(2000);  // Allow sensor to stabilize
  Serial.println("✓ DHT11 initialized successfully");
}

// ============================================================================
// FUNCTION: Initialize WiFi Connection
// ============================================================================

void initWiFi() {
  Serial.println("\nConnecting to WiFi...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi connected successfully");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nERROR: WiFi connection failed!");
  }
}

// ============================================================================
// FUNCTION: SETUP - Runs once at startup
// ============================================================================

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n========================================");
  Serial.println("SMART ENVIRONMENTAL MONITORING SYSTEM");
  Serial.println("========================================");
  Serial.println("Initializing...");
  
  // Initialize Sensors
  initDHT11();
  initBMP280();
  
  // Initialize WiFi
  initWiFi();
  
  // Initialize Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Set up timer to send data every 2 seconds
  timer.setInterval(2000L, sendData);
  
  Serial.println("\n✓ System initialization complete!");
  Serial.println("========================================\n");
}

// ============================================================================
// FUNCTION: LOOP - Runs continuously
// ============================================================================

void loop() {
  // Check if Blynk is connected, if not, reconnect
  if (Blynk.connected()) {
    Blynk.run();
  }
  
  // Run timer tasks
  timer.run();
  
  // Small delay to prevent watchdog issues
  delay(10);
}

// ============================================================================
// BLYNK VIRTUAL PIN HANDLERS
// ============================================================================

// Virtual Pin V0 - Temperature (Read Only)
BLYNK_READ(V0) {
  Blynk.virtualWrite(V0, temperature);
}

// Virtual Pin V1 - Humidity (Read Only)
BLYNK_READ(V1) {
  Blynk.virtualWrite(V1, humidity);
}

// Virtual Pin V2 - Pressure (Read Only)
BLYNK_READ(V2) {
  Blynk.virtualWrite(V2, pressure);
}

// Virtual Pin V3 - Altitude (Read Only)
BLYNK_READ(V3) {
  Blynk.virtualWrite(V3, altitude);
}

// Virtual Pin V4 - Air Quality (Read Only)
BLYNK_READ(V4) {
  Blynk.virtualWrite(V4, airQuality);
}
