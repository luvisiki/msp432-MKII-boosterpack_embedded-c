//
// Created by Luvisiki Liu on 2023/3/15.
//

#include "analog.h"
#include <stdint.h>
#include "buttons/buttons.h"

#define VREF 3.3                                        //Reference voltage
#define ADC_RES 16348                                   //ADC14 resolution 14bits.
#define TEMP_OFFSET 35                                  //large offset

volatile long temp=0;


void init_adc14(void)
{
    ADC14->CTL0 = 0;
    ADC14->CTL1 = 0;
    ADC14->CTL0 |= (ADC14_CTL0_SSEL__HSMCLK |           //HSMCLK clock source
                    ADC14_CTL0_PDIV_0 |                 //predividing by 1
                    ADC14_CTL0_DIV_1);                  //dividing by 2

    ADC14->CTL0 |= (ADC14_CTL0_SHP |                    //sample-and-hold pulse-mode select
                    ADC14_CTL0_CONSEQ_1);               //in exer14: change to sequence of channels
    
    ADC14->CTL0 |= ADC14_CTL0_SHT0_5;                   //can be modified only when ADC14ENC=0,select 96 sampling periods
    ADC14->CTL0 |= ADC14_CTL0_ON;                       //ADC on

    ADC14->CTL1 |= ADC14_CTL1_RES__14BIT;               //set ADC14 resolution to 14bits
//    P5->SEL0 |= BIT0;
}

void config_temp(void)
{
    ADC14->CTL1 |= ADC14_CTL1_TCMAP;                    //ADC internal temperature sensor channel is selected for ADC input channel
    REF_A->CTL0 |= REF_A_CTL0_ON;                       //switch on the voltage reference and enable powering the temperature sensor.
    REF_A->CTL0 &= ~REF_A_CTL0_TCOFF;                   //enable temperature sensor

    ADC14->MCTL[0] |= (ADC14_MCTLN_VRSEL_0 |            //set combinations of VR+ and VR-
                        ADC14_MCTLN_INCH_22);           //set input channel.  channel 22 is equal to pin5.2.
               
    
    ADC14->MEM[0]=0;
    
    //ADC14->IFGR0 |= ADC14_CLRIFGR0_CLRIFG0;
    //ADC14->IER0 |=  ADC14_IER0_IE0;                     //set E0 interrupt enable.
    // NVIC_EnableIRQ(ADC14_IRQn);
    
}   
void config_joystic(void)
{
    /*
        SEL   :J1.5  -> P4.3 analog in A12
        HOR(X):J1.2  -> P6.0 analog in A15
        VER(Y):J3.26 -> P4.4 analog in A9
    */
    //config the DIO pins input.
    // P4->SEL0 |= BIT3;
    // P4->SEL1 |= BIT3;
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;

    REF_A->CTL0 |= REF_A_CTL0_ON;
    ADC14->CTL1 |= ADC14_CTL1_TCMAP;

    ADC14->CTL0 &= ~ADC14_CTL0_ENC ;                    //disable ENC

    ADC14->MEM[3]=0;                                    //config ADC14MEM3,4
    ADC14->MEM[4]=0;
    ADC14->MCTL[3] |= (ADC14_MCTLN_VRSEL_0 |            //set combinations of VR+ and VR-
                       ADC14_MCTLN_INCH_15);            //set input channel.  channel 15 is equal to pin6.0
    ADC14->MCTL[4] |= (ADC14_MCTLN_VRSEL_0 |            //set combinations of VR+ and VR-
                       ADC14_MCTLN_INCH_9);             //set input channel.  channel 9 is equal to pin4.4

    ADC14->CTL0 |= ADC14_CTL0_MSC;                      //set ADC14MSC 1.
    ADC14->MCTL[4] |= ADC14_MCTLN_EOS;                  //set ADC14EOS:end of sequence
}

void config_accel(void)
{
    /*
        description : use 3-axis accelermoeter
        X:  J3.23 -> P6.1 A14
        Y:  J3.24 -> P4.0 A13
        Z:  J3.25 -> P4.2 A11
    */
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;

    
    ADC14->CTL0 &= ~ADC14_CTL0_ENC ;                    //disable ENC

    REF_A->CTL0 |= REF_A_CTL0_ON;
    ADC14->CTL1 |= ADC14_CTL1_TCMAP;
    

    ADC14->MEM[5]=0;                                    //config ADC14MEM3,4
    ADC14->MEM[6]=0;
    ADC14->MEM[7]=0;
    ADC14->MCTL[5] |= (ADC14_MCTLN_VRSEL_0 |            //set combinations of VR+ and VR-
                       ADC14_MCTLN_INCH_14);            //set input channel.  
    ADC14->MCTL[6] |= (ADC14_MCTLN_VRSEL_0 |            //set combinations of VR+ and VR-
                       ADC14_MCTLN_INCH_13);            //set input channel.  
    ADC14->MCTL[7] |= (ADC14_MCTLN_VRSEL_0 |            //set combinations of VR+ and VR-
                       ADC14_MCTLN_INCH_11);            //set input channel.  

    ADC14->CTL0 |= ADC14_CTL0_MSC;                      //set ADC14MSC 1.
    ADC14->MCTL[7] |= ADC14_MCTLN_EOS;                  //set ADC14EOS:end of sequence
}

void read_joystick(uint16_t *x,uint16_t *y)
{
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;                     //disable enc
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;      //start conversation
    while(!ADC14->IFGR0 & ADC14_IFGR0_IFG4){}     //wait for pooling
    *x = ADC14->MEM[3];
    *y = ADC14->MEM[4];
    
}

void read_accel(uint16_t *x, uint16_t *y, uint16_t *z)
{
    /*
        CONNET TO CONFIG_ACCEL FUNCTION
    */
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;                     //disable enc
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;      //start conversation
    while(!ADC14->IFGR0 & ADC14_IFGR0_IFG7){}           //wait for pooling
    *x = ADC14->MEM[5];
    *y = ADC14->MEM[6];
    *z = ADC14->MEM[7];
    
}

uint16_t read_temp(void)
{
    ADC14->CTL0 &=  ~ADC14_CTL0_ENC;                     //enc conifg.
    ADC14->CTL0 |=  ADC14_CTL0_SC | ADC14_CTL0_ENC;      //start conversation
    while(!ADC14->IFGR0 & ADC14_IFGR0_IFG0){}
    return ADC14->MEM[0];
}

void better_control(uint16_t *x, uint16_t *y, uint16_t *z)
{
    /*
        in exercise 17 we need to fix the speed position.
    */
    uint16_t x_ = 0;
    uint16_t y_ = 0;
    uint16_t x_max = 16265;
    uint16_t x_min = 26;
    uint16_t x_max_zero = 8500;
    uint16_t x_min_zero = 8200;
    uint16_t y_max = 16265;
    uint16_t y_min = 0;
    uint16_t y_max_zero = 8500;
    uint16_t y_min_zero = 8000;
    uint16_t sensitivity = 40;

    read_joystick(&x_, &y_);
    printf("x:%d,y:%d \n",x_,y_);
    if (x_>x_max_zero)  
    {
        *x = (127*(x_ - x_max_zero))/(sensitivity*(x_max - x_max_zero));
    }
    if (x_<x_min_zero)
    {
        *x = (-128*(x_ - x_min))/(sensitivity*(x_min_zero - x_min));
    }
    if (y_>y_max_zero)
    {
        *y = (127*(y_ - y_max_zero))/(sensitivity*(y_max - y_max_zero));
    }
    if (y_<y_min_zero)
    {
        *y = (-128*(y_ - y_min))/(sensitivity*(y_min_zero - y_min));
    }
    *z = check_and_clear_bj_flag();
}

float convert_to_volts(uint16_t reading)
{
    float voltage = (float)reading * VREF / ADC_RES;    //V = Vref × ADC_output_value / (2^n - 1)
//    printf("Voltage: %.5f \n",voltage);
    return voltage;
}

float convert_to_Celsius(float volts)
{
    float Celsius = (volts - 0.75)/0.01 + TEMP_OFFSET;
//    printf("Celsius: %.5f \n",Celsius);
    return Celsius;
}

void all_values_temp(uint16_t* ADC_value, float* voltage, float* Celsius)
{

    *ADC_value = read_temp();
    *voltage = convert_to_volts(*ADC_value);
    *Celsius = convert_to_Celsius(*voltage);

}


extern void ADC14_IRQHandler(void)
{

    if (ADC14->IFGR0 & ADC14_IFGR0_IFG0)                 //ADC14MEM0 interrupt flag
    {
        temp = ADC14->MEM[0];     
        ADC14->CLRIFGR0 |= ADC14_CLRIFGR0_CLRIFG0;       //clear the flags;
    }
    
}
