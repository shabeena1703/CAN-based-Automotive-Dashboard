#include<xc.h>
#include "digital_keypad.h"


void init_digital_keypad(void)
{
    TRISC = TRISC |0X0F;   //setting lower 4 bits of TRISC as inputs...these are our switches
    
}


unsigned char read_digital_keypad(unsigned char trigger)
{
    static int once_pressed = 0;
    if(trigger == EDGE)
    {
        if(((PORTC & 0X0F) != ALL_RELEASED) && (once_pressed == 0))   //if any switch is pressed and not pressed once before
        {
            once_pressed = 1;
            return PORTC & 0X0F;
        }
        
        else if((PORTC & 0X0F)== ALL_RELEASED)
        {
            once_pressed = 0;
        }
        return 0X0F;
    }
    
    
    else if(trigger == LEVEL)
    {
        return PORTC & 0X0F;
    }
    
}

