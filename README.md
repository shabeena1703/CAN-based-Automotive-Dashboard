# 🚗 CAN-Based Automotive Dashboard

> A multi-ECU automotive dashboard project using CAN communication to monitor and display **Speed, Gear, RPM, and Indicator status**.

---

## 📝 About the Project

This project implements a **CAN-Based Automotive Dashboard** using **three PIC18F4580 ECUs**.

Each ECU performs a specific function and communicates with the other ECUs through the **CAN protocol**.

The dashboard ECU receives the vehicle information through CAN and displays the data on a **Character LCD**.

```text
                  ┌─────────────────────┐
                  │       ECU 1         │
                  │   🚗 Speed + Gear   │
                  └──────────┬──────────┘
                             │
                             │ CAN
                             ▼
                  ┌─────────────────────┐
                  │       ECU 3         │
                  │    📺 Dashboard     │
                  │                     │
                  │ Speed               │
                  │ Gear                │
                  │ RPM                 │
                  │ Indicator           │
                  └──────────┬──────────┘
                             ▲
                             │ CAN
                             │
                  ┌──────────┴──────────┐
                  │       ECU 2         │
                  │   🔄 RPM + Indicator│
                  └─────────────────────┘
```

---

## ✨ Features

- 🚗 Speed monitoring
- ⚙️ Gear monitoring
- 🔄 RPM monitoring
- ↔️ Left and right indicator control
- 🚨 Hazard indicator support
- 📡 CAN communication between multiple ECUs
- 📺 Real-time dashboard display
- 💡 Indicator LED control
- ⏱️ Timer0-based indicator blinking
- 🔧 Register-level Embedded C programming

---

## 🧠 How It Works

The project is divided into **three ECUs**, where each ECU performs a specific task.

### 🚗 ECU 1 – Speed and Gear

ECU 1 is responsible for:

- Reading speed input through ADC
- Reading gear selection
- Sending speed data through CAN
- Sending gear data through CAN

```text
Speed Input
     ↓
    ADC
     ↓
   ECU 1
     │
     ├──────── CAN ────────→ Speed
     │
Gear Input
     ↓
   ECU 1
     │
     └──────── CAN ────────→ Gear
```

### 🔄 ECU 2 – RPM and Indicator

ECU 2 is responsible for:

- Reading RPM through ADC
- Reading indicator selection
- Left indicator
- Right indicator
- Hazard indicator
- Indicator OFF
- Sending RPM and indicator information through CAN

```text
RPM Input
    ↓
   ADC
    ↓
  ECU 2
    │
    └──────── CAN ─────────→ RPM


Indicator Input
       ↓
     ECU 2
       │
       └────── CAN ────────→ Indicator
```

### 📺 ECU 3 – Dashboard

ECU 3 acts as the **dashboard ECU**.

It:

- 📡 Receives CAN messages
- 🔎 Identifies the message using CAN ID
- ⚙️ Processes the received data
- 📺 Displays Speed, Gear, RPM, and Indicator status
- 💡 Controls indicator LEDs
- ⏱️ Uses Timer0 for indicator blinking

```text
             CAN Messages
                  ↓
              ECU 3
                  ↓
          Identify CAN ID
                  ↓
        ┌─────────┼─────────┐
        ↓         ↓         ↓
      Speed      Gear       RPM
        │         │         │
        └─────────┼─────────┘
                  ↓
             Indicator
                  ↓
             LCD Display
                  +
           Indicator LEDs
```

---

## 📡 CAN Communication

The three ECUs communicate with each other using the **Controller Area Network (CAN)** protocol.

Each type of vehicle information is assigned a unique CAN message ID.

| 🚘 Parameter | 🆔 CAN Message ID |
|:------------:|:-----------------:|
| Speed        | `0x10`            |
| Gear         | `0x20`            |
| RPM          | `0x30`            |
| Indicator    | `0x40`            |

ECU 3 receives the CAN messages and processes them according to the **message ID**.

---

## 🚦 Speed Processing

The speed input is read using the ADC.

The ADC value is in the range:

```text
0 ─────────────────────── 1023
```

The ADC value is converted into a speed value in the range:

```text
0 ─────────────────────── 100 km/h
```

The converted speed is transmitted through CAN and displayed on the dashboard.

```text
ADC Input
    ↓
ADC Value
    ↓
CAN Transmission
    ↓
ECU 3
    ↓
Speed Conversion
    ↓
LCD Display
```

---

## ⚙️ Gear Processing

The gear information is transmitted as an index.

| 🔢 Index | ⚙️ Gear |
|:--------:|:-------:|
| `0`      | `GN`    |
| `1`      | `G1`    |
| `2`      | `G2`    |
| `3`      | `G3`    |
| `4`      | `G4`    |
| `5`      | `G5`    |
| `6`      | `GR`    |
| `7`      | `_C`    |

ECU 3 receives the gear index and converts it into the corresponding gear name before displaying it on the LCD.

```text
Gear Input
    ↓
Gear Index
    ↓
CAN Transmission
    ↓
ECU 3
    ↓
Gear String
    ↓
LCD Display
```

---

## 🔄 RPM Processing

RPM is obtained using the ADC.

The ADC value is converted into an RPM value in the range:

```text
0 ─────────────────────── 6000 RPM
```

The RPM value is then transmitted through CAN.

```text
RPM Input
    ↓
ADC
    ↓
RPM Value
    ↓
CAN
    ↓
ECU 3
    ↓
LCD Display
```

---

## 💡 Indicator Processing

The indicator system supports four states.

| 🔢 Value | 💡 Indicator State | 📺 LCD Display |
|:--------:|:------------------:|:--------------:|
| `0`      | Left               | `<-`           |
| `1`      | Right              | `->`           |
| `2`      | Hazard             | `<->`          |
| `3`      | OFF                | Blank          |

The indicator LEDs are controlled using GPIO.

| 💡 Indicator | 🔌 GPIO Pin |
|:------------:|:-----------:|
| Left LED     | `RB0`       |
| Right LED    | `RB7`       |

### ◀️ Left Indicator

```text
Left LED  → ON
Right LED → OFF
```

LCD:

```text
IND : <-
```

### ▶️ Right Indicator

```text
Left LED  → OFF
Right LED → ON
```

LCD:

```text
IND : ->
```

### 🚨 Hazard Indicator

```text
Left LED  → ON
Right LED → ON
```

LCD:

```text
IND : <->
```

### ⛔ Indicator OFF

```text
Left LED  → OFF
Right LED → OFF
```

LCD:

```text
IND :
```

---

## ⏱️ Timer0 and Indicator Blinking

Timer0 is used to generate the timing required for indicator blinking.

The Timer0 interrupt periodically updates the blink state.

```text
Timer0 Overflow
       ↓
   Interrupt
       ↓
     ISR
       ↓
 Update Counter
       ↓
 Toggle Blink
       ↓
Indicator ON / OFF
```

This allows the indicator LEDs to blink periodically while the selected indicator is active.

---

## 📺 Dashboard Display

ECU 3 displays the received vehicle information on a **Character LCD**.

### 🟢 Normal Condition

```text
--------------------
Speed : 75 km/h
Gear  : G3
RPM   : 3500
IND   : OFF
--------------------
```

### ◀️ Left Indicator

```text
--------------------
Speed : 60 km/h
Gear  : G2
RPM   : 2800
IND   : <-
--------------------
```

### ▶️ Right Indicator

```text
--------------------
Speed : 70 km/h
Gear  : G3
RPM   : 3200
IND   : ->
--------------------
```

### 🚨 Hazard Indicator

```text
--------------------
Speed : 40 km/h
Gear  : G2
RPM   : 2200
IND   : <->
--------------------
```

---

## 🔌 Hardware Configuration

### 📡 CAN Interface

| 🔌 Signal | 📍 Pin |
|:---------:|:------:|
| CAN TX    | `RB2`  |
| CAN RX    | `RB3`  |

### 📺 Character LCD

| 📺 LCD Signal | 📍 Pin |
|:-------------:|:------:|
| LCD Data      | `PORTD` |
| EN            | `RC2`  |
| RS            | `RC1`  |
| RW            | `RC0`  |
| Busy          | `RD7`  |

### 💡 Indicator LEDs

| 💡 Indicator | 📍 Pin |
|:------------:|:------:|
| Left LED     | `RB0`  |
| Right LED    | `RB7`  |

---

## 📁 Project Structure

```text
CAN-based-Automotive-Dashboard/
│
├── ECU1.X/
│   ├── main.c
│   ├── adc.c
│   ├── can.c
│   └── ...
│
├── ECU2.X/
│   ├── main.c
│   ├── adc.c
│   ├── can.c
│   ├── keypad.c
│   └── ...
│
├── ECU3.X/
│   ├── main.c
│   ├── can.c
│   ├── clcd.c
│   ├── isr.c
│   ├── timer.c
│   └── ...
│
└── README.md
```

---

## 🛠️ Technologies & Concepts

| 🛠️ Category | 💻 Technology / Concept |
|:------------:|:-----------------------:|
| Programming Language | Embedded C |
| Microcontroller | PIC18F4580 |
| Communication | CAN |
| Display | Character LCD |
| Analog Input | ADC |
| Timer | Timer0 |
| Interrupts | Timer0 Interrupt |
| I/O | GPIO |
| IDE | MPLAB X IDE |
| Compiler | XC8 |

---

## 🔄 Program Flow

```text
                         🚀 START
                            ↓
                  Initialize Peripherals
                            ↓
                     Initialize CAN
                            ↓
                  Initialize LCD/GPIO
                            ↓
                     Configure Timer0
                            ↓
                   Enable Interrupts
                            ↓
                    Receive CAN Data
                            ↓
                  Identify CAN Message
                            ↓
             ┌──────────────┼──────────────┐
             ↓              ↓              ↓
           Speed           Gear            RPM
             │              │              │
             └──────────────┼──────────────┘
                            ↓
                        Indicator
                            ↓
                    Process CAN Data
                            ↓
                   Update LCD Display
                            ↓
                   Control Indicator LEDs
                            ↓
                           LOOP
```

---

## 🚀 How to Run

1. Open **MPLAB X IDE**.
2. Open the required ECU project.
3. Select the **PIC18F4580** microcontroller.
4. Build the project using the **XC8 compiler**.
5. Program the respective ECU.
6. Connect the ECUs through the CAN network.
7. Power the system.
8. Provide the required speed, gear, RPM, and indicator inputs.
9. Observe the vehicle information on the dashboard LCD.

---

## 📊 Sample Output

### 🟢 Output 1 – Normal Condition

```text
--------------------
Speed : 75 km/h
Gear  : G3
RPM   : 3500
IND   : OFF
--------------------
```

### ◀️ Output 2 – Left Indicator

```text
--------------------
Speed : 60 km/h
Gear  : G2
RPM   : 2800
IND   : <-
--------------------
```

### ▶️ Output 3 – Right Indicator

```text
--------------------
Speed : 70 km/h
Gear  : G3
RPM   : 3200
IND   : ->
--------------------
```

### 🚨 Output 4 – Hazard Indicator

```text
--------------------
Speed : 40 km/h
Gear  : G2
RPM   : 2200
IND   : <->
--------------------
```

---

## 💡 Key Learning

- 📡 Understanding CAN communication between multiple ECUs
- 🆔 Understanding CAN message IDs
- 📈 ADC-based data acquisition
- 📺 Character LCD interfacing
- ⏱️ Timer0 configuration
- ⚡ Interrupt handling
- 🔌 GPIO configuration
- 🔄 CAN data transmission and reception
- ⚙️ Processing received CAN messages
- 📊 Converting ADC values into meaningful vehicle parameters
- 🧩 Multi-ECU embedded system design
- 💻 Register-level Embedded C programming
- 📺 Real-time dashboard data display

---

## 🧪 Result

The **CAN-Based Automotive Dashboard** successfully demonstrates communication between three **PIC18F4580 ECUs**.

The system receives and displays:

```text
✔ 🚗 Speed
✔ ⚙️ Gear
✔ 🔄 RPM
✔ 💡 Indicator Status
```

The project demonstrates how multiple ECUs can communicate through a **CAN network** and how the received vehicle information can be processed and displayed on a centralized dashboard.

---

## 👤 Author

### **Sk Shabeena**

📧 **Email:** skshabeena33@gmail.com

🔗 **LinkedIn:** https://www.linkedin.com/in/shaik-shabeena-36a7b933/

🔗 **GitHub:** https://github.com/shabeena1703

