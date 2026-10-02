# 🚗 CAN-Based Automotive Dashboard

A **CAN-based automotive dashboard system** developed using **PIC18F4580 microcontrollers** and **Embedded C**.

The system uses **three ECUs** that communicate with each other through the **CAN protocol**. Vehicle parameters such as **Speed, Gear, RPM, and Indicator status** are transmitted over CAN and displayed on a Character LCD.

---

## 📌 Project Overview

The project is designed using a **3-ECU architecture**:

- 🚘 **ECU1** – Handles Speed and Gear
- ⚙️ **ECU2** – Handles RPM and Indicator
- 📟 **ECU3** – Receives CAN data and displays the information on the dashboard

All ECUs communicate using the **CAN (Controller Area Network)** protocol.

---

## 🏗️ System Architecture

```text
                    ┌─────────────────────┐
                    │       ECU 1         │
                    │  Speed + Gear       │
                    └──────────┬──────────┘
                               │
                               │ CAN
                               ▼
                    ┌─────────────────────┐
                    │       ECU 3         │
                    │   Dashboard ECU     │
                    │                     │
                    │  Character LCD      │
                    │  Speed / Gear       │
                    │  RPM / Indicator    │
                    └──────────▲──────────┘
                               │
                               │ CAN
                               │
                    ┌──────────┴──────────┐
                    │       ECU 2         │
                    │  RPM + Indicator    │



ECU Responsibilities
ECU	Function
🚘 ECU1	Reads vehicle speed and gear information and transmits it through CAN
⚙️ ECU2	Reads RPM and indicator information and transmits it through CAN
📟 ECU3	Receives CAN messages and displays vehicle information on the dashboard
🆔 CAN Message IDs
Parameter	CAN ID
🚗 Speed	0x10
⚙️ Gear	0x20
🔄 RPM	0x30
💡 Indicator	0x40

The CAN messages use standard CAN identifiers.

🔄 CAN Communication Flow
Speed ──────┐
            │
Gear ───────┤
            │
            ▼
         CAN BUS
            │
RPM ────────┤
            │
Indicator ──┘
            │
            ▼
        Dashboard
            │
            ▼
      Character LCD
⚙️ How It Works
🚘 ECU1 – Speed and Gear
Reads speed information using ADC.
Converts the ADC value into the required speed range.
Reads the selected gear.
Transmits Speed and Gear information through CAN.
⚙️ ECU2 – RPM and Indicator
Reads RPM information using ADC.
Converts the ADC value into the required RPM range.
Handles indicator selection.
Transmits RPM and Indicator information through CAN.
📟 ECU3 – Dashboard

ECU3 continuously receives CAN messages and processes them according to their CAN IDs.

The received information is displayed on the Character LCD:

Speed : 75 km/h
Gear  : G3
RPM   : 3500
Ind   : <- 
📊 Data Processing
🚗 Speed

The ADC value is converted into a speed value from 0 to 100.

Speed = ADC Value × 100 / 1023
🔄 RPM

The ADC value is converted into an RPM value from 0 to 6000.

RPM = ADC Value × 6000 / 1023
⚙️ Gear

Gear information is represented using:

0 → GN
1 → G1
2 → G2
3 → G3
4 → G4
5 → G5
6 → GR
7 → _C
💡 Indicator System

The indicator status is received through CAN and displayed on the dashboard.

Value	Indicator
0	← Left
1	→ Right
2	↔ Hazard
3	OFF

The indicator LEDs are controlled using GPIO and blinking is handled using Timer0.

📟 Dashboard Display

ECU3 displays the received vehicle information on a Character LCD.

The dashboard provides:

🚗 Vehicle Speed
⚙️ Current Gear
🔄 Engine RPM
💡 Indicator Status
📡 CAN Communication

The CAN communication is implemented using the PIC18F4580 ECAN module.

CAN Configuration
Microcontroller: PIC18F4580
Communication: CAN
Mode: Normal Mode
CAN IDs: Standard IDs
CAN TX: RB2
CAN RX: RB3
Clock: 8 MHz
⏱️ Timer0 – Indicator Blinking

Timer0 is used to generate the timing required for indicator blinking.

8-bit Timer0
Internal clock
No prescaler
Timer reload value is used in the interrupt
Blink state is toggled periodically

This allows the left, right, and hazard indicators to blink on the dashboard.

📁 Project Structure
CAN-based-Automotive-Dashboard/
│
├── ECU1/
│   ├── main.c
│   ├── ...
│   └── ...
│
├── ECU2/
│   ├── main.c
│   ├── ...
│   └── ...
│
├── ECU3/
│   ├── main.c
│   ├── can.c
│   ├── can.h
│   ├── clcd.c
│   ├── clcd.h
│   ├── timer.c
│   ├── timer.h
│   └── ...
│
└── README.md
🧩 Technologies Used
Category	Technologies
💻 Programming	Embedded C
🔧 Microcontroller	PIC18F4580
📡 Communication	CAN
📟 Display	Character LCD
🎛️ Input	ADC
⏱️ Timer	Timer0
🔌 GPIO	Digital I/O
🛠️ IDE	MPLAB X IDE
🔁 Complete Program Flow
        Start
          │
          ▼
   Initialize ECUs
          │
          ▼
   Read Vehicle Data
          │
          ▼
      Create CAN
       Messages
          │
          ▼
    Transmit over
       CAN Bus
          │
          ▼
       ECU3
      Receives
       Messages
          │
          ▼
    Identify CAN ID
          │
          ▼
    Process Received
        Data
          │
          ▼
   Display on LCD
          │
          ▼
   Control Indicators
          │
          ▼
        Repeat
🖥️ Example Dashboard Output
--------------------
 Speed : 75
 Gear  : G3
 RPM   : 3500
 Ind   : <-
--------------------

The displayed values change according to the data received from the other ECUs through the CAN bus.

🎯 Key Learning

Through this project, I gained practical experience in:

🔹 CAN protocol and ECU-to-ECU communication
🔹 PIC18F4580 microcontroller
🔹 Embedded C programming
🔹 ADC interfacing
🔹 Character LCD interfacing
🔹 GPIO configuration
🔹 Timer0 and interrupt handling
🔹 CAN message transmission and reception
🔹 Multi-ECU system architecture
🔹 Real-time data processing
✅ Result

Successfully developed a 3-ECU CAN-based automotive dashboard system in which vehicle parameters are transmitted between ECUs using CAN and displayed on a Character LCD.

👤 Author

Sk Shabeena

📧 Email: skshabeena33@gmail.com
💼 LinkedIn: Shaik Shabeena
🐙 GitHub: shabeena1703
                    └─────────────────────┘
