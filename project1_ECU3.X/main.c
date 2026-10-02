/*
 NAME : SHAIK SHABEENA
 REG NO : 25048_004
 
 DESCRIPTION :
 
 * ECU3 is the main processing and display ECU in the CAN-based automotive dashboard project.
 * ECU3 receives information from ECU1 and ECU2 through the CAN bus. 
 * ECU3 also controls the indicator LEDs and uses Timer0 to generate the timing required for indicator blinking.
 * Therefore, ECU3 acts as the central processing and dashboard display ECU.
  
 What each file does ?
1. main.c :
  * main.c is the main application file of ECU3.
  * It controls the overall operation of ECU3.
  * During initialization, it initializes:
        -> Character LCD
        -> CAN communication
        -> Indicator LEDs
        -> Timer0
  * After initialization, ECU3 continuously checks the CAN bus for incoming messages.
  * Whenever a CAN message is available, main.c calls the CAN message processing function.
  * Therefore, main.c has a simple responsibility:
        Initialize the required peripherals ? Continuously process received CAN data
  * The actual processing of Speed, Gear, RPM, and Indicator messages is handled by message_handler.c.

 * So, main.c acts as the entry point and overall controller, rather than containing all the dashboard logic itself.  
   
 
 
2. clcd.h :
  * clcd.h is the header file for the LCD.
  * It contains the LCD pin definitions, LCD commands, line positions, and function declarations.
  * It tells the program how to use the LCD. 
  
  
  
3. clcd.c :
  * clcd.c contains the actual LCD working.
  * It:
        -> Initializes the LCD.
        -> Sends commands to the LCD.
        -> Displays characters.
        -> Displays strings.
        -> Checks whether the LCD is ready.
  * ECU3 uses the LCD to display:
        -> Speed
        -> Gear
        -> RPM
        -> Indicator status  
  
  
  
4. message_handler.h :
  * message_handler.h is the header file for processing CAN messages.
  * It provides the function declarations for handling different types of data:
        -> Speed
        -> Gear
        -> RPM
        -> Engine temperature
        -> Indicator  
 
   
  
5. message_handler.c :
  * message_handler.c contains the main processing logic of ECU3.
  * This is where ECU3 decides what the received CAN data means.
  * First, it checks the CAN message ID.
  * For example:
        0x10 ? Speed
        0x20 ? Gear
        0x30 ? RPM
        0x40 ? Indicator
  * Then it calls the corresponding function to process that data.
        a. Speed :
            -> It receives the speed data from ECU1, converts it into the required speed value, and displays it on the LCD.

        b. Gear :
            -> It receives the gear index from ECU1 and converts the index into the corresponding gear display such as:
                GN, G1, G2, G3, G4, G5, GR, or _C.

        c. RPM :
            -> It receives the RPM data from ECU2, converts it into the required RPM value, and displays it on the LCD.

        d. Indicator :
            -> It receives the indicator status from ECU2.

  * Based on the status, it displays:
        <- for left
        -> for right
        <-> for hazard
        Blank for OFF

  * It also controls the left and right indicator LEDs.

* message_handler.c is the brain of ECU3. It understands the received CAN data and decides what should be displayed or controlled.
  
  
  
6. msg_id.h :
  * msg_id.h contains the CAN message IDs used in the project.
  * Each type of data has a different ID.
            -> Speed (msg_id 0x10) sent by ECU1.
            -> Gear (msg_id 0x20) sent by ECU1.
            -> RPM (msg_id 0x30) sent by ECU2.
            -> Indicator (msg_id 0x40) sent by ECU2.
  * The message ID helps ECU3 identify the received data.
  
  
  
7. timer0.h :
  * timer0.h is the header file for Timer0.
  * It provides the function declaration needed to initialize Timer0.
  * In simple words, timer0.h provides the interface for Timer0.  
  
  
  
8. timer0.c :
  * timer0.c contains the Timer0 configuration.
  * It:
        -> Configures Timer0.
        -> Enables Timer0.
        -> Selects the timer clock.
        -> Sets the initial timer value.
        -> Enables the Timer0 interrupt.

  * Timer0 provides regular interrupts that are used for indicator blinking. 
  
  
  
9. isr.c :
  * isr.c contains the Interrupt Service Routine (ISR).
  * The ISR runs whenever Timer0 generates an interrupt.
  * It counts the Timer0 interrupts and changes the blink state after a certain number of interrupts.
  * This blink state is used by the indicator handler to turn the indicator display and LEDs ON and OFF. 
  
 
* ECU3 receives Speed and Gear from ECU1 and RPM and Indicator from ECU2 through CAN, processes the received information, 
  displays it on the LCD, and controls the indicator LEDs.  
 */
#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
#include "timer0.h"

void init_leds() 
{
    
    TRISB0 = 0;
    TRISB7 = 0;
    RB0 = 0;
    RB7 = 0;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();

    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }

    return;
}
