/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Utility.h"
#include "LCD_Blio.h"
#include "stdio.h"

int main(void) {
	Utility_Init();
	USART1_Init();

	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);

	while(1)
	{
		uint16_t leitura = ADC_GetSingleConversion(ADC1);
		
		printf("Valor lido = %d\n", leitura);
		Delay_ms(200);
	}


	return 0;

}
