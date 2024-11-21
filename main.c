/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Utility.h"



void aula04_11(void){

	//void atraso(int valor) {
	//	while (valor) --valor;
	//}
	// RCC->AHB1ENR |= 1 << 4;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; // liga o clock do GPIOA >>> LIGA O ABHNER <<<
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;


		GPIOE->MODER &= ~(0b11 << 8); // CONFIGURA PE4 como entrada
		GPIOE->PUPDR |= 0b01 << 8; // habilita o pullup no pino 4

		GPIOE->MODER &= ~(0b11 << 6); // CONFIGURA PE4 como entrada
		GPIOE->PUPDR |= 0b01 << 6; // habilita o pullup no pino 3

		GPIOA->ODR |= 1 << 6; // desliga o LED inicialmente
		GPIOA->MODER |= 0b01 << 12; // configura pa6 como saida

		GPIOA->ODR |= 1 << 7; // desliga o LED inicialmente
		GPIOA->MODER |= 0b01 << 14; // configura pa7 como saida



		while(1)
		{
			uint16_t var = GPIOE->IDR & (1 << 4);
			if(var)
				GPIOA->ODR |= 1 << 6; // DESLIGA O LED
			else
				GPIOA->ODR &= ~(1 << 6);

			uint16_t var1 = GPIOE->IDR & (1 << 3);
			if(var1)
				GPIOA->ODR |= 1 << 7; // DESLIGA O LED
			else
				GPIOA->ODR &= ~(1 << 7);
		}
}

void aula05_11(void){


	// LIGANDO o clock do GPIOA e GPIOE
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);

	// CONFIGURANDO OS modos dos pinos
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

	// LIGANDO os resistores de pull-up
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	// ESTADO Inicial dos leds
	GPIO_Write_Pin(GPIOA, PIN_6, LOW);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);


	while(1){
		if(!GPIO_Read_Pin(GPIOE, PIN_3) == !GPIO_Read_Pin(GPIOE, PIN_4))
		{
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		}
		else
		{
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		}

	}


}

void aula6_11(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PA4 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);

	int tempo = 0;
	int incremento = 50;

	while(1){
		GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
		Delay_us(tempo);
		GPIO_Write_Pin(GPIOA, PIN_4, LOW);
		Delay_us(10000 - tempo);
		tempo = tempo + incremento;
		if (tempo == 10000) incremento = -incremento;
		if (tempo == 0) incremento = -incremento;
	}
}

void questao1(void){
	// inicia o sistema de clock
	Utility_Init();

	// configura PA4 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	// estado inicial dos leds
	GPIO_Write_Pin(GPIOA, PIN_6, LOW);

	while(1){
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		Delay_ms(100);
	}
}

void questao2(void){
	// CONfiguração basica
	Utility_Init();

	// configurando PA7 como SAIDA
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	// estado inicial
	GPIO_Write_Pin(GPIOA, PIN_7, LOW);

	while(1){
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		Delay_ms(1000);
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		Delay_ms(1000);
	}

}

void questao3(void){
	// inicia o sistema de clock
	Utility_Init();

	// configura PA6 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	// configura PA7 como saida
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	int tempo = 0;
	int incremento = 50;

	while(1){
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		Delay_us(tempo);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		Delay_us(10000 - tempo);
		tempo = tempo + incremento;
		if (tempo == 10000) incremento = -incremento;
		if (tempo == 0) incremento = -incremento;
	}
}

void questao4(void){
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	while(1){
		for(int i = 0; i < 256; i++){
			GPIO_Write_Port(GPIOA, i);
			Delay_ms(100);
		}
	}
}

void questao5(void){
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);



    while (1) {
        for (int i = 0; i < 8; i++) {
            GPIO_Write_Pin(GPIOA, i, HIGH);
            Delay_ms(100);
            GPIO_Write_Pin(GPIOA, i, LOW);
        }
        for (int i = 7; i >= 0; i--) {
            GPIO_Write_Pin(GPIOA, i, HIGH);
            Delay_ms(100);
            GPIO_Write_Pin(GPIOA, i, LOW);
        }
    }
}

void questao6(void) {
    Utility_Init();
    GPIO_Clock_Enable(GPIOA);

    // Configurando os pinos como saída
    GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); // Verde Semáforo 1
    GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); // Amarelo Semáforo 1
    GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT); // Vermelho Semáforo 1
    GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); // Verde Semáforo 2
    GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT); // Amarelo Semáforo 2
    GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT); // Vermelho Semáforo 2

    while (1) {
        GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
        GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
        Delay_ms(5000);
        GPIO_Write_Pin(GPIOA, PIN_2, LOW);

        GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
        Delay_ms(2000);
        GPIO_Write_Pin(GPIOA, PIN_1, LOW);

        GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
        GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
        GPIO_Write_Pin(GPIOA, PIN_3, LOW);
        Delay_ms(5000);
        GPIO_Write_Pin(GPIOA, PIN_5, LOW);

        GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
        Delay_ms(2000);
        GPIO_Write_Pin(GPIOA, PIN_4, LOW);

        GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
        GPIO_Write_Pin(GPIOA, PIN_0, LOW);
    }
}

void questao7(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PA6 e PA7 como saida
	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	// Decodificação de display de 7 segmentos com uso de máscaras em matriz
	const uint8_t mask[16]={ 0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A
	0b01111100, //B
	0b00111001, //C
	0b01011110, //D
	0b01111001, //E
	0b01110001 //F
	};

	while(1) {

		for (int i = 0; i < 16; i++) {
			GPIO_Write_Port(GPIOA, mask[i]);
			Delay_ms(300);
		}
        for (int i = 15; i >= 0; i--) {
        	GPIO_Write_Port(GPIOA, mask[i]);
            Delay_ms(300);
        }
    }
}

void questao9(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PE4 como saida
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_4, OUTPUT);

	int tempo = 0;
	int incremento = 50;

	while(1){
		GPIO_Write_Pin(GPIOE, PIN_4, HIGH);
		Delay_us(tempo);
		GPIO_Write_Pin(GPIOE, PIN_4, LOW);
		Delay_us(20000 - tempo);
		tempo = tempo + incremento;
		if (tempo == 2500) incremento = -incremento;
		if (tempo == 0) incremento = -incremento;
	}



}

void questao13(void){
	// inicia o sistema de clock
	Utility_Init();

	// configura PA6 e PA7 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	// configura PE3 e PE4 como entrada
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

	// LIGANDO os resistores de pull-up
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	while(1){
		if(GPIO_Read_Pin(GPIOE, PIN_3) == LOW)
		{
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		}
		else
		{
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		}
		if(GPIO_Read_Pin(GPIOE, PIN_4) == LOW)
		{
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		}
		else
		{
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		}
	}
}

void questao14(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PA6 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	// configura PE3 como entrada
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);

	// LIGANDO os resistores de pull-up
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

    // Estado inicial do LED
    GPIO_Write_Pin(GPIOA, PIN_6, HIGH);

    int estado_anterior = HIGH;

    while (1) {
        // Lê o estado atual do botão
        int estado_atual = GPIO_Read_Pin(GPIOE, PIN_3);

        // Detecta transição de HIGH para LOW (botão pressionado)
        if (estado_atual == LOW && estado_anterior == HIGH) {

            // Verifica novamente se o botão ainda está pressionado
            if (GPIO_Read_Pin(GPIOE, PIN_3) == LOW) {
                // Alterna o estado do LED
                if (GPIO_Read_Pin(GPIOA, PIN_6) == LOW) {
                    GPIO_Write_Pin(GPIOA, PIN_6, HIGH); // Liga o LED
                } else {
                    GPIO_Write_Pin(GPIOA, PIN_6, LOW); // Desliga o LED
                }
            }
        }

        // Atualiza o estado anterior
        estado_anterior = estado_atual;
    }
}

void questao15(void) {
	// LIGANDO o clock do GPIOA(leds) e GPIOE(buttoes)
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);

	// CONFIGURANDO OS modos dos pinos
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

	// LIGANDO os resistores de pull-up
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP); // k1
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP); // k0





	while(1){
		int k0_apertado = 0;
		int k1_apertado = 0;
		// ESTADO Inicial dos leds
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH); // inicia desligado

//		if (GPIO_Read_Pin(GPIOE, PIN_4) == LOW ) { // k0 quando pressionado guarda 1
//			k0_apertado = 1;
//		}
//		else{
//			k0_apertado = 0;
//		}
//		if (GPIO_Read_Pin(GPIOE, PIN_3) == LOW ) { // k1 quando pressionado guarda 1
//			k1_apertado = 1;
//		}
//		else{
//			k0_apertado = 1;
//		}

		if (!GPIO_Read_Pin(GPIOE, PIN_4) == 1) {
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			if (GPIO_Read_Pin(GPIOE, PIN_3) == LOW){ // quando k0 e k1 forem pressionados
				GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			}
		}
//		if (k1_apertado == 1) {
//			k0_apertado = 0;
//			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//			if (k0_apertado == 1){
//				GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//			}
//		}
	}
}


int main(void) {
	questao9();
};


