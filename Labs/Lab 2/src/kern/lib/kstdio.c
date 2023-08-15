/*
 * Copyright (c) 2022
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <gpio.h>
#include <kstdio.h>
#include <kstring.h>
#include <stm32_peps.h>
#include <usart.h>
// #include<seven_segment.h>
/**
 * first argument define the type of string to kprintf and kscanf,
 * %c for charater
 * %s for string,
 * %d for integer
 * %x hexadecimal
 * %o octal number
 * %f for floating point number
 */

int hello[][7] = {{1, 1, 1, 1, 1, 1, 0},
                  {0, 1, 2, 0, 0, 0, 0},
                  {1, 1, 0, 1, 1, 0, 1},
                  {1, 1, 1, 1, 0, 0, 1},
                  {0, 1, 1, 0, 0, 1, 1},
                  {1, 0, 1, 1, 0, 1, 1},
                  {1, 0, 1, 1, 1, 1, 1},
                  {1, 1, 1, 0, 0, 0, 1},
                  {1, 1, 1, 1, 1, 1, 1},
                  {1, 1, 1, 1, 0, 1, 1}};

lul whot[7];

// Simplified version of printf
void kprintf(char *format, ...) {
    // write your code here
    char *tr;
    uint32_t i;
    uint8_t *str;
    va_list list;
    double dval;
    int flag = 0;
    va_start(list, format);
    int val = 0;
    for (tr = format; *tr != '\0'; tr++) {
        while (*tr != '%' && *tr != '\0') {
            UART_SendChar(USART2, *tr);
            tr++;
        }
        if (*tr == '\0') break;
        tr++;
        switch (*tr) {
            case 'c':
                i = va_arg(list, int);
                UART_SendChar(USART2, i);
                break;
            case 'd':
                i = va_arg(list, int);
                if (i < 0) {
                    UART_SendChar(USART2, '-');
                    i = -i;
                }
                val = i;
                _USART_WRITE(USART2, (uint8_t *)convert(i, 10));
                break;
            case 'L':
                i = va_arg(list, int);
                if (i < 0) {
                    UART_SendChar(USART2, '-');
                    i = -i;
                }
                val = i;
                flag = 1;
                _USART_WRITE(USART2, (uint8_t *)convert(i, 10));
                break;
            case 'o':
                i = va_arg(list, int);
                if (i < 0) {
                    UART_SendChar(USART2, '-');
                    i = -i;
                }
                _USART_WRITE(USART2, (uint8_t *)convert(i, 8));
                break;
            case 'x':
                i = va_arg(list, int);
                if (i < 0) {
                    UART_SendChar(USART2, '-');
                    i = -i;
                }
                _USART_WRITE(USART2, (uint8_t *)convert(i, 16));
                break;
            case 's':
                str = va_arg(list, uint8_t *);
                _USART_WRITE(USART2, str);
                break;
            case 'f':
                dval = va_arg(list, double);
                _USART_WRITE(USART2, (uint8_t *)float2str(dval));
                break;
            default:
                break;
        }
    }
    va_end(list);
    if (flag) {
        whot[0].GPIOx = GPIOA;
        whot[0].led = 7;

        whot[1].GPIOx = GPIOA;
        whot[1].led = 4;

        whot[2].GPIOx = GPIOA;
        whot[2].led = 6;

        whot[3].GPIOx = GPIOA;
        whot[3].led = 8;

        whot[4].GPIOx = GPIOC;
        whot[4].led = 7;

        whot[5].GPIOx = GPIOB;
        whot[5].led = 6;

        whot[6].GPIOx = GPIOB;
        whot[6].led = 10;

        for (int i = 0; i < 7; ++i) gpio_init1(whot[i], 1);

        for (int i = 0; i < 7; ++i) {
            if (hello[val][i]) {
                gpio_write1(whot[i], 1);
            } else {
                gpio_write1(whot[i], 0);
            }
        }
    }
}

void kprintf_seven_segment_display(int val) {
    kprintf("It works gg\n");
    whot[0].GPIOx = GPIOA;
    whot[0].led = 7;

    whot[1].GPIOx = GPIOA;
    whot[1].led = 4;

    whot[2].GPIOx = GPIOA;
    whot[2].led = 6;

    whot[3].GPIOx = GPIOA;
    whot[3].led = 8;

    whot[4].GPIOx = GPIOC;
    whot[4].led = 7;

    whot[5].GPIOx = GPIOB;
    whot[5].led = 6;

    whot[6].GPIOx = GPIOB;
    whot[6].led = 10;

    for (int i = 0; i < 7; ++i) gpio_init1(whot[i], 1);

    for (int i = 0; i < 7; ++i) {
        if (hello[val][i]) {
            gpio_write1(whot[i], 1);
        } else {
            gpio_write1(whot[i], 0);
        }
    }
}

// Simplified version of scanf
void kscanf(char *format, ...) {
    // write your code here
    va_list list;
    char *ptr;
    uint8_t buff[50];
    uint8_t *str;
    int len;
    ptr = format;
    va_start(list, format);
    while (*ptr) {
        if (*ptr == '%')  // looking for format of an input
        {
            ptr++;
            switch (*ptr) {
                case 'c':  // charater
                    *(uint8_t *)va_arg(list, uint8_t *) = UART_GetChar(USART2);
                    break;
                case 'd':  // integer number
                    _USART_READ_STR(USART2, buff, 50);
                    *(uint32_t *)va_arg(list, uint32_t *) = __str_to_num(buff, 10);
                    break;
                case 's':  // string without spaces
                    _USART_READ_STR(USART2, buff, 50);
                    str = va_arg(list, uint8_t *);
                    len = __strlen(buff);
                    for (int u = 0; u <= len; u++)  // copy from buff to user defined char pointer (i.e string)
                        str[u] = buff[u];
                    break;
                case 'x':  // hexadecimal number
                    _USART_READ_STR(USART2, buff, 50);
                    *(int *)va_arg(list, uint32_t *) = __str_to_num(buff, 16);
                    break;
                case 'o':  // octal number
                    _USART_READ_STR(USART2, buff, 50);
                    *(uint32_t *)va_arg(list, uint32_t *) = __str_to_num(buff, 8);
                    break;
                case 'f':  // floating point number
                    _USART_READ_STR(USART2, buff, 50);
                    //*(uint32_t*)va_arg(list,double*) = __str_to_num(buff,10);
                    *(float *)va_arg(list, float *) = str2float(buff);  // Works for float but not for double !!!
                    break;
                default:  // rest not recognized
                    break;
            }
        }
        ptr++;
    }
    va_end(list);
}
