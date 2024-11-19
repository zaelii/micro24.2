/*
 * Utility.h para o STM32CubeIDE
 *
 *  Created on: 12 de out de 2024
 *      Author: Prof. Dr. Fagner de Araujo Pereira
 */

#ifndef UTILITY_H_
#define UTILITY_H_

//Definições Globais

//definições dos números dos pinos GPIO
#define PIN_0	((uint8_t) 0)
#define PIN_1	((uint8_t) 1)
#define PIN_2	((uint8_t) 2)
#define PIN_3	((uint8_t) 3)
#define PIN_4	((uint8_t) 4)
#define PIN_5	((uint8_t) 5)
#define PIN_6	((uint8_t) 6)
#define PIN_7	((uint8_t) 7)
#define PIN_8	((uint8_t) 8)
#define PIN_9	((uint8_t) 9)
#define PIN_10	((uint8_t) 10)
#define PIN_11	((uint8_t) 11)
#define PIN_12	((uint8_t) 12)
#define PIN_13	((uint8_t) 13)
#define PIN_14	((uint8_t) 14)
#define PIN_15	((uint8_t) 15)

//definições dos modos de operação de um pino GPIO
#define	INPUT		((uint8_t) 0b00)	//modo de entrada digital
#define	OUTPUT		((uint8_t) 0b01)	//modo de saída digital
#define	ALTERNATE	((uint8_t) 0b10)	//modo de função alternativa
#define	ANALOG		((uint8_t) 0b11)	//modo analógico

//definições dos tipos de saída de um pino GPIO
#define	PUSH_PULL	((uint8_t) 0)	//saída push-pull
#define	OPEN_DRAIN	((uint8_t) 1)	//saída open-drain

//definições para o nível lógico de saída de um pino
#define	LOW		((uint8_t) 0b0)	//nível lógico baixo
#define	HIGH	((uint8_t) 0b1)	//nível lógico alto

//definições dos modos de operação dos resistores de pull-up e pull-down
#define	PULL_UP		((uint8_t) 0b01)	//resistor de pull-up
#define	PULL_DOWN	((uint8_t) 0b10)	//resistor de pull-down


//Declarações de funções úteis

//Funções de configuração do sistema de clock do STM32
void Utility_Init(void);		//inicialização de funções da biblioteca
void Configure_Clock(void);		//configuração do sistema de clock

//Funções de timers e temporização
void TIM2_Setup(void);				//configuração do Timer2 como base de tempo de 1us
void Delay_us(uint32_t delay);		//atraso em us
void Delay_ms(uint32_t delay);		//atraso em ms

//Funções de manipulação de GPIO
void GPIO_Clock_Enable(GPIO_TypeDef* GPIOx);								//habilita o clock de um GPIO
void GPIO_Pin_Mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);			//configura o modo de operação de um pino de um GPIO
void GPIO_Output_Mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);		//configura o tipo de saída de um pino de um GPIO
static inline void GPIO_Write_Pin(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t level);		//escreve um nível lógico em um pino de um GPIO
static inline void GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx, uint8_t pin);						//inverte o nível lógico em um pino de um GPIO
static inline void GPIO_Write_Port(GPIO_TypeDef* GPIOx, uint16_t value);					//escreve um valor numa porta GPIO
void GPIO_Resistor_Enable(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);	//habilita os resistores de pull-up ou pull-down
static inline uint8_t GPIO_Read_Pin(GPIO_TypeDef* GPIOx, uint8_t pin);					//lê e retorna o nível lógico em um pino de um GPIO
static inline uint16_t GPIO_Read_Port(GPIO_TypeDef* GPIOx);								//lê e retorna os níveis lógicos de uma porta GPIO

//Funções de periféricos de comunicação
void USART1_Init(void);				//configuração da USART1 para debug com printf

//Funções de geração de números aleatórios
uint32_t Random_Number(void);		//retorna um número aleatório de 32 bits


//Funções de configuração do sistema de clock do STM32
//Inicialização de funções da biblioteca
void Utility_Init(void)
{
	Configure_Clock();	//inicializa o sistema de clock
	TIM2_Setup();		//configura o Timer2 como base de tempo de 1us
}

//Configuração do sistema de clock para velocidade máxima em todos os barramentos utilizando um cristal externo de 8MHz
//HCLK = 168 MHz
//APB1 = 42 MHz
//APB2 = 84 MHz
//USB, RNG, SDIO = 48 MHz
void Configure_Clock(void)
{
	//Parâmetros do PLL principal
	#define PLL_M	4
	#define PLL_N	168
	#define PLL_P	2
	#define PLL_Q	7

	//Configurações da Flash e do regulador de tensão para permitir operação em alta velocidade
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;	//habilita prefetch, caches e a latência da flash
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;	//habilita o clock da interface de energia
	PWR->CR |= PWR_CR_VOS;				//regulador de tensão no modo 2

	//Configuração do modo de agrupamento de prioridades das interrupções
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//Reseta os registradores do módulo RCC para o estado inicial
	RCC->CIR = 0;				//desabilita todas as interrupções de RCC
	RCC->CR |= RCC_CR_HSION;	//liga o oscilador HSI
	RCC->CFGR = 0;				//reseta o registrador CFGR
	//Desliga HSE, CSS e o PLL e o bypass de HSE
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON | RCC_CR_HSEBYP);
	RCC->PLLCFGR = 0x24003010;	//reseta o registrador PLLCFGR

	//Configura a fonte de clock (HSE), os parâmetros do PLL e prescalers dos barramentos AHB, APB
	RCC->CR |= RCC_CR_HSEON;				//habilita HSE
	while(!((RCC->CR) & RCC_CR_HSERDY));	//espera HSE ficar pronto
    RCC->CFGR |= 0x9400;	//HCLK = SYSCLK/1, PCLK2 = HCLK/2, PCLK1 = HCLK/4

    //Configura a fonte de clock e os parâmetros do PLL principal
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (0x400000) | (PLL_Q << 24);

    RCC->CR |= RCC_CR_PLLON;			//habilita o PLL
    while(!(RCC->CR & RCC_CR_PLLRDY));	//espera o PLL ficar pronto verificando a flag PLLRDY

    RCC->CFGR |= 0x2;					//seleciona o PLL como fonte de SYSCLK
    while((RCC->CFGR & 0xC) != 0x8);	//espera o PLL ser a fonte de SYSCLK
}


//Funções de timers e temporização
//Configura o timer 2 como base de tempo de 1us
void TIM2_Setup(void)
{
	//O modo padrão do contador é com contagem crescente
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	//liga o clock do Timer2
	TIM2->PSC = 83;						//prescaler para incrementos a cada 1uS
	TIM2->EGR = TIM_EGR_UG;				//update event para escrever o valor do prescaler
	TIM2->CR1 |= TIM_CR1_CEN;			//habilita o timer
}

//Criação de atraso em us
void Delay_us(uint32_t delay)
{
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < delay);	//aguarda o tempo passar
}

//Criação de atraso em ms
void Delay_ms(uint32_t delay)
{
	uint32_t max = 1000*delay;
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < max);		//aguarda o tempo passar
}


//Funções de manipulação de GPIO
//Habilita o clock de um GPIO
void GPIO_Clock_Enable(GPIO_TypeDef* GPIOx)
{
	RCC->AHB1ENR |= (1 << ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE)));
}

//Configura o modo de operação de um pino de um GPIO
void GPIO_Pin_Mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode)
{
	GPIOx->MODER &= ~(0b11 << 2*pin);	//reseta os 2 bits do modo de operação
	GPIOx->MODER |= (mode << 2*pin);	//configura o modo selecionado
}

//Configura o tipo de saída de um pino de um GPIO
void GPIO_Output_Mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode)
{
	GPIOx->OTYPER &= ~(1 << pin);	//reseta o tipo de saída
	GPIOx->OTYPER |= (mode << pin);	//configura o tipo selecionado
}

//Escreve um nível lógico em um pino de um GPIO
static inline void GPIO_Write_Pin(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t level)
{
	if(level)
		GPIOx->ODR |= (1 << pin);	//nível alto no pino
	else
		GPIOx->ODR &= ~(1 << pin);	//nível baixo no pino
}

//Inverte o nível lógico em um pino de um GPIO
static inline void GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	GPIOx->ODR ^= (1 << pin);	//inverte o nível lógico no pino
}

//Escreve um valor numa porta GPIO
static inline void GPIO_Write_Port(GPIO_TypeDef* GPIOx, uint16_t value)
{
	GPIOx->ODR = value;
}

//Habilita os resistores de pull-up ou pull-down
void GPIO_Resistor_Enable(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode)
{
	GPIOx->PUPDR &= ~(0b11 << 2*pin);	//desabilita qualquer resistor
	GPIOx->PUPDR |= (mode << 2*pin);	//configura o resistor selecionado
}

//Lê e retorna o nível lógico em um pino de um GPIO
static inline uint8_t GPIO_Read_Pin(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	if(GPIOx->IDR & (1 << pin))
		return 1;
	return 0;
}

//Lê e retorna os níveis lógicos de uma porta GPIO
static inline uint16_t GPIO_Read_Port(GPIO_TypeDef* GPIOx)
{
	return GPIOx->IDR;
}


//Funções de periféricos de comunicação
//Configuração básica da USART1
void USART1_Init(void)
{
	//Configuração da USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;				//habilita o clock da USART1
	USART1->BRR = 84;									//ajusta baud rate para 1 Mbps (frequência do periférico de 84MHz)
	//O estado default do registrador USART1->CR1 garante:
	//1 stop bit, 8 bits de dados, sem bit de paridade,
	//oversampling de 16 amostras por bit
	USART1->CR1 |= (USART_CR1_TE | USART_CR1_UE);		//habilita apenas o transmissor e a USART1
	//USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE);	//habilita o transmissor, receptor, interrupção de RX e a USART1

	//Habilita a interrupção da USART1 no NVIC
	//NVIC_SetPriority(USART1_IRQn, 0);	//seta a prioridade da USART1
	//NVIC_EnableIRQ(USART1_IRQn);		//habilita a interrupção da USART1

	//Configuração dos pinos PA9 (TX) e PA10(RX)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;			//habilita o clock do GPIOA
	GPIOA->MODER |= (0b10 << 20) | (0b10 << 18);	//pinos PA10 e PA9 em função alternativa
	GPIOA->AFR[1] |= (0b0111 << 8) | (0b0111 << 4);	//função alternativa 7 (USART1)
}

//Redefinição da função de envio de dados pela USART1
int __io_putchar(int ch)
{
	USART1->DR = ch;						//transmite o dado
	while (!(USART1->SR & USART_SR_TXE));	//espera pelo fim da transmissão
	return ch;
}

//Redefinição da função de recebimento de dados pela USART1
int __io_getchar(void)
{
   return (uint16_t)(USART1->DR);	//lê o dado recebido
}

//ISR da USART1. Todas as ISR's estão definidas no arquivo startup_stm32f407vetx.s
void USART1_IRQHandler(void)
{
	__io_putchar(__io_getchar());	//lê o dado e reenvia pela USART1
}


//Funções de geração de números aleatórios
//Retorna um número aleatório de 32 bits
uint32_t Random_Number(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;	//habilita o clock do RNG
	RNG->CR |= RNG_CR_RNGEN;			//liga o RNG
	while(!(RNG->SR & RNG_SR_DRDY));	//aguarda um número aleatório estar pronto
	(void)RNG->DR;						//despreza o primeiro número aleatório gerado
	while(!(RNG->SR & RNG_SR_DRDY));	//aguarda novo número aleatório estar pronto
	RNG->CR &= ~RNG_CR_RNGEN;			//desliga o RNG
	return RNG->DR;						//retorna o número aleatório
}


#endif /* UTILITY_H_ */
