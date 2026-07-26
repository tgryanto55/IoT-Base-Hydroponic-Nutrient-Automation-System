# 🌱 IoT-Based Hydroponic Nutrient Automation System

An Internet of Things (IoT) project that automates hydroponic nutrient management using **ESP32**, **TDS Sensor**, **pH Sensor**, **Blynk IoT**, and **Google Sheets**. The system continuously monitors nutrient concentration and pH while automatically maintaining the desired TDS level.

> Final Year Project (Bachelor Thesis)

---

## 📖 Overview

Managing hydroponic nutrient solutions manually is time-consuming and prone to human error. This project provides an automated solution capable of:

- Real-time monitoring of TDS and pH values
- Automatic nutrient dosing
- Automatic water refill when nutrient concentration is too high
- Remote monitoring through Blynk Mobile
- Cloud data logging using Google Sheets

---

## ✨ Features

- 📊 Real-time TDS monitoring
- 🧪 Real-time pH monitoring
- ⚙️ Automatic nutrient dosing (AB Mix)
- 💧 Automatic fresh water addition
- 📱 Mobile dashboard using Blynk IoT
- ☁️ Cloud data logging to Google Sheets
- 🔔 pH alert notifications
- 🌐 Wi-Fi connectivity using ESP32

---

## 🏗 System Architecture

### Input

- PH-4502C Sensor
- TDS Meter V1

### Processing

- ESP32 Microcontroller

### Output

- Peristaltic Pump (Nutrient A)
- Peristaltic Pump (Nutrient B)
- DC Water Pump

### Cloud Platform

- Blynk IoT
- Google Sheets

---

## 🔧 Hardware Components

| Component | Function |
|------------|----------|
| ESP32 | Main controller |
| PH-4502C | pH measurement |
| TDS Meter V1 | Nutrient concentration measurement |
| Relay Module | Pump control |
| Peristaltic Pumps | Nutrient dosing |
| DC Water Pump | Fresh water supply |
| Breadboard | Circuit connection |
| USB Type-C Breakout | External power source |

---

## 📌 Pin Configuration

| Device | ESP32 Pin |
|---------|-----------|
| pH Sensor | GPIO34 |
| TDS Sensor | GPIO32 |
| Relay Nutrient A | GPIO4 |
| Relay Nutrient B | GPIO2 |
| Relay Water Pump | GPIO15 |
| Relay TDS Power | GPIO16 |

---

## ⚙️ System Workflow

1. ESP32 reads TDS and pH sensors.
2. Data is sent to Blynk Cloud.
3. Sensor data is logged into Google Sheets.
4. Decision logic:
   - If TDS is below the minimum threshold → Activate Nutrient Pumps.
   - If TDS is above the maximum threshold → Activate Water Pump.
5. If pH is outside the ideal range (5.5–6.5), a notification is sent to the user.

---

## 📱 Mobile Dashboard

The project includes a custom dashboard built with **Blynk IoT** to display:

- TDS Value
- pH Value
- Pump Status
- System Status
- Notification Alerts

---

## ☁️ Data Logging

Sensor data is automatically stored in **Google Sheets** using HTTP POST requests via Google Apps Script.

Recorded data includes:

- Timestamp
- TDS
- pH
- Pump Status

---

## 🛠 Development Tools

- Arduino IDE
- ESP32 Board Package
- Blynk IoT
- Google Apps Script
- Google Sheets

---

## 📂 Project Structure

```
.
├── firmware.ino
├── README.md
└── Technical Documentation.pdf

```

---

## 🧪 Testing

The system has been tested for:

- ✅ Sensor initialization
- ✅ Automatic nutrient dosing
- ✅ Automatic water refill
- ✅ pH notification system
- ✅ Google Sheets data logging
- ✅ Wi-Fi communication

---

## 📸 Project Gallery

You can add screenshots here:

- Hardware Prototype
- Wiring Diagram
- Blynk Dashboard
- Google Sheets Logging
- Testing Process

---

## 🚀 Future Improvements

- Automatic pH adjustment
- Web Dashboard
- OTA Firmware Update
- Machine Learning for nutrient prediction
- Multi-tank monitoring
- Solar-powered operation

---

## 🎥 Demo

**Video Demo**

> https://www.youtube.com/watch?v=Mfc2Rc4_AZg

---

## 📄 Documentation

Technical documentation is available in the `Technical Documentation (IDN)` PDF file.

---

## 👨‍💻 Author

**Tegar Riyanto**

Bachelor of Computer Engineering

---

## 📜 License

This project is intended for educational and portfolio purposes.
