# Smart Environmental Monitoring System 🌍

IoT environmental monitoring with ESP8266, DHT11, BMP280, MQ135 sensors + Blynk cloud integration.

## 📊 Features

- Temperature, Humidity, Pressure, Altitude monitoring
- Air Quality measurement (MQ135)
- Real-time Blynk cloud dashboard
- Mobile app support (iOS/Android)

## 🔧 Hardware

- ESP8266 NodeMCU
- DHT11 (Temperature/Humidity)
- BMP280 (Pressure/Altitude) - I2C
- MQ135 (Air Quality) - Analog

## 🔌 Circuit Wiring

```
DHT11: D3 (GPIO0) → Data, 3.3V, GND
BMP280: D1 (GPIO5) SCL, D2 (GPIO4) SDA → I2C, 3.3V, GND
MQ135: A0 → Analog, 3.3V, GND
```

See **circuit.png** for detailed diagram.

## 📁 Files

- **src/Smart_Environmental_Monitoring.ino** - Arduino code (600+ lines)
- **circuit.png** - Hardware wiring diagram
- **web_output.png** - Blynk dashboard screenshot

## ⚡ Quick Start

1. Copy code from `src/Smart_Environmental_Monitoring.ino` to Arduino IDE
2. Update WiFi credentials and Blynk auth token
3. Install libraries: Blynk, DHT, Adafruit BMP280
4. Upload to ESP8266
5. Open Blynk app to monitor data

## 📱 Blynk Virtual Pins

| Pin | Sensor | Unit |
|-----|--------|------|
| V0 | Temperature | °C |
| V1 | Humidity | % |
| V2 | Pressure | hPa |
| V3 | Altitude | m |
| V4 | Air Quality | PPM |

## 📖 Setup Guide

See `docs/SETUP_GUIDE.md` for detailed instructions.

## 🔗 Resources

- [Blynk Docs](https://docs.blynk.io)
- [ESP8266 Docs](https://arduino-esp8266.readthedocs.io)

---

**Monitor environmental data in real-time!** 🚀
