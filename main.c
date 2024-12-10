/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Utility.h"
#include "LCD_Blio.h"

void aula04_11(void) {

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

	while (1) {
		uint16_t var = GPIOE->IDR & (1 << 4);
		if (var)
			GPIOA->ODR |= 1 << 6; // DESLIGA O LED
		else
			GPIOA->ODR &= ~(1 << 6);

		uint16_t var1 = GPIOE->IDR & (1 << 3);
		if (var1)
			GPIOA->ODR |= 1 << 7; // DESLIGA O LED
		else
			GPIOA->ODR &= ~(1 << 7);
	}
}

void aula05_11(void) {

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

	while (1) {
		if (!GPIO_Read_Pin(GPIOE, PIN_3) == !GPIO_Read_Pin(GPIOE, PIN_4)) {
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		} else {
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

	while (1) {
		GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
		Delay_us(tempo);
		GPIO_Write_Pin(GPIOA, PIN_4, LOW);
		Delay_us(10000 - tempo);
		tempo = tempo + incremento;
		if (tempo == 10000)
			incremento = -incremento;
		if (tempo == 0)
			incremento = -incremento;
	}
}

void questao1ok(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PA4 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	// estado inicial dos leds
	GPIO_Write_Pin(GPIOA, PIN_6, LOW);

	while (1) {
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		Delay_ms(100);
	}
}

void questao2ok(void) {
	// CONfiguração basica
	Utility_Init();

	// configurando PA7 como SAIDA
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	// estado inicial
	GPIO_Write_Pin(GPIOA, PIN_7, LOW);

	while (1) {
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

void questao3ok(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PA6 como saida
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	// configura PA7 como saida
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	int tempo = 0;
	int incremento = 50;

	while (1) {
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		Delay_us(tempo);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		Delay_us(10000 - tempo);
		tempo = tempo + incremento;
		if (tempo == 10000)
			incremento = -incremento;
		if (tempo == 0)
			incremento = -incremento;
	}
}

void questao4ok(void) {
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
		for (int i = 0; i < 256; i++) {
			GPIO_Write_Port(GPIOA, i);
			Delay_ms(100);
		}
	}
}

void questao5ok(void) {
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

void questao6ok(void) {
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

void questao7ok(void) {
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
	const uint8_t mask[16] = { 0b00111111, //0
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

	while (1) {

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

void questao8 (void)
{
	char str[3];
	Utility_Init();
	LCD_Init(4, 20);

	while(1)
	{
		for (int i = 10; i > 0; i--)
		{
			LCD_Write_String(1, 3, "Ola");
			LCD_Write_String(2, 3, "Linkedin");
			LCD_Write_String(3, 3, ":)");

			sprintf(&str, "%d", i);
			LCD_Write_String(4, 9, str);
			Delay_ms(250);
			LCD_Clear();
		}
	}
}

void questao9ok(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PE4 como saida
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_4, OUTPUT);

	int tempo = 0;
	int incremento = 50;

	while (1) {
		GPIO_Write_Pin(GPIOE, PIN_4, HIGH);
		Delay_us(tempo);
		GPIO_Write_Pin(GPIOE, PIN_4, LOW);
		Delay_us(20000 - tempo);
		tempo = tempo + incremento;
		if (tempo == 2500)
			incremento = -incremento;
		if (tempo == 0)
			incremento = -incremento;
	}
}

void questao10ok(void){
	Utility_Init();
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (0B01 << 0) | (0B01 << 2) | (0B01 << 4);

	GPIOA->ODR |= (1 << 0);
	GPIOA->ODR &= ~(1 << 1);

	while(1){

		for (int i = 1; i < 2000; i += 20) {
			GPIOA->ODR &= ~(1 << 2);
			Delay_us(20000 - i);
			GPIOA->ODR |= (1 << 2);
			Delay_us(i);
		}

		for (int i = 2000; i > 1; i -= 20) {
			GPIOA->ODR |= (1 << 2);
			Delay_us(i);
			GPIOA->ODR &= ~(1 << 2);
			Delay_us(20000 - i);
		}


		GPIOA->ODR &= ~(1 << 2);
		Delay_ms(100);

		GPIOA->ODR &= ~(1 << 0);
		GPIOA->ODR |= (1 << 1);

		for (int i = 1; i < 2000; i += 20) {
			GPIOA->ODR &= ~(1 << 2);
			Delay_us(20000 - i);
			GPIOA->ODR |= (1 << 2);
			Delay_us(i);
		}

		for (int i = 2000; i > 1; i -= 20) {
			GPIOA->ODR |= (1 << 2);
			Delay_us(i);
			GPIOA->ODR &= ~(1 << 2);
			Delay_us(20000 - i);
		}

		GPIOA->ODR |= (1 << 0);
		GPIOA->ODR &= ~(1 << 1);

	}
}

void questao11ok(void) {
	// inicia o sistema de clock
	Utility_Init();

	// configura PA4 como entrada
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_4, INPUT);
	GPIO_Resistor_Enable(GPIOA, PIN_4, PULL_UP);

	// configura PA5 como saida
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	GPIO_Output_Mode(GPIOA, PIN_7, OPEN_DRAIN);

	while (1) {
		if (GPIO_Read_Pin(GPIOA, PIN_4) == HIGH) {
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		} else {
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		}
	}
}

void questao13ok(void) {
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

	while (1) {
		if (GPIO_Read_Pin(GPIOE, PIN_3) == LOW) {
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		} else {
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		}
		if (GPIO_Read_Pin(GPIOE, PIN_4) == LOW) {
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		} else {
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		}
	}
}

void questao14ok(void) {
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

void questao15ok(void){
	Utility_Init();
	    RCC -> AHB1ENR |= (1 << 0) | (1 << 4);
	    GPIOA -> MODER |= (0b01 << 12) ;
	    GPIOE -> PUPDR |= (0b01 << 6) | (0b01 << 8);

	    int k1, k0;

	    while(1){
	        k1 = !(GPIOE->IDR & (1 << 3));
	        k0 = !(GPIOE->IDR & (1 << 4));
	        if(k1){
	            continue;
	        }

	        if(k0){
	            while(k0){
	            k0 = !(GPIOE->IDR & (1 << 4));
	            k1 = !(GPIOE->IDR & (1 << 3));

	            if(k1 && k0){
	                GPIOA->ODR &= ~(1 << 6);
	                }else GPIOA->ODR |= (1 << 6);
	            }
	        }
	        GPIOA->ODR |= (1 << 6);
	        k1 = k0 = 0;
	    }
}

void questao16ok(void) {
	Utility_Init();

	#define k0 ! (GPIOE -> IDR & (1<<4))
	#define k1 ! (GPIOE -> IDR & (1<<3))

	RCC->AHB1ENR |= (1 << 0);
	RCC->AHB1ENR |= (1 << 4);

	GPIOA ->MODER |= (0B01 <<12);
	GPIOE ->MODER &= ~(0B01 <<6);
	GPIOE ->PUPDR |= (0B01 <<6);
	GPIOE ->MODER &= ~(0B01 <<8);
	GPIOE ->PUPDR |= (0B01 <<8);

	while (1){
		(GPIOA->ODR |= (1 << 6));


		if (k0 && !k1){
			uint32_t a = 0;
			while (k0){
				Delay_ms(200);
				if (k1){
					if (a<= 1000){
						(GPIOA->ODR &= ~(1 << 6));


					}
				} else
					(GPIOA->ODR |= (1 << 6));
				a += 500;
			}
		}
	}
}

void questao17ok(void) {
	// Inicia o sistema de clock
	Utility_Init();

	// Configura GPIOs dos botões
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT); // Botão aumentar k0
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT); // Botão diminuir k1

	// Ativa resistores de pull-up
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	// Configura o pino de saída para o PWM do servomotor
	GPIO_Pin_Mode(GPIOE, PIN_6, OUTPUT);

	int tempo = 1500;
	int incremento = 50;
	int delayMovimento = 20;

	while (1) {
		if (GPIO_Read_Pin(GPIOE, PIN_3) == LOW) {
			if (tempo + incremento <= 2500) {
				tempo += incremento;
			}
			GPIO_Write_Pin(GPIOE, PIN_6, HIGH);
			Delay_us(tempo);
			GPIO_Write_Pin(GPIOE, PIN_6, LOW);
			Delay_us(20000 - tempo);
			Delay_ms(delayMovimento);
		}

		if (GPIO_Read_Pin(GPIOE, PIN_4) == LOW) {
			if (tempo - incremento >= 500) {
				tempo -= incremento;
			}
			GPIO_Write_Pin(GPIOE, PIN_6, HIGH);
			Delay_us(tempo);
			GPIO_Write_Pin(GPIOE, PIN_6, LOW);
			Delay_us(20000 - tempo);
			Delay_ms(delayMovimento);
		}
	}
}

void questao18ok(void) {
    // Inicia o sistema de clock
    Utility_Init();

    // Configura GPIOE PIN_5 a PIN_8 como entrada com resistor pull-up
    GPIO_Clock_Enable(GPIOE);
    GPIO_Pin_Mode(GPIOE, PIN_5, INPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_5, PULL_UP);
    GPIO_Pin_Mode(GPIOE, PIN_6, INPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_6, PULL_UP);
    GPIO_Pin_Mode(GPIOE, PIN_7, INPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_7, PULL_UP);
    GPIO_Pin_Mode(GPIOE, PIN_8, INPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_8, PULL_UP);

    // Configura GPIOE PIN_1 a PIN_4 como saída em modo open-drain
    GPIO_Pin_Mode(GPIOE, PIN_1, OUTPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_1, PULL_UP);
    GPIO_Output_Mode(GPIOE, PIN_1, OPEN_DRAIN);
    GPIO_Pin_Mode(GPIOE, PIN_2, OUTPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_2, PULL_UP);
    GPIO_Output_Mode(GPIOE, PIN_2, OPEN_DRAIN);
    GPIO_Pin_Mode(GPIOE, PIN_3, OUTPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
    GPIO_Output_Mode(GPIOE, PIN_3, OPEN_DRAIN);
    GPIO_Pin_Mode(GPIOE, PIN_4, OUTPUT);
    GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
    GPIO_Output_Mode(GPIOE, PIN_4, OPEN_DRAIN);

    // Configura GPIOD PIN_0 a PIN_6 como saída
    GPIO_Clock_Enable(GPIOD);
    GPIO_Pin_Mode(GPIOD, PIN_0, OUTPUT);
    GPIO_Pin_Mode(GPIOD, PIN_1, OUTPUT);
    GPIO_Pin_Mode(GPIOD, PIN_2, OUTPUT);
    GPIO_Pin_Mode(GPIOD, PIN_3, OUTPUT);
    GPIO_Pin_Mode(GPIOD, PIN_4, OUTPUT);
    GPIO_Pin_Mode(GPIOD, PIN_5, OUTPUT);
    GPIO_Pin_Mode(GPIOD, PIN_6, OUTPUT);

    // Máscara para números/hexadecimais
    const uint8_t mask[16] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111, // 9
        0b01110111, // A
        0b01111100, // B
        0b00111001, // C
        0b01011110, // D
        0b01111001, // E
        0b01110001  // F
    };

    // Mapeamento do teclado matricial
    const uint8_t key_map[4][4] = {
        {1, 2, 3, 10},  // 10 é 'A'
        {4, 5, 6, 11},  // 11 é 'B'
        {7, 8, 9, 12},  // 12 é 'C'
        {14, 0, 15, 13} // 14 é 'E', 15 é 'D'
    };

    while (1) {
        for (int row = 0; row < 4; row++) {
            // Seleciona a linha
            GPIO_Write_Pin(GPIOE, PIN_1 + row, LOW);

            for (int col = 0; col < 4; col++) {
                // Lê o estado do pino da coluna
                if (!GPIO_Read_Pin(GPIOE, PIN_5 + col)) {
                    uint8_t key = key_map[row][col];
                    if (key < 16) {
                        GPIO_Write_Port(GPIOD, mask[key]); // Mostra o número
                        Delay_ms(300); // Evita múltiplas leituras
                    }
                }
            }

            // Reseta a linha
            GPIO_Write_Pin(GPIOE, PIN_1 + row, HIGH);
        }
    }
}

void questao20(void) {
    // Habilita o clock para o GPIOC
    RCC->AHB1ENR |= (1 << 2);

    // Configura pinos PC0 a PC3 como saída (LEDs)
    GPIOC->MODER |= (0b01 << 0) | (0b01 << 2) | (0b01 << 4) | (0b01 << 6);

    // Configura pinos PC4 a PC7 como entrada (botões)
    GPIOC->MODER &= ~((0b11 << 8) | (0b11 << 10) | (0b11 << 12) | (0b11 << 14));
    GPIOC->PUPDR |= (0b01 << 8) | (0b01 << 10) | (0b01 << 12) | (0b01 << 14);

    // Sequência inicial de LEDs (0 a 3)
    int sequencia[7] = {0, 1, 2, 0, 1, 2, 3};
    int jogador[7];  // Armazena as entradas do jogador
    int parada = 0;
    int contador = 0;

    while (1) {
        // Mostrar a sequência para o jogador
        for (int i = 0; i <= contador; i++) {
            if (sequencia[i] == 0) {
                GPIOC->ODR |= (1 << 0);  // Acende LED Vermelho (PC0)
                Delay_ms(500);
                GPIOC->ODR &= ~(1 << 0); // Apaga LED Vermelho
                Delay_ms(500);
            } else if (sequencia[i] == 1) {
                GPIOC->ODR |= (1 << 1);  // Acende LED Azul (PC1)
                Delay_ms(500);
                GPIOC->ODR &= ~(1 << 1); // Apaga LED Azul
                Delay_ms(500);
            } else if (sequencia[i] == 2) {
                GPIOC->ODR |= (1 << 2);  // Acende LED Verde (PC2)
                Delay_ms(500);
                GPIOC->ODR &= ~(1 << 2); // Apaga LED Verde
                Delay_ms(500);
            } else if (sequencia[i] == 3) {
                GPIOC->ODR |= (1 << 3);  // Acende LED Amarelo (PC3)
                Delay_ms(500);
                GPIOC->ODR &= ~(1 << 3); // Apaga LED Amarelo
                Delay_ms(500);
            }
        }

        // Espera o jogador repetir a sequência pressionando os botões
        for (int i = 0; i <= contador; i++) {
            while (1) {
                int b0 = GPIOC->IDR & (1 << 4);  // Leitura do botão do LED Vermelho (PC4)
                int b1 = GPIOC->IDR & (1 << 5);  // Leitura do botão do LED Azul (PC5)
                int b2 = GPIOC->IDR & (1 << 6);  // Leitura do botão do LED Verde (PC6)
                int b3 = GPIOC->IDR & (1 << 7);  // Leitura do botão do LED Amarelo (PC7)

                if (!b0) {
                    GPIOC->ODR |= (1 << 0); // Acende LED Vermelho
                    jogador[i] = 0;  // Armazena a escolha do jogador
                    Delay_ms(300);
                    GPIOC->ODR &= ~(1 << 0); // Apaga LED Vermelho
                    break;
                } else if (!b1) {
                    GPIOC->ODR |= (1 << 1); // Acende LED Azul
                    jogador[i] = 1;  // Armazena a escolha do jogador
                    Delay_ms(300);
                    GPIOC->ODR &= ~(1 << 1); // Apaga LED Azul
                    break;
                } else if (!b2) {
                    GPIOC->ODR |= (1 << 2); // Acende LED Verde
                    jogador[i] = 2;  // Armazena a escolha do jogador
                    Delay_ms(300);
                    GPIOC->ODR &= ~(1 << 2); // Apaga LED Verde
                    break;
                } else if (!b3) {
                    GPIOC->ODR |= (1 << 3); // Acende LED Amarelo
                    jogador[i] = 3;  // Armazena a escolha do jogador
                    Delay_ms(300);
                    GPIOC->ODR &= ~(1 << 3); // Apaga LED Amarelo
                    break;
                }
            }

            // Verifica se a entrada do jogador está correta
            if (sequencia[i] != jogador[i]) {
                // Jogador errou, acende todos os LEDs em sinal de erro
                for (int j = 0; j < 3; j++) {
                    GPIOC->ODR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3); // Acende todos os LEDs
                    Delay_ms(500);
                    GPIOC->ODR &= ~(1 << 0) & ~(1 << 1) & ~(1 << 2) & ~(1 << 3); // Apaga todos os LEDs
                    Delay_ms(500);
                }
                parada = 1;  // A partida termina
                break;
            }
        }

        // Se o jogador errou, reinicia a sequência
        if (parada == 1) {
            // Reinicia a sequência
            for (int i = 0; i < 7; i++) {
                sequencia[i] = (i < 4) ? i : (i - 4);  // Exemplo de nova sequência
            }
            contador = 0;
            parada = 0;
        } else {
            // Caso o jogador acerte, aumenta a sequência
            contador++;
        }

        Delay_ms(2000);  // Espera entre as rodadas
    }
}

// Função para configurar os pinos GPIO para PWM (PD0 e PD1)
void GPIO_PWM_Config(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // Habilita o clock para o GPIOD

    // Configura PD0 e PD1 como funções alternativas (AF)
    GPIOD->MODER |= (0x02 << (0 * 2)) | (0x02 << (1 * 2));  // PD0 e PD1 como função alternativa
    GPIOD->AFR[0] |= (0x02 << (0 * 4)) | (0x02 << (1 * 4));  // Seleciona a função AF2 para TIM2_CH1 (PD0) e TIM2_CH2 (PD1)
}

// Função para configurar o Timer 2 para gerar PWM
void Timer_PWM_Config(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Habilita o clock do Timer 2

    // Configura o Timer 2 para PWM
    TIM2->PSC = 84 - 1;   // Prescaler para obter uma frequência de 1 kHz (considerando um clock de 84 MHz)
    TIM2->ARR = 1000 - 1;  // Período do PWM (1000 counts para 1 kHz)
    TIM2->CCR1 = 500;      // Duty cycle inicial para canal 1 (50%)
    TIM2->CCR2 = 500;      // Duty cycle inicial para canal 2 (50%)

    // Configura os canais para PWM
    TIM2->CCMR1 |= (0x06 << 4); // PWM mode, channel 1 (PD0)
    TIM2->CCMR1 |= (0x06 << 12); // PWM mode, channel 2 (PD1)
    TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;  // Habilita a saída PWM nos canais 1 e 2

    TIM2->CR1 |= TIM_CR1_CEN;  // Habilita o Timer 2
}


// Função que gira o motor em sentido horário ou anti-horário
void gira_motor(int delay, int sentido, int rotacoes) {
    // sentido = 1 -> Horário, sentido = 0 -> Anti-horário
    for (int a = 0; a < (50 * rotacoes); a++) {  // 50 passos por rotação (ajuste conforme necessário)

        if (sentido == 1) {
            // Gira o motor no sentido horário
            for (int i = 0; i < 4; i++) {
                GPIO_Write_Port(GPIOA, (1 << i));  // Envia sinal para os pinos
                Delay_ms(delay);  // Atraso entre os passos
            }
        } else if (sentido == 0) {
            // Gira o motor no sentido anti-horário
            for (int i = 0; i < 4; i++) {
                GPIO_Write_Port(GPIOA, (8 >> i));  // Envia sinal para os pinos
                Delay_ms(delay);  // Atraso entre os passos
            }
        }
    }
}




// Função que gira o motor em sentido horário ou anti-horário

void gira_motor(int delay, int sentido, int rotacoes) {

// sentido = 1 -> Horário, sentido = 0 -> Anti-horário

for (int a = 0; a < (50 * rotacoes); a++) {

if (sentido == 1) {

// Gira o motor no sentido horário

for (int i = 0; i < 4; i++) {

GPIO_Write_Port(GPIOA, (1 << i)); // Envia sinal para os pinos

Delay_ms(delay); // Atraso entre os passos

}

} else if (sentido == 0) {

// Gira o motor no sentido anti-horário

for (int i = 0; i < 4; i++) {

GPIO_Write_Port(GPIOA, (8 >> i)); // Envia sinal para os pinos

Delay_ms(delay); // Atraso entre os passos

}

}

}

}



int main(void) {

	// Inicializa utilitários e configura pinos

	Utility_Init();



	// Habilita o clock para GPIOA

	GPIO_Clock_Enable(GPIOA);



	// Configura os pinos como saídas (presumindo que esses pinos controlam o motor)

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); // INB1

	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); // INB2

	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT); // INA1

	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); // INA2



	// Loop principal

	while (1) {

	// Gira o motor no sentido horário por 2 rotações

	gira_motor(10, 1, 2);



	// Gira o motor no sentido anti-horário por 1 rotação

	gira_motor(10, 0, 1);

	}



return 0;

}
