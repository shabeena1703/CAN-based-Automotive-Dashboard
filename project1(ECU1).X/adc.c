#include<xc.h>
#include "adc.h"

void init_adc(void)
{
    ADON = 0;            //turn off adc
    
    //KEEP ALL AS ANALOG(0000)
    //PCFG0 = 0;
    //PCFG1 = 0;
    //PCFG2 = 0;
    //PCFG3 = 0;
    
    //REFERENCE VOLTAGE(default)
    VCFG0 = 0;
    VCFG1 = 0;
    
    //FOSC/32 clock conversion(010) .So 1TAD = 1.6us
    ADCS0 = 0;
    ADCS1 = 1;
    ADCS2 = 0;
    
    //for 4TAD(010), acquisition time -> 6.4us
    ACQT0 = 1;
    ACQT1 = 1;
    ACQT2 = 1;
    
    ADFM = 1;       //right justification
    
    ADON = 1;       //turn on ADC
}


unsigned short read_adc(unsigned char channel)
{
    ADCON0 = (ADCON0 & 0XC3) | (channel << 2);
    GO = 1;
    
    while(GO);
    return (ADRESH << 8) | ADRESL;
}
