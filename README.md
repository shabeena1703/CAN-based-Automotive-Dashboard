# 🚗 CAN-Based Automotive Dashboard

A **CAN-based automotive dashboard system** developed using **PIC18F4580 microcontrollers** and **Embedded C**.

The system consists of **three ECUs** communicating through the **CAN (Controller Area Network)** protocol. Vehicle parameters such as **Speed, Gear, RPM, and Indicator status** are transmitted over CAN and displayed on a Character LCD.

---

## 📌 Project Overview

The project follows a **3-ECU architecture**, where each ECU performs a specific function.

- 🚘 **ECU1** – Handles Speed and Gear
- ⚙️ **ECU2** – Handles RPM and Indicator
- 📟 **ECU3** – Receives CAN data and displays the information on the dashboard

All three ECUs communicate through the **CAN bus**.

---

## 🏗️ System Architecture

```text
                  ┌─────────────────────┐
                  │       ECU1          │
                  │    Speed + Gear     │
                  └──────────┬──────────┘
                             │
                             │ CAN BUS
                             ▼
                  ┌─────────────────────┐
                  │       ECU3          │
                  │   Dashboard ECU     │
                  │                     │
                  │   Character LCD     │
                  │ Speed / Gear / RPM  │
                  │     Indicator       │
                  └──────────▲──────────┘
                             │
                             │ CAN BUS
                             │
                  ┌──────────┴──────────┐
                  │       ECU2          │
                  │   RPM + Indicator   │
                  └─────────────────────┘

---

##🔧 ECU Responsibilities

ECU	Responsibility
🚘 ECU1	Reads Speed and Gear information and transmits it through CAN
⚙️ ECU2	Reads RPM and Indicator information and transmits it through CAN
📟 ECU3	Receives CAN messages and displays Speed, Gear, RPM, and Indicator status
🆔 CAN Message IDs

Parameter	CAN ID
🚗 Speed	0x10
⚙️ Gear	0x20
🔄 RPM	0x30
💡 Indicator	0x40

The project uses standard CAN identifiers for communication between the ECUs.

---

##🔄 CAN Communication Flow
       Speed ───────┐
                    │
       Gear ────────┤
                    │
                    ▼
                 CAN BUS
                    │
       RPM ─────────┤
                    │
       Indicator ───┘
                    │
                    ▼
              Dashboard ECU
                  ECU3
                    │
                    ▼
             Character LCD

---

##⚙️ How the System Works
**🚘 ECU1 – Speed and Gear**
Speed information is obtained using ADC.
The ADC value is converted into the required speed range.
Gear information is obtained.
Speed and Gear data are packed into CAN messages.
The messages are transmitted through the CAN bus.

**⚙️ ECU2 – RPM and Indicator**
RPM information is obtained using ADC.
The ADC value is converted into the required RPM range.
Indicator status is handled.
RPM and Indicator data are transmitted through CAN.

**📟 ECU3 – Dashboard**
ECU3 continuously checks for incoming CAN messages.
The CAN ID is identified.
The corresponding data is extracted.
Speed, Gear, RPM, and Indicator information are processed.
The processed information is displayed on the Character LCD.
GPIO and Timer0 are used to control indicator blinking.

---

##📊 Data Processing
**🚗 Speed Calculation**

The ADC value is converted into a speed value from 0 to 100.

Speed = ADC Value × 100 / 1023

**🔄 RPM Calculation**

The ADC value is converted into an RPM value from 0 to 6000.

RPM = ADC Value × 6000 / 1023

**⚙️ Gear Mapping**

The gear information is represented using the following values:

Value	Gear
0	GN
1	G1
2	G2
3	G3
4	G4
5	G5
6	GR
7	_C
**💡 Indicator System**

The indicator status is received through CAN.

Value	Indicator
0	← Left
1	→ Right
2	↔ Hazard
3	OFF

The indicator LEDs are controlled using GPIO, while Timer0 is used to generate the blinking operation.

**📟 Dashboard Display**

ECU3 displays the received vehicle information on a Character LCD.

The dashboard displays:

🚗 Vehicle Speed
⚙️ Current Gear
🔄 Engine RPM
💡 Indicator Status
Example Display
┌────────────────────┐
│ Speed : 75 km/h    │
│ Gear  : G3         │
│ RPM   : 3500       │
│ Ind   : <-         │
└────────────────────┘

---

##📡 CAN Communication

The project uses the ECAN module of the PIC18F4580 for communication.

CAN Configuration
Parameter	Configuration
Microcontroller	PIC18F4580
Communication Protocol	CAN
CAN Mode	Normal Mode
Identifier Type	Standard CAN ID
CAN TX	RB2
CAN RX	RB3
Clock Frequency	8 MHz
⏱️ Timer0 – Indicator Blinking

Timer0 is used to generate the timing required for indicator blinking.

Timer0 Configuration
8-bit Timer0
Internal clock
No prescaler
Timer reload inside the interrupt
Blink state toggled periodically

This allows the left, right, and hazard indicators to blink according to the selected indicator mode.

---

##📁 Project Structure
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

---

🧩 Technologies Used
Category	Technology
💻 Programming Language	Embedded C
🔧 Microcontroller	PIC18F4580
📡 Communication	CAN
📟 Display	Character LCD
🎛️ Input	ADC
⏱️ Timer	Timer0
🔌 Hardware Interface	GPIO
🛠️ IDE	MPLAB X IDE
🔁 Complete Program Flow
                    ┌───────────────┐
                    │     START     │
                    └───────┬───────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Initialize ECUs  │
                  │ CAN / LCD / ADC  │
                  │ Timer / GPIO     │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Read Vehicle Data │
                  │ Speed / Gear /     │
                  │ RPM / Indicator   │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Create CAN        │
                  │ Messages          │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Transmit Data     │
                  │ through CAN Bus   │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │       ECU3        │
                  │ Receive CAN Data  │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Identify CAN ID   │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Process Received  │
                  │ Data              │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Display Data on   │
                  │ Character LCD     │
                  └─────────┬─────────┘
                            │
                            ▼
                  ┌───────────────────┐
                  │ Control Indicator │
                  │ LEDs using GPIO   │
                  └─────────┬─────────┘
                            │
                            ▼
                         REPEAT
▶️ How to Run
1. Open the Projects

Open the corresponding ECU1, ECU2, and ECU3 projects in MPLAB X IDE.

2. Configure the Hardware

Connect the three PIC18F4580 ECUs through the CAN communication interface.

3. Build the Projects

For each ECU:

MPLAB X IDE
     ↓
Clean and Build Project
     ↓
Generate HEX file
4. Program the Microcontrollers

Program the generated HEX file into the respective PIC18F4580 microcontroller using a compatible programmer/debugger.

5. Connect the CAN Network

Connect the CAN TX and CAN RX lines between the ECUs through the CAN interface.

6. Power ON the System

After powering the ECUs:

ECU1 ──┐
       │
       ├── CAN BUS ──> ECU3
       │
ECU2 ──┘

ECU3 receives the transmitted data and displays the vehicle information on the Character LCD.

🖥️ Output

The dashboard displays the received values in real time.

Example 1 – Normal Operation
┌────────────────────┐
│ Speed : 75 km/h    │
│ Gear  : G3         │
│ RPM   : 3500       │
│ Ind   : OFF        │
└────────────────────┘
Example 2 – Left Indicator
┌────────────────────┐
│ Speed : 60 km/h    │
│ Gear  : G2         │
│ RPM   : 2800       │
│ Ind   : <-         │
└────────────────────┘
Example 3 – Hazard Indicator
┌────────────────────┐
│ Speed : 40 km/h    │
│ Gear  : G2         │
│ RPM   : 2200       │
│ Ind   : <->        │
└────────────────────┘

The displayed values change according to the data received from ECU1 and ECU2 through the CAN bus.

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
🔹 Standard CAN identifiers
🔹 Multi-ECU system architecture
🔹 Real-time data processing
✅ Result

Successfully developed a 3-ECU CAN-based automotive dashboard system using PIC18F4580 and Embedded C.

The system successfully transfers Speed, Gear, RPM, and Indicator information between multiple ECUs through CAN and displays the received information on a Character LCD.

👤 Author

Sk Shabeena

📧 Email: skshabeena33@gmail.com
💼 LinkedIn: Shaik Shabeena
🐙 GitHub: shabeena1703

