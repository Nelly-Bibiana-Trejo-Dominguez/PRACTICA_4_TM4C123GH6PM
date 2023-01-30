

/**
 * main.c
 */
#include "include.h"

#define canales            6   ///defino cuantos canales he d eleer
uint16_t adc_data[canales] = {0};// arreglos de enteros con 4 casillas
uint8_t i = 0;

char data_str[64] = " " ;

void Delay(void){
  unsigned long volatile time;
  time = 1000;
  while(time){
        time--;
  }
}



int main(void)
{

    SetSystemClock_MHz(_20MHZ); //_50 para el 1 20 para 2 y 3
    Configurar_UART3(19200,_20MHZ);
    Configurar_GPIO();



   ADC_config_modulo_0();

	while(1U){


 	    ADC_leer_canal(adc_data);
 	 //  Delay();
        duty0 =  adc_data[0] ; /// E3
        duty1 =  adc_data[1] ; ///E2
        duty2 =  adc_data[2] ; ///E1
        duty3 =  adc_data[3] ; ///D3
        duty4 =  adc_data[4] ; /// D2
        duty5 =  adc_data[5] ; ///D1


        ///////////////////// enviar datos

///////comentar o descomentar para saber cuál graficar.
    /*  sprintf(data_str, "%04u", duty0);
        Tx_string(data_str); */
       /*  sprintf(data_str, "%04u", duty1);
           Tx_string(data_str); */
             sprintf(data_str, "%04u", duty2);
               Tx_string(data_str);
            /*   sprintf(data_str, "%04u", duty3);
                  Tx_string(data_str); */
                /*   sprintf(data_str, "%04u", duty4);
                      Tx_string(data_str); */
                    /*   sprintf(data_str, "%04u", duty5);
                         Tx_string(data_str); */



	}
}


