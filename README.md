# 🚗 CAN-Based Automotive Dashboard

> A CAN-based automotive dashboard implemented using three PIC18F4580 ECUs to monitor and display Speed, Gear, RPM, and Indicator status.

---

## 📝 About the Project

The **CAN-Based Automotive Dashboard** is an embedded systems project developed using **PIC18F4580 microcontrollers** and **Embedded C**.

The system consists of three ECUs communicating through a **CAN (Controller Area Network) bus**.

- 🚗 **ECU1** → Speed and Gear
- 🔄 **ECU2** → RPM and Indicator
- 📺 **ECU3** → Dashboard Display

ECU1 and ECU2 collect vehicle-related information and transmit it through CAN. ECU3 receives the CAN messages, identifies the data using CAN message IDs, processes the received information, and displays it on a Character LCD.

---

## ✨ Features

- 🚗 Speed monitoring
- ⚙️ Gear monitoring
- 🔄 RPM monitoring
- 💡 Left indicator
- 💡 Right indicator
- 🚨 Hazard indicator
- 📡 CAN communication between multiple ECUs
- 📺 Character LCD dashboard
- 💡 Indicator LED control
- ⏱️ Timer0 interrupt-based blinking
- 🆔 CAN message ID-based data processing
- 🔧 PIC18F4580 based embedded system
- 💻 Embedded C programming

---

## 🏗️ System Architecture

```text
                         🚗 AUTOMOTIVE DASHBOARD
                                  │
          ┌───────────────────────┼───────────────────────┐
          │                       │                       │
          ▼                       ▼                       ▼
    ┌─────────────┐         ┌─────────────┐         ┌─────────────┐
    │    ECU1     │         │    ECU2     │         │    ECU3     │
    │             │         │             │         │             │
    │ Speed       │         │ RPM         │         │ Dashboard   │
    │ Gear        │         │ Indicator   │         │             │
    └──────┬──────┘         └──────┬──────┘         └──────┬──────┘
           │                       │                       │
           └───────────────────────┼───────────────────────┘
                                   │
                              📡 CAN BUS
                                   │
                                   ▼
                           📺 Character LCD
                           💡 Indicator LEDs
```

---

## 🧠 How It Works

**🚗 ECU1 – Speed and Gear**

ECU1 is responsible for collecting and transmitting:

- Speed
- Gear

The speed input is processed through ADC and the gear information is converted into a corresponding gear value.

```text
              ECU 1
                 │
        ┌────────┴────────┐
        │                 │
        ▼                 ▼
      Speed             Gear
        │                 │
        ▼                 │
       ADC                │
        │                 │
        └────────┬────────┘
                 │
                 ▼
            CAN Transmit
                 │
                 ▼
              CAN BUS
```

---

**🔄 ECU2 – RPM and Indicator**

ECU2 is responsible for:

- RPM measurement
- Indicator selection

RPM is read through **ADC channel CH4**.

The digital keypad is used to select the indicator condition.

| 🔘 Switch | 💡 Function |
|:---------:|:------------|
| `SW1` | Left |
| `SW2` | Hazard |
| `SW3` | Right |
| `SW4` | OFF |

```text
                  ECU2
                    │
           ┌────────┴────────┐
           │                 │
           ▼                 ▼
        ADC CH4           Keypad
           │                 │
           ▼                 ▼
          RPM           Indicator
           │                 │
           └────────┬────────┘
                    │
                    ▼
               CAN Transmit
                    │
                    ▼
                 CAN BUS
```

---

**📺 ECU3 – Dashboard**

ECU3 receives Speed, Gear, RPM, and Indicator messages from the CAN bus.

It:

1. Receives CAN messages
2. Checks the CAN message ID
3. Extracts the received data
4. Processes the data
5. Updates the Character LCD
6. Controls the indicator LEDs

```text
                     CAN BUS
                         │
                         ▼
                  CAN Reception
                         │
                         ▼
                  Check CAN ID
                         │
          ┌──────────────┼──────────────┐
          ▼              ▼              ▼
        Speed           Gear           RPM
          │              │              │
          └──────────────┼──────────────┘
                         │
                         ▼
                     Indicator
                         │
                         ▼
                    Process Data
                         │
                 ┌───────┴───────┐
                 ▼               ▼
               CLCD             LEDs
```

---

## 📡 CAN Communication

The three ECUs communicate using the **CAN protocol**.

CAN is used to exchange vehicle information between the ECUs through a common communication bus.

**CAN Pins**

| 🔌 Signal | 📍 Pin |
|:---------:|:------:|
| CAN TX | `RB2` |
| CAN RX | `RB3` |

---

**🆔 CAN Message IDs**

Each vehicle parameter has a separate CAN message ID.

| 🚘 Parameter | 🆔 CAN ID | 📦 Information |
|:------------:|:---------:|:----------------|
| Speed | `0x10` | Speed value |
| Gear | `0x20` | Gear information |
| RPM | `0x30` | RPM value |
| Indicator | `0x40` | Indicator status |

---

**🔄 CAN Communication Flow**

```text
                       ┌─────────────┐
                       │    ECU1     │
                       │ Speed/Gear  │
                       └──────┬──────┘
                              │
                              │
                              ▼
                       ┌─────────────┐
                       │             │
                       │  CAN BUS    │
                       │             │
                       └──────┬──────┘
                              │
                    ┌─────────┴─────────┐
                    │                   │
                    ▼                   ▼
             ┌─────────────┐     ┌─────────────┐
             │    ECU2     │     │    ECU3     │
             │ RPM/Ind.    │     │ Dashboard   │
             └─────────────┘     └──────┬──────┘
                                        │
                              ┌─────────┼─────────┐
                              ▼         ▼         ▼
                            Speed     Gear       RPM
                                        │
                                        ▼
                                   Indicator
                                        │
                                        ▼
                                  📺 Dashboard
```

---

**🚦 Speed Processing**

The speed input is read using ADC and processed before transmission.

```text
               Speed Input
                    │
                    ▼
                   ADC
                    │
                    ▼
              ADC Value
                    │
                    ▼
             Speed Processing
                    │
                    ▼
               CAN Transmit
                    │
                    ▼
                 CAN BUS
                    │
                    ▼
                   ECU3
                    │
                    ▼
               LCD Display
```

The speed value is mapped to:

```text
0 ─── 100 km/h
```

---

**⚙️ Gear Processing**

The gear is represented using an index and converted into the corresponding gear string.

| 🔢 Index | ⚙️ Gear |
|:--------:|:-------:|
| `0` | `GN` |
| `1` | `G1` |
| `2` | `G2` |
| `3` | `G3` |
| `4` | `G4` |
| `5` | `G5` |
| `6` | `GR` |
| `7` | `_C` |

---

**🔄 RPM Processing**

RPM is measured using **ADC channel CH4** in ECU2.

```text
                  RPM Input
                       │
                       ▼
                      ADC
                       │
                       ▼
                 ADC Value
                       │
                       ▼
                 RPM Processing
                       │
                       ▼
                  CAN Transmit
                       │
                       ▼
                    CAN BUS
                       │
                       ▼
                      ECU3
                       │
                       ▼
                  LCD Display
```

The RPM value is processed in the range:

```text
0 ── 6000 RPM
```

---

**💡 Indicator Processing**

The digital keypad controls the indicator selection.

| 🔘 Switch | 💡 Indicator |
|:---------:|:-------------|
| `SW1` | LEFT |
| `SW2` | HAZARD |
| `SW3` | RIGHT |
| `SW4` | OFF |

**💡 Indicator Values**

| 🔢 Value | 💡 Condition |
|:--------:|:-------------|
| `0` | LEFT |
| `1` | RIGHT |
| `2` | HAZARD |
| `3` | OFF |

---

**⏱️ Timer0 and Indicator Blinking**

Timer0 is used to generate periodic interrupts for indicator blinking.

```text
                    ⏱️ Timer0
                        │
                        ▼
                Timer0 Overflow
                        │
                        ▼
                   Interrupt
                        │
                        ▼
                  ISR Execution
                        │
                        ▼
                  Update Counter
                        │
                        ▼
                  Toggle Indicator
                        │
                        ▼
                    💡 Blink
```

**⚙️ Timer0 Configuration**

- 8-bit Timer0
- Internal clock
- No prescaler
- Timer preload: `TMR0 = 6`
- Interrupt-based operation
- Counter-based blinking

---

## 📺 Dashboard Display

ECU3 uses an **8-bit Character LCD** to display the received vehicle information.

**🖥️ Example Dashboard Layout**

```text
┌────────────────┐
│SPD:75 G:G3     │
│RPM:3500 IND:OFF│
└────────────────┘
```

The LCD displays:

- 🚦 Speed
- ⚙️ Gear
- 🔄 RPM
- 💡 Indicator status

---

## 🔌 Hardware Configuration

**📡 CAN**

| Signal |  Pin |
|:---------:|:------:|
| CAN TX | `RB2` |
| CAN RX | `RB3` |

**📺 Character LCD**

|  LCD Signal |  Pin |
|:-------------:|:------:|
| LCD Data | `PORTD` |
| EN | `RC2` |
| RS | `RC1` |
| RW | `RC0` |
| Busy | `RD7` |

**💡 Indicator LEDs**

|  Indicator |  Pin |
|:------------:|:------:|
| Left LED | `RB0` |
| Right LED | `RB7` |

---

## 📁 Project Structure

```text
CAN-Based-Automotive-Dashboard/
│
├── ECU1.X/
│   ├── main.c
│   ├── adc.c
│   ├── adc.h
│   ├── can.c
│   ├── can.h
│   ├── digital_keypad.c
│   ├── digital_keypad.h
│   ├── timer0.c
│   └── timer0.h
│
├── ECU2.X/
│   ├── main.c
│   ├── adc.c
│   ├── adc.h
│   ├── can.c
│   ├── can.h
│   ├── digital_keypad.c
│   ├── digital_keypad.h
│   ├── timer0.c
│   └── timer0.h
│
├── ECU3.X/
│   ├── main.c
│   ├── can.c
│   ├── can.h
│   ├── clcd.c
│   ├── clcd.h
│   ├── timer0.c
│   └── timer0.h
│
└── README.md
```

---

## 📋 File Description

| 📄 File | 📝 Description |
|:--------|:---------------|
| `main.c` | Contains the main application logic of each ECU |
| `adc.c` | Implements ADC configuration and conversion |
| `adc.h` | Contains ADC definitions and function declarations |
| `can.c` | Implements CAN initialization, transmission, and reception |
| `can.h` | Contains CAN definitions and function declarations |
| `digital_keypad.c` | Implements digital keypad operations |
| `digital_keypad.h` | Contains keypad definitions and declarations |
| `timer0.c` | Implements Timer0 configuration |
| `timer0.h` | Contains Timer0 declarations |
| `clcd.c` | Implements Character LCD operations |
| `clcd.h` | Contains CLCD definitions and declarations |
| `README.md` | Project documentation |

---

## 🛠️ Technologies & Concepts

| 🛠️ Category | 💻 Used |
|:------------|:--------|
| Microcontroller | PIC18F4580 |
| Programming Language | Embedded C |
| Communication | CAN |
| Display | Character LCD |
| Analog Input | ADC |
| Input | Digital Keypad |
| Timer | Timer0 |
| Interrupts | Timer0 Interrupt |
| GPIO | Digital Input / Output |
| CAN TX | RB2 |
| CAN RX | RB3 |
| IDE | MPLAB X IDE |
| Compiler | XC8 |

---

## 🔄 Program Flow

```text
                          START
                            │
                            ▼
                   Initialize ECU
                            │
              ┌─────────────┼─────────────┐
              │             │             │
              ▼             ▼             ▼
             ADC          Keypad          CAN
              │             │             │
              ▼             ▼             │
         Read Input    Read Switch        │
              │             │             │
              ▼             ▼             │
        Vehicle Data   Indicator          │
              │          Status            │
              └─────────────┬──────────────┘
                            │
                            ▼
                       CAN Transmit
                            │
                            ▼
                         CAN BUS
                            │
                            ▼
                           ECU3
                            │
                            ▼
                       CAN Receive
                            │
                            ▼
                      Identify CAN ID
                            │
              ┌─────────────┼─────────────┐
              ▼             ▼             ▼
            Speed          Gear           RPM
              │             │             │
              └─────────────┼─────────────┘
                            │
                            ▼
                        Indicator
                            │
                            ▼
                       Process Data
                            │
                            ▼
                        Dashboard
                            │
                    ┌───────┴───────┐
                    ▼               ▼
                   CLCD           LEDs
                          
```

---

## 🚀 How to Run

**1️⃣ Open the Projects**

Open each project separately in **MPLAB X IDE**:

```text
ECU1.X
ECU2.X
ECU3.X
```

**2️⃣ Build the Projects**

For each ECU:

- Select **PIC18F4580**
- Use **XC8 Compiler**
- Perform **Clean and Build**
- Generate the HEX file

**3️⃣ Program the Microcontrollers**

Program the generated HEX file into the respective PIC18F4580 microcontroller.

**4️⃣ Connect the CAN Network**

Connect the three ECUs through the CAN communication network.

**5️⃣ Power On**

After powering the system:

```text
ECU1 → Sends Speed and Gear
ECU2 → Sends RPM and Indicator
ECU3 → Receives CAN Data
ECU3 → Processes CAN Data
ECU3 → Displays Dashboard Data
```

---

## 📊 Sample Output

Different vehicle conditions can be tested using different Speed, Gear, RPM, and Indicator values.

| 🧪 Condition | 🚦 Speed | ⚙️ Gear | 🔄 RPM | 💡 Indicator |
|:-------------|:--------:|:-------:|:------:|:------------:|
| Normal | 75 km/h | G3 | 3500 | OFF |
| Left Turn | 60 km/h | G2 | 2800 | <- |
| Right Turn | 70 km/h | G3 | 3200 | -> |
| Hazard | 40 km/h | G2 | 2200 | <-> |

**🟢 Normal**

```text
Speed = 75 km/h
Gear = G3
RPM = 3500
Indicator = OFF
```

**◀️ Left Turn**

```text
Speed = 60 km/h
Gear = G2
RPM = 2800
Indicator = LEFT
```

**▶️ Right Turn**

```text
Speed = 70 km/h
Gear = G3
RPM = 3200
Indicator = RIGHT
```

**🚨 Hazard**

```text
Speed = 40 km/h
Gear = G2
RPM = 2200
Indicator = HAZARD
```

---

## 💡 Key Learning

This project provided practical experience in:

- 📡 CAN communication
- 🧩 Multi-ECU communication
- 🔧 PIC18F4580 microcontroller
- 💻 Embedded C programming
- 📈 ADC interfacing
- 🔘 Digital keypad interfacing
- 📺 Character LCD interfacing
- ⏱️ Timer0 configuration
- ⚡ Interrupt handling
- 🔌 GPIO configuration
- 🆔 CAN message IDs
- 🔄 CAN data transmission and reception
- 🚗 Automotive embedded systems
- 🛠️ Register-level Embedded C

---

## 🧪 Result

Successfully developed a **CAN-Based Automotive Dashboard** using three PIC18F4580 ECUs.

The system demonstrates how multiple ECUs can communicate through a common CAN bus to exchange vehicle information.

```text
 Speed
   │
 Gear
   │
 RPM
   │
 Indicator
   │
   ▼
 CAN BUS
   │
   ▼
 DASHBOARD
```

The received vehicle parameters are processed by ECU3 and displayed on the Character LCD, while the indicator status is represented using indicator LEDs.

---

## 👤 Author

**Sk Shabeena**

📧 Email: `skshabeena33@gmail.com`

💼 LinkedIn: https://www.linkedin.com/in/shaik-shabeena-36a7b933/

🐙 GitHub: https://github.com/shabeena1703
