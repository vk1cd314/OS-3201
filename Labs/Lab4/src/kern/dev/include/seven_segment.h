#ifndef __SEVEN_SEGMENT_H
#define __SEVEN_SEGMENT_H

#include <gpio.h>
#include <stdint.h>
#include <cm4.h>

struct LED_PIN_INFO {
    GPIO_TypeDef* gpio;
    uint16_t pin;
};

static struct LED_PIN_INFO pin_info_table[7] = {
    {GPIOA,5},{GPIOA,6},{GPIOA,7},{GPIOA,8},{GPIOA,9},{GPIOA,10},{GPIOB,1}
};

static uint8_t digit_arr[10][7] = {
    {1,1,1,0,1,1,1}, //0
    {1,0,0,0,0,0,1}, //1
    {1,1,0,1,1,1,0}, //2
    {1,1,0,1,0,1,1}, //3
    {1,0,1,1,0,0,1}, //4
    {0,1,1,1,0,1,1}, //5
    {0,1,1,1,1,1,1}, //6
    {1,1,0,0,0,0,1}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}  //9
};

static GPIO_InitTypeDef gpio_init;

uint32_t module_init(void);
void module_exit(void);
void print_digit(uint8_t digit);

#endif