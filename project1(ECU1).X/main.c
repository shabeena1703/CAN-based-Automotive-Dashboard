/*
 NAME : SHAIK SHABEENA
 REG NO : 25048_004

 DESCRIPTION:
 * ECU1 is one of the Electronic Control Units in the CAN-based automotive dashboard project.
 * The main responsibility of ECU1 is to collect vehicle speed and gear information and send this information to ECU3 through 
   the CAN communication network.

ECU1 gets:
    -> Speed information from a potentiometer through the ADC.
    -> Gear selection from the digital keypad.
After obtaining these inputs, ECU1 sends the corresponding information through CAN using separate message IDs.


What each file does ?
1. main.c :
  It decides what ECU1 should do during normal operation. It initializes all the required peripherals and continuously performs 
  the following operations:

  -> Reads the potentiometer value through the ADC.
  -> Uses the ADC value as the speed input.
  -> Reads the digital keypad to identify the selected gear.
  -> Maintains the current gear selection.
  -> Sends the speed information to ECU3 through CAN.
  -> Sends the gear information to ECU3 through CAN.

  So, main.c acts as the central controller of ECU1. It does not implement the internal working of ADC, CAN, keypad, LCD, or 
  UART itself. Instead, it uses the functions provided by their respective driver files.


2. adc.h :
 * adc.h is the header file for the ADC module.
 * Its purpose is to provide the information required by other files to use the ADC driver.
 * It contains:

        -> ADC channel definitions.
        -> Declarations of ADC-related functions.

 * For example, ECU1 needs to tell the ADC driver which channel to read. The channel definitions provided by this file make 
   that possible.

 * Therefore, adc.h acts as the interface between the main application and the ADC driver.


3. adc.c :
 * adc.c contains the actual working of the ADC peripheral.
 * Its responsibilities are:

        -> Configure the ADC module.
        -> Select the required analog channel.
        -> Start the analog-to-digital conversion.
        -> Wait until the conversion is completed.
        -> Return the converted digital value to the application.

 * In ECU1, the potentiometer is connected to ADC channel CH4.
 * The potentiometer produces an analog voltage depending on its position. The ADC converts this analog voltage into a 
   digital value, which ECU1 uses as the speed input.

 * So, the complete purpose of this file is:
        Potentiometer -> Analog Voltage -> ADC Conversion -> Digital Value
  
  
 4. can.h :
 * can.h is the header file for the CAN communication module.
 * It provides the declarations and definitions required by the application to communicate using CAN.
 * Its purpose is to make CAN communication functions available to main.c without exposing the internal implementation of the CAN driver.
 * ECU1 uses the CAN interface mainly for:

        -> Transmitting speed information.
        -> Transmitting gear information.

 * Therefore, can.h acts as the communication interface between the application and the CAN driver.
  
  
   
 5. can.c :
 * can.c contains the actual implementation of CAN communication.
 * Its responsibilities include:
        -> Configuring the CAN peripheral.
        -> Configuring CAN communication parameters.
        -> Preparing CAN message identifiers.
        -> Loading data into the CAN transmit buffer.
        -> Transmitting CAN messages.
        -> Receiving CAN messages when required.

 * ECU1 uses this driver to send the collected speed and gear information to ECU3.

 * The CAN message identifiers are used to tell ECU3 what type of information has been received.
 * For example:
    -> One CAN ID represents speed.
    -> Another CAN ID represents gear.

* Therefore, can.c handles the low-level CAN communication, while main.c decides what information needs to be transmitted.
  
  
  
 6. digital_keypad.h :
 * digital_keypad.h is the header file for the digital keypad.
 * It defines:
        -> Switch values.
        -> Keypad operating modes.
        -> Function declarations required to initialize and read the keypad.

 * This file provides the interface through which main.c communicates with the keypad driver.
 * Therefore, its main purpose is to define how the application can interact with the keypad. 

 
 7. digital_keypad.c :
 * keypad.c contains the actual working of the digital keypad.
 * Its responsibilities are:
        -> Configure the keypad pins as inputs.
        -> Read the status of the switches.
        -> Detect which switch has been pressed.
        -> Provide the switch information to the main application.
        -> Support edge-triggered or level-triggered key detection.

 * In ECU1, the keypad is used for gear selection.
 * The keys are used to change the gear according to the required operation.
 * The keypad driver does not decide what a particular key means for the vehicle. It only detects the pressed key and returns 
   that information.
 * The gear-selection decision is handled in main.c.


  
 Overall Role of ECU1 :
 * ECU1 can therefore be considered the Speed and Gear Input ECU.
 * Its job is to:
   Acquire -> Process -> Transmit
    -> Acquire speed from the potentiometer.
    -> Acquire gear selection from the keypad.
    -> Process these inputs in the main application.
    -> Transmit the information to ECU3 through CAN.
 * ECU1 does not perform the complete dashboard operation. It is responsible for collecting and sending its assigned vehicle 
   parameters, while ECU3 receives the information from the CAN network and performs the final dashboard processing and display.
  */



#include <xc.h>
#include "adc.h"
#include "digital_keypad.h"
#include "can.h"
//#include "clcd.h"

#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define RPM_MSG_ID 0x30
#define INDICATOR_MSG_ID 0x40

void init_config(void) {

    init_digital_keypad();
    init_adc();
    init_clcd();
    init_can();
}


void main(void) {
    init_config();
    unsigned char key;
    unsigned char gear[8][3] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "_C"};
    unsigned char i = 0;

    uint16_t rx_msg_id;
    uint8_t rx_data[8];
    uint8_t rx_len;

    while (1) 
    {
        //gear increment and decrement
        key = read_digital_keypad(EDGE);

        if (key == SW1) 
        {
            if (i < 6) 
            {
                i++;
            }
        }
        if (key == SW2) 
        {
            if (i > 0) {
                i--;
            }
        }
       
        if(key == SW3)
        {
            i = 7;
            
       }
        
        unsigned short adc_value = read_adc(CH4);
        
        //transmit the speed
        can_transmit(SPEED_MSG_ID,&adc_value,2);
        for(int wait = 0;wait <= 100;wait++);
        
        //transmit the gear
        can_transmit(GEAR_MSG_ID,&i,1);
        for(int wait = 0;wait <= 200;wait++);
             
        
    }
}
    
