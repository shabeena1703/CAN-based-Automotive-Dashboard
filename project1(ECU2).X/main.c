/*
 NAME : SHAIK SHABEENA
 REG NO : 25048_004
 
DESCRIPTION :

 * ECU2 is responsible for collecting RPM and indicator information in the CAN-based automotive dashboard project.
 * ECU2 has two main functions:

        -> It reads an analog input through the ADC and sends the corresponding RPM information to ECU3 through CAN.
        -> It reads the digital keypad to select the indicator condition and sends the indicator status to ECU3 through CAN.
 * ECU3 receives these CAN messages and uses them to display the RPM and indicator status on the dashboard.
 * Therefore, ECU2 acts as the RPM and Indicator Input ECU.
  
  
 What each file does ? 
 1. main.c :
  * main.c is the main control file of ECU2.
  * It controls the complete operation of ECU2 and decides when each peripheral should be used.
  * The main responsibilities of this file are:
        -> Initialize the ADC.
        -> Initialize the digital keypad.
        -> Initialize Timer0.
        -> Initialize CAN communication.
        -> Configure the indicator output pins.
        -> Read the analog input from ADC channel CH4.
        -> Send the ADC value as RPM information through CAN.
        -> Read the digital keypad.
        -> Identify the selected indicator condition.
        -> Send the selected indicator status through CAN.

  * The keypad is used to select four indicator conditions:
        SW1 ? Left indicator
        SW2 ? Hazard indicator
        SW3 ? Right indicator
        SW4 ? Indicator OFF

  * The actual indicator status is represented internally by a corresponding value. ECU3 receives this value and decides what should be displayed on the 
    dashboard.

 Therefore, main.c acts as the central application controller of ECU2.
  
  
 
 2. adc.h :
  * adc.h is the header file for the ADC module.
  * Its purpose is to provide the definitions and function declarations required to use the ADC driver.
  * It defines the available ADC channels, including CH0 to CH10.
  * The main application uses these channel definitions to select the required analog input.
  * In ECU2, CH4 is used for the RPM input.
  * Therefore, adc.h provides the interface through which the application can access the ADC driver. 
  
  
  
 3. adc.c :
  * adc.c contains the actual implementation of the ADC peripheral.
  * Its responsibilities are:
        -> Configure the ADC module.
        -> Configure the ADC conversion clock.
        -> Configure the acquisition time.
        -> Configure the result format.
        -> Select the required ADC channel.
        -> Start the ADC conversion.
        -> Wait until the conversion is completed.
        -> Return the converted digital value.

  * In ECU2, an analog input is connected to ADC channel CH4.
  * The analog input is converted into a digital value, which is then used by main.c as the RPM input information.
  * So, the working flow is:
        Analog RPM Input ? ADC ? Digital Value ? main.c ? CAN

  * The ADC driver is responsible only for obtaining the digital value. The application decides how that value is used. 
  
  
  
 4. can.h :
  * can.h is the header file for the CAN communication module.
  * It provides the definitions and function declarations required to communicate through CAN.
  * It provides the interface for:
        -> CAN initialization.
        -> CAN data transmission.
        -> CAN data reception.
  * It also contains definitions related to the ECAN module, CAN operation modes, message data positions, and CAN receive buffers.
  * In ECU2, the CAN interface is mainly used to transmit:
        -> RPM information.
        -> Indicator status.

  * Therefore, can.h acts as the communication interface between the ECU2 application and the CAN driver.  
  
  
  
 5. can.c :
  * can.c contains the low-level implementation of CAN communication.
  * Its responsibilities include:
        -> Configure the CAN transmit and receive pins.
        -> Put the CAN module into the required configuration mode.
        -> Configure CAN timing parameters.
        -> Configure the CAN operating mode.
        -> Configure the CAN receive buffer.
        -> Set the CAN message identifier.
        -> Load data into the CAN transmit buffer.
        -> Request CAN transmission.
        -> Read received CAN messages when required.

  * ECU2 uses this driver to transmit two types of information(RPM message and indicator message).  
  * Therefore, can.c handles the actual CAN hardware communication, while main.c decides which information should be transmitted.
  
  
  
 6. digital_keypad.h :
  * digital_keypad.h is the header file for the digital keypad module.
  * It defines the switch values and the keypad operating modes.
  * It provides the application with the interface required to:
        -> Initialize the keypad.
        -> Read the keypad.
        -> Identify the pressed switch.
        -> Use edge-triggered or level-triggered operation.

  * The keypad contains four switches:
        -> SW1
        -> SW2
        -> SW3
        -> SW4
  * These switches are used by ECU2 to select the required indicator condition.
  * Therefore, digital_keypad.h provides the interface between the application and the keypad driver.  
  
  
  
 7. digital_keypad.c :
  * keypad.c contains the actual implementation of the digital keypad.
  * Its responsibilities are:
        -> Configure the keypad pins as inputs.
        -> Read the status of the switches.
        -> Detect when a switch is pressed.
        -> Prevent repeated detection of the same key press when edge-triggered mode is used.
        -> Return the detected switch value to main.c.

  * The keypad driver itself does not decide whether a key means left indicator, right indicator, or hazard.
  * It only detects which switch was pressed.
  * The meaning of each switch is decided by main.c.
  * For ECU2:
        -> SW1 ? Left
        -> SW2 ? Hazard
        -> SW3 ? Right
        -> SW4 ? OFF

  * keypad.c ? Detects the key
  * main.c ? Decides the indicator action 
  
  
  
 8. timer0.h :
  * timer0.h is the header file for the Timer0 module.
  * It provides the function declaration required to initialize Timer0.
  * The application does not need to know the internal Timer0 configuration. It simply requests Timer0 initialization through this interface.
  * Therefore, timer0.h acts as the interface between the application and Timer0 driver.  
  
  
  
 9. timer0.c :
  * timer.c contains the configuration of the Timer0 peripheral.
  * Its responsibilities are:
        -> Enable Timer0.
        -> Configure Timer0 as an 8-bit timer.
        -> Select the internal instruction clock as the timer source.
        -> Configure the Timer0 preload value.
        -> Configure Timer0 to generate interrupts.
        -> Enable the required interrupt controls.
        -> Clear the Timer0 interrupt flag.

  * Timer0 is included in ECU2 mainly to provide a periodic interrupt mechanism.
  * This periodic interrupt can be used for time-based operations such as indicator blinking.
  * Therefore:
        Timer0 ? Periodic interrupt ? Timing control

  * The Timer0 driver handles the timer hardware configuration, while the application/interrupt logic can use the generated interrupt for periodic operations.
  
  
* ECU2 can be considered the RPM and Indicator Input ECU.
* Its operation can be summarized as:
    RPM:
    Analog Input -> ADC -> RPM Data -> CAN -> ECU3

    Indicator:
    Keypad -> Indicator Selection -> Indicator Status -> CAN -> ECU3

* ECU2 therefore collects its assigned vehicle parameters and sends them to ECU3 through the CAN network. ECU3 is responsible for processing the received information and presenting the final dashboard output.  
    
  */



#include <xc.h>
#include "adc.h"
#include "digital_keypad.h"
#include "timer0.h"
#include "can.h"
//#include "clcd.h"

#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define RPM_MSG_ID 0x30
#define INDICATOR_MSG_ID 0x40

#define IND_LEFT    0
#define IND_RIGHT   1
#define IND_HAZARD  2
#define IND_OFF     3

volatile unsigned char indicator_status;
char blink = 0;

void init_config(void) {
    init_adc();
    init_digital_keypad();
    init_timer0();
    init_can();
    //init_clcd();
    
    TRISB0 = 0;
    RB0 = 0;

    TRISB7 = 0;
    RB7 = 0;
}

void main(void) {
    init_config();
    unsigned char key;
    indicator_status = IND_OFF;
    
    uint16_t rx_msg_id;
    uint8_t rx_data[8];
    uint8_t rx_len;

    while (1) 
    {

        
        unsigned short adc_value = (read_adc(CH4));
        
        
        can_transmit(RPM_MSG_ID,&adc_value,2);
        for(int wait = 0;wait <= 300; wait++);
          

        key = read_digital_keypad(EDGE);

        if (key == SW1) 
        {
            indicator_status = IND_LEFT;
        }
        if (key == SW2) 
        {
            indicator_status = IND_HAZARD;
        }
        if (key == SW3) 
        {
            indicator_status = IND_RIGHT;
        }
        if (key == SW4) 
        {
            indicator_status = IND_OFF;
        }
        
        can_transmit(INDICATOR_MSG_ID, &indicator_status, 1);
        for(int wait = 0;wait <= 400;wait++);

    }
}
