# 🚗 CAN-Based Automotive Dashboard

> An Embedded C project that implements a **CAN-based automotive dashboard using three PIC18F4580 ECUs**, where vehicle parameters such as Speed, Gear, RPM, and Indicator status are collected, transmitted through CAN, and displayed on the dashboard.

---

## 📝 About the Project

The **CAN-Based Automotive Dashboard** project demonstrates communication between multiple Electronic Control Units (ECUs) using the **Controller Area Network (CAN)** protocol.

The system consists of three PIC18F4580 ECUs:

- 🚗 **ECU1** – Handles Speed and Gear
- 🔄 **ECU2** – Handles RPM and Indicator
- 📺 **ECU3** – Acts as the Dashboard ECU

ECU1 collects Speed and Gear information, while ECU2 collects RPM and Indicator information. The collected data is transmitted through the CAN bus to ECU3.

ECU3 receives the CAN messages, identifies the message using the CAN ID, processes the data, and displays the vehicle information on a Character LCD.

---

## ✨ Features

- 🚗 Speed monitoring
- ⚙️ Gear monitoring
- 🔄 RPM monitoring using ADC
- 💡 Left and Right indicator control
- 🚨 Hazard indicator control
- 📡 CAN communication between multiple ECUs
- 📺 Character LCD dashboard display
- 💡 Indicator LED control
- ⏱️ Timer0 interrupt for indicator blinking
- 🆔 Separate CAN message IDs for different vehicle parameters
- 🔧 PIC18F4580 based embedded system
- 💻 Embedded C programming
- 🔌 GPIO, ADC, CAN and LCD interfacing

---

## 🏗️ System Architecture

```text
                         🚗 CAN-Based Automotive Dashboard
                                      │
                 ┌────────────────────┼────────────────────┐
                 │                    │                    │
                 ▼                    ▼                    ▼
          ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
          │    ECU1     │      │    ECU2     │      │    ECU3     │
          │             │      │             │      │             │
          │ Speed       │      │ RPM         │      │ Dashboard   │
          │ Gear        │      │ Indicator   │      │             │
          └──────┬──────┘      └──────┬──────┘      └──────┬──────┘
                 │                    │                    │
                 └────────────────────┼────────────────────┘
                                      │
                                  📡 CAN BUS
                                      │
                                      ▼
                              📺 Character LCD
                              💡 Indicator LEDs
