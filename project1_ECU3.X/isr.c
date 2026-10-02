
#include<xc.h>
#include "timer0.h"

#define IND_LEFT    0
#define IND_RIGHT   1
#define IND_HAZARD  2
#define IND_OFF     3


volatile unsigned char indicator_status = IND_OFF;
extern volatile char blink;

void __interrupt() isr(void) {
    static int count = 0;
    if (TMR0IF == 1) {
        TMR0 = TMR0 + 8;

        if (count++ == 10000) {
            count = 0;
            blink = !blink;
        }
        TMR0IF = 0;
    }
}
