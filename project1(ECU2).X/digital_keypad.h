

#ifndef DIGITAL_KEYPAD_H
#define	DIGITAL_KEYPAD_H

unsigned char read_digital_keypad(unsigned char trigger);
void init_digital_keypad(void);

#define SW1                 0X0E
#define SW2                 0X0D
#define SW3                 0X0B
#define SW4                 0X07
#define ALL_RELEASED        0X0F

#define LEVEL       1
#define EDGE        0



#endif	/* MATRIX_KEYPAD_H */

