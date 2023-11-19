#include <sys.h>

void EXTI_GPIO_Config(GPIO_TypeDef* gpio,uint16_t pin){
	GPIO_InitTypeDef gpio_init;
	gpio_init.Mode = GPIO_MODE_INPUT;
	gpio_init.Pull = GPIO_PULLUP;
	gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_init.Pin = 1 << pin;

	GPIO_Init(gpio,&gpio_init);
}

void EXTI0_Init(void){
	RCC->APB2ENR |= 1<<14; //enable SYSCFG clock
	SYSCFG->EXTICR[0] &= ~(0x000F<<0); //select PA0 as source of EXTI0
	EXTI->IMR |= 1<<0; //unmask EXTI0
	EXTI->RTSR |= 1<<0; //select rising edge trigger
	EXTI->FTSR &= ~(1<<0); //disable falling edge trigger
	__NVIC_EnableIRQn(EXTI0_IRQn); //enable EXTI0 interrupt
	
}

void EXTI1_Init(void){
    RCC->APB2ENR |= 1<<14; //enable SYSCFG clock
    SYSCFG->EXTICR[0] &= ~(0x000F<<4); //select PA1 as source of EXTI1
    EXTI->IMR |= 1<<1; //unmask EXTI1
    EXTI->RTSR |= 1<<1; //select rising edge trigger
    EXTI->FTSR &= ~(1<<1); //disable falling edge trigger
    __NVIC_EnableIRQn(EXTI1_IRQn); //enable EXTI1 interrupt
}