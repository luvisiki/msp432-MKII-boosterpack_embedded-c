//
// Created by Luvisiki Liu on 2023/3/15.
//

#include "analog.h"
#include <stdint.h>

volatile long temp;

void init_adc14(void)
{

    ADC14->CTL0 = 0;
    ADC14->CTL1 = 0;
    ADC14->CTL0 |= (ADC14_CTL0_SSEL__HSMCLK |   //HSMCLK clock source
                    ADC14_CTL0_PDIV_0 |         //predividing by 1
                    ADC14_CTL0_DIV_1);          //dividing by 2
    ADC14->CTL0 |= (ADC14_CTL0_SHP |        //sample-and-hold pulse-mode select
                    ADC14_CTL0_CONSEQ_0);   //single-channel , single-conversion
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;           //disable ENC
    ADC14->CTL0 |= ADC14_CTL0_SHT0_5;       //can be modified only when ADC14ENC=0,select 96 sampling periods
    ADC14->CTL0 |= ADC14_CTL0_ON;           //ADC on

    ADC14->CTL1 |= ADC14_CTL1_RES__14BIT;   //set ADC14 resolution to 14bits
    P5->SEL0 |= BIT5;
    P5->SEL1 |= BIT5;

}

void config_temp(void)
{
    ADC14->CTL1 |= ADC14_CTL1_TCMAP;        //ADC internal temperature sensor channel is selected for ADC input channel
    REF_A->CTL0 |= REF_A_CTL0_ON;           //switch on the voltage reference and enable powering the temperature sensor.
    REF_A->CTL0 &= ~REF_A_CTL0_TCOFF;       //enable temperature sensor

    ADC14->MCTL[0] |= (ADC14_MCTLN_VRSEL_0 |    //set combinations of VR+ and VR-
                        ADC14_MCTLN_INCH_22);    //set input channel.
    ADC14->MEM[0]=0;
    //ADC14->IFGR0 |= ADC14_CLRIFGR0_CLRIFG0;
    ADC14->IER0 |=  ADC14_IER0_IE0;             //set E0 interrupt enable.
    NVIC_EnableIRQ(ADC14_IRQn);
}   

void read_temp(void)
{
    ADC14->CTL0 |=  ADC14_CTL0_ENC;               //enable the enc.
    ADC14->CTL0 |=  ADC14_CTL0_SC;              //start conversation
    
}

extern void ADC14_IRQHandler(void)
{
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG0)        //ADC14MEM0 interrupt flag
    {
        temp = ADC14->MEM[0];     
        printf("value: %d \n",temp);
        ADC14->CLRIFGR0 |= ADC14_CLRIFGR0_CLRIFG0;
    }
    
}
