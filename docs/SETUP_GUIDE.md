# Setup Guide - Smart Environmental Monitoring System

## 📋 Prerequisites

Before starting, ensure you have:
- ESP8266 NodeMCU board
- DHT11 temperature/humidity sensor
- BMP280 pressure/altitude sensor
- MQ135 air quality sensor
- USB cable for programming
- Computer with Arduino IDE installed

## 🔧 Hardware Setup

### Step 1: Connect DHT11 Sensor

| DHT11 Pin | ESP8266 Pin | Connection |
|-----------|-------------|------------|
| VCC       | 3.3V        | Power      |
| DATA      | D3 (GPIO0)  | Data Line  |
| GND       | GND         | Ground     |

**Note**: Add a 10kΩ pull-up resistor between DATA and VCC pins

### Step 2: Connect BMP280 Sensor (I2C)

| BMP280 Pin | ESP8266 Pin | Connection |
|-----------|-------------|------------|
| VCC       | 3.3V        | Power      |
| GND       | GND         | Ground     |
| SCL       | D1 (GPIO5)  | Clock      |
| SDA       | D2 (GPIO4)  | Data       |

### Step 3: Connect MQ135 Sensor

| MQ135 Pin | ESP8266 Pin | Connection |
|-----------|-------------|------------|
| VCC       | 3.3V        | Power      |
| GND       | GND         | Ground     |
| AO        | A0          | Analog In  |

## 💻 Software Installation

### Step 1: Install Arduino IDE

1. Download from https://www.arduino.cc/en/software
2. Install for your operating system

### Step 2: Add ESP8266 Support

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Paste this URL in "Additional Boards Manager URLs":
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
4. Click **Tools → Board: "..." → Boards Manager**
5. Search for "ESP8266" and install the latest version

### Step 3: Install Required Libraries

1. Go to **Sketch → Include Library → Manage Libraries**
2. Search and install each library:
   - **Blynk** (by Volodymyr Shymanskyy) - v1.0.0+
   - **DHT sensor library** (by Adafruit)
   - **Adafruit Unified Sensor** (by Adafruit)
   - **Adafruit BMP280 Library** (by Adafruit)

### Step 4: Select Board and Port

1. **Tools → Board → ESP8266 Boards → NodeMCU 1.0 (ESP-12E Module)**
2. **Tools → Port → COM3** (or your board's COM port)

## 🌐 Blynk IoT Cloud Setup

### Step 1: Create Blynk Account

1. Go to https://blynk.cloud/
2. Sign up with email
3. Verify your email

### Step 2: Create Template

1. Go to **Developer Zone → Templates**
2. Click **Create Template**
3. Fill in:
   - **Name**: Smart Environmental Monitoring System
   - **Hardware**: ESP8266
   - **Connection**: WiFi

### Step 3: Set Up Virtual Pins

In template, click **Datastreams** and create:

| Virtual Pin | Name | Data Type | Min | Max |
|------------|------|-----------|-----|-----|
| V0 | Temperature | Double | -10 | 50 |
| V1 | Humidity | Double | 0 | 100 |
| V2 | Pressure | Double | 300 | 1100 |
| V3 | Altitude | Double | -500 | 10000 |
| V4 | Air Quality | Integer | 0 | 1000 |

### Step 4: Get Credentials

1. Go to **Developer Zone → Templates**
2. Click your template name
3. Copy:
   - **Template ID**
   - **Template Name**

### Step 5: Create Device

1. Go to **My Devices**
2. Click **Create Device**
3. Select your template
4. Choose **From Template**
5. Note the **Auth Token**

## 📝 Code Configuration

### Update WiFi Credentials

1. Open `src/Smart_Environmental_Monitoring.ino`
2. Find these lines (near top):
   ```cpp
   char ssid[] = "YOUR_WIFI_NAME";
   char pass[] = "YOUR_WIFI_PASSWORD";
   ```
3. Replace with your WiFi details:
   ```cpp
   char ssid[] = "MyWiFi";
   char pass[] = "MyPassword123";
   ```

### Update Blynk Credentials

1. Find these lines:
   ```cpp
   #define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
   #define BLYNK_TEMPLATE_NAME "Smart Environmental Monitoring System"
   #define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
   ```
2. Replace with your Blynk credentials:
   ```cpp
   #define BLYNK_TEMPLATE_ID "TMPxxxxxxx"
   #define BLYNK_TEMPLATE_NAME "Smart Environmental Monitoring System"
   #define BLYNK_AUTH_TOKEN "AuthTokenHere"
   ```

## ⬆️ Upload Code

1. Connect ESP8266 to computer via USB
2. In Arduino IDE: **Sketch → Upload** (or press Ctrl+U)
3. Wait for "Uploading..." message
4. Look for "Hard resetting via RTS pin" confirmation

## 🔍 Verify Installation

### Check Serial Monitor

1. **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. Press ESP8266 reset button
4. Should see startup messages:
   ```
   ========================================
   SMART ENVIRONMENTAL MONITORING SYSTEM
   ========================================
   Initializing...
   Initializing DHT11 sensor...
   ✓ DHT11 initialized successfully
   Initializing BMP280 sensor...
   ✓ BMP280 initialized successfully
   Connecting to WiFi...
   ✓ WiFi connected successfully
   ```

### Troubleshooting Serial Messages

| Message | Cause | Solution |
|---------|-------|----------|
| BMP280 not found | I2C connection issue | Check SCL/SDA connections |
| DHT sensor read failed | Sensor malfunction | Check DATA pin connection |
| WiFi connection failed | Wrong credentials | Verify SSID/password |
| Blynk connection failed | Network/token issue | Check auth token |

## 📱 Mobile App Setup

### iOS/Android

1. Download **Blynk IoT** from App Store/Play Store
2. Log in with your account
3. Select **Smart Environmental Monitoring System** device
4. Dashboard shows real-time sensor data

### Create Custom Dashboard

1. Tap **+** to add widget
2. For each sensor:
   - Select **Gauge** or **Value Display**
   - Assign to corresponding Virtual Pin (V0-V4)
   - Set min/max values

## 🔄 Data Update Interval

Data is sent to Blynk every **2 seconds** (can be adjusted in code):

```cpp
timer.setInterval(2000L, sendData);  // 2000ms = 2 seconds
```

To change interval:
- 1000L = 1 second
- 5000L = 5 seconds
- 10000L = 10 seconds

## ✅ Verification Checklist

- [ ] Arduino IDE installed
- [ ] ESP8266 board support added
- [ ] All libraries installed
- [ ] Hardware connections verified
- [ ] Blynk account created
- [ ] WiFi credentials updated in code
- [ ] Blynk credentials updated in code
- [ ] Code uploaded successfully
- [ ] Serial monitor shows proper messages
- [ ] Blynk app shows sensor data
- [ ] Mobile app displays real-time data

## 📞 Support

If you encounter issues, check:
1. Serial monitor output for errors
2. [Troubleshooting Guide](TROUBLESHOOTING.md)
3. [Blynk Documentation](https://docs.blynk.io)
4. Component datasheets in `docs/` folder

---

**Ready to monitor!** 🎉
