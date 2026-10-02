#include <xc.h>
#include<stdint.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


#define IND_LEFT    0
#define IND_RIGHT   1
#define IND_HAZARD  2
#define IND_OFF     3

volatile char blink = 0;
void handle_speed_data(uint8_t *data, uint8_t len)
{
    
    uint16_t adc_value;
    unsigned long value;

    if(len != 2)
    {
        return;
    }

    adc_value = data[0] | ((uint16_t)data[1] << 8);

    value = ((unsigned long)adc_value * 100) / 1023;
    clcd_print("SPD",LINE1(0));

    clcd_putch((value / 100) % 10 + '0', LINE2(0));
    clcd_putch((value / 10) % 10 + '0', LINE2(1));
    clcd_putch(value % 10 + '0', LINE2(2));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    unsigned char gear[8][3] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "_C"};
     clcd_print("GR", LINE1(4));
    for(int i=0;i<len;i++)
    {
          clcd_print(gear[data[i]], LINE2(4));
    }
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    uint16_t adc_value;
    unsigned long value;

    if(len != 2)
    {
        return;
    }

    adc_value = data[0] | ((uint16_t)data[1] << 8);
    value = ((unsigned long)adc_value * 6000) / 1023;
    
    clcd_print("RPM", LINE1(7));
    clcd_putch((value / 1000) % 10 + '0', LINE2(7));
    clcd_putch((value / 100) % 10 + '0', LINE2(8));
    clcd_putch((value / 10) % 10 + '0', LINE2(9));
    clcd_putch(value % 10 + '0', LINE2(10));
    
}


void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    clcd_print("IND", LINE1(12));
    for(int i=0;i<len;i++)
    {
        switch (data[i]) 
        {
            case IND_LEFT:
                if (blink) 
                {
                    clcd_print("<-", LINE2(12));
                    RB0 = 1;
                    RB7 = 0;
                } 
                else 
                {
                    clcd_print("  ", LINE2(12));
                    RB0 = 0;
                    RB7 = 0;
                }
                break;

            case IND_RIGHT:
                if(blink)
                {
                    RB0 = 0;
                    clcd_print("-> ", LINE2(12));
                    RB7 = 1;
                }
                else
                {
                    RB0 = 0;
                    clcd_print("  ", LINE2(12));
                    RB7 = 0;
                }
                break;

            case IND_HAZARD:
                if(blink)
                {
                    RB0 = 1;
                    RB7 = 1;
                    clcd_print("<->", LINE2(12));
                }
                else
                {
                    RB0 = 0;
                    RB7 = 0;
                    clcd_print("   ", LINE2(12));
                }
                
                break;

            case IND_OFF:
                clcd_print("   ", LINE2(12));
                RB0 = 0;
                RB7 = 0;
                break;

        }
    }
}

void process_canbus_data() 
{   
    uint16_t msg_id;
    uint8_t data[8];
    uint8_t len;
    can_receive(&msg_id,data,&len);
    
    switch(msg_id)
    {
        case SPEED_MSG_ID:
            handle_speed_data(data,len);
            break;
            
        case GEAR_MSG_ID:
            handle_gear_data(data,len);
            break;
            
        case RPM_MSG_ID:
            handle_rpm_data(data,len);
            break;
            
        case INDICATOR_MSG_ID:
            handle_indicator_data(data,len);
            break;
    }
    
}
