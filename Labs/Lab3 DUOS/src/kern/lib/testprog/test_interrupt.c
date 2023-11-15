#include <test_interrupt.h>
static uint32_t GLOBAL_COUNT_EXTI0 = 0;




void blinky_test_code(void){
	uint16_t gpio_pin = 5;
    GPIO_InitTypeDef gpio_init = {1 << gpio_pin,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FREQ_VERY_HIGH,0};
    GPIO_Init(GPIOA,&gpio_init);
	while(1){
		GPIOA->BSRR |= 0x1U << gpio_pin;
		__delay_ms(500);
		GPIOA->BSRR |= 0x1U << (gpio_pin+16U);
		__delay_ms(500);
	}
}

void test_set_get_priority(void){
	for(int iprio = 9;iprio >= 6;iprio--){
		kprintf("Setting EXTI0 priority to : %d\n",iprio);
		__NVIC_SetPriority(EXTI0_IRQn,iprio);
		kprintf("Get_Priority of EXTI0 IRQn: %d\n",__NVIC_GetPriority(EXTI0_IRQn));
	}
}




void test_masking(void){
	kprintf("Setting Fault Mask\n");

	kprintf("Before Setting Fault Mask\nSysTick Works Fine\n");
	__SysTick_init(1000);
	kprintf("(__GetTime Before) 1 : %d\n",__getTime());
	int temp = 10000000;
	while(temp--)asm("NOP");
	kprintf("(__GetTime Before) 2 : %d\n",__getTime());


	kprintf("Setting Fault Mask to 1\n");
	__set_FAULTMASK();
	kprintf("Faultmask Value (get) : %d\n",__get_FAULTMASK());
	kprintf("After Setting Fault Mask\nSysTick Does not Work\n");
	__SysTick_init(1000);

	kprintf("(__GetTime After) 1 : %d\n",__getTime());
	temp = 10000000;
	while(temp--)asm("NOP");
	kprintf("(__GetTime After) 2 : %d\n",__getTime());
	kprintf("Systick Get Time should not work\n");

}


void test_hardfault(void){
	//read an address 0x20CDCDCD
	kprintf("Reading an address 0x20CDCDCD (which does not exist)\n");
	uint32_t *ptr = (uint32_t *)0x20CDCDCD;
	uint32_t val = *ptr;
	kprintf("Value at address 0x20CDCDCD : %d\n",*ptr);
}

void test_sys_tick(void){
	kprintf("Systick Works fine\n");
	for(int i = 0;i < 5;i++){
		kprintf("Systick i : %d\n",i);
		__delay_ms(1000);
	}

	kprintf("Setting SysTick Priority to 12\n");
	__NVIC_SetPriority(SysTick_IRQn,12);

	kprintf("(GET)Systick Priority>> : %d\n",__NVIC_GetPriority(SysTick_IRQn));
	kprintf("Setting BASEPRI to 2\n");
	__set_BASEPRI(2);
	kprintf("Systick Should not work\n");
	//test systick handler
	__SysTick_init(1000);
	kprintf("(__GetTime) 1 : %d\n",__getTime());
	int temp = 10000000;
	while(temp--)asm("NOP");
	kprintf("(__GetTime) 2 : %d\n",__getTime());
	kprintf("Systick Get Time should not work\n");

	kprintf("Setting BASEPRI to 0\n");
	__set_BASEPRI(0);
	kprintf("Setting SysTick Priority to 0\n");
	__NVIC_SetPriority(SysTick_IRQn,0);
}

void test_all(void){
	int cmd;
	kprintf("================ Testing hardfault ================\n");
	kprintf("Do you want to test hardfault? (1/0)\n");
	kscanf("%d",&cmd);
	if(cmd == 1){
		kprintf("Testing hardfault\n");
		test_hardfault();
	}
	else{
		kprintf("Skipping hardfault\n");
	}

	kprintf("Do you want to test NVIC functions? (1/0)\n");
	kscanf("%d",&cmd);
	if(cmd == 0){
		return;
	}

	kprintf("________________Testing all________________\n");
	kprintf("===== Testing __NVIC_set/get_priority =====+\n");
	test_set_get_priority();

	

	//hardfault testing

	kprintf("===== Testing SysTick enable/disable using BASEPRI register=====+\n");
	test_sys_tick();

	kprintf("================ Testing interrupt masking ================\n");
	test_masking();

	
}