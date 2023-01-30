/*
 * ADC.c
 *
 */
#include "../include.h"


//////////lit todo puerto E y D para recibir señal, solo digo cunatos canales he d eleer

extern void ADC_config_modulo_0(void)
{
    /////////////// PINES
    // 1. RCGCADC
    SYSCTL->RCGCADC |= (1<<0) | (1<<1);
    // 2. RCGCGPIO
    SYSCTL->RCGCGPIO |= (1<<4); ///E
    SYSCTL->RCGCGPIO|= (1<<3); ///D
    // 3. GPIOFSEL
    GPIOE->AFSEL |= 0x0e;
    GPIOD->AFSEL |= 0x0e;
    // 4. GPIODEN
    GPIOE->DEN &= ~0x0e;
    GPIOD->DEN &= ~0x0e;
    // 5. GPIOAMSEL
    GPIOE->AMSEL |= 0x0e;
    GPIOD->AMSEL |= 0x0e;

    /////////////// SECUENCIADOR 0
    // 1. ADCACTSS
    ADC0->ACTSS &= ~(0x0f);
    // 2. ADCEMUX
    ADC0->EMUX |= 0x0000;
    // 3. ADCSSMUXn
    ADC0->SSMUX0 |= 0x00000210;
    // 4. ADCSSCTLn
    ADC0->SSCTL0 |= 0x00000644;
    // 5. ADCIM
    ADC0->IM |= (0xf<<16) | (0xf<<0);
    // 6. ADCPP y ADCPC
    //ADC0_PP_R |= 0x7
    ADC0->PC |= 0x3;
    // 7. ADCACTSS
    ADC0->ACTSS |= (1<<0);

    /////////////// SECUENCIADOR 1
      // 1. ADCACTSS
      ADC1->ACTSS &= ~(0x0f);
      // 2. ADCEMUX
      ADC1->EMUX |= 0x0000;
      // 3. ADCSSMUXn
      ADC1->SSMUX1 |= 0x0654;
      // 4. ADCSSCTLn
      ADC1->SSCTL1 |= 0x0644;
      // 5. ADCIM
      ADC1->IM|= (0xf<<16) | (0xf<<0);
      // 6. ADCPP y ADCPC
      //ADC0_PP_R |= 0x3
      ADC1->PC |= 0x3;
      // 7. ADCACTSS
      ADC1->ACTSS |=(1<<1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////// RECIBIR CHAR UART
extern void ADC_leer_canal(uint16_t data[])
{
    ////Selector 0
    ADC0->PSSI |= (1<<0);
    SysTick_espera(.001);

    while (ADC0->RIS & 0x01 == 0);
    SysTick_espera(.001);

    while(ADC0->SSOP0 & (1<<0) == (1<<0));
    data[0] = ADC0->SSFIFO0 & 0xfff;
    SysTick_espera(.001);
    while(ADC0->SSOP0 & (1<<4) == (1<<4));
    data[1] = ADC0->SSFIFO0 & 0xfff;
    SysTick_espera(.001);
    while(ADC0->SSOP0 & (1<<8) == (1<<8));
    data[2] = ADC0->SSFIFO0 & 0xfff;
    SysTick_espera(.001);

    ADC0->ISC |= (1<<0);
    SysTick_espera(.001);

    ////Selector 1
    ADC1->PSSI |= (1<<1);
    SysTick_espera(.001);

    while (ADC1->RIS & 0x02 == 0);
    SysTick_espera(.001);
    while(ADC1->SSOP1 & (1<<0) == (1<<0));
    data[3] = ADC1->SSFIFO1 & 0xfff;
    SysTick_espera(.001);
    while(ADC1->SSOP1 & (1<<4) == (1<<4));
    data[4] = ADC1->SSFIFO1 & 0xfff;
    SysTick_espera(.001);
    while(ADC1->SSOP1 & (1<<8) == (1<<8));
    data[5] = ADC1->SSFIFO1 & 0xfff;
    SysTick_espera(.001);

    ADC1->ISC |= (1<<1);
    SysTick_espera(.001);
}



