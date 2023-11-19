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
 
#include <kfloat.h>
#include <kstdio.h>
double __aeabi_f2d(float x)
{
   __single_pnum num;
   __double_number dnum;
   dnum.num=0;
   num.num=x;
   dnum.reg |= ((uint64_t)(num.reg>>31)<<63); //sign bit
   dnum.reg |= (uint64_t) (num.reg & ~((uint32_t)0x1FF<<23))<<29;
   dnum.reg |= (uint64_t)(((uint16_t) ((num.reg>>23) & ~(1<<8)))-127+1023)<<52;
   return dnum.num;
}
float __aeabi_d2f(double x)
{
    __double_number dnum;
    __single_pnum num;
    num.num=0;
    dnum.num=x;
    num.reg |= ((uint32_t)(dnum.reg>>63)<<31);
    num.reg |= (uint32_t)(((((dnum.reg<<1)>>53)-1023)+127)<<23);
    num.reg |= ((uint32_t)((dnum.reg &~((uint64_t)0xFFF<<52))>>29));
    return num.num;
}
int32_t __aeabi_d2iz(double x)
{
    __double_number dnum;
    dnum.num=x;
    int32_t num;
    uint32_t mantissa;
    uint16_t exponent = (uint16_t)(((dnum.reg & ~ ((uint64_t)0x1<<63))>>52)-1023); 
    int8_t sign = (dnum.reg>>63)? -1:1;
    mantissa = (uint32_t)(((dnum.reg & ~((uint64_t)0xFFF<<52)) | (((uint64_t)0b1<<52)))>>(52-exponent));
    num = mantissa * sign;
    return num;
}
int __aeabi_d2i(double x)
{
    __double_number dnum;
    dnum.num=x;
    int num;
    uint32_t mantissa;
    uint16_t exponent = (uint16_t)(((dnum.reg & ~ ((uint64_t)0x1<<63))>>52)-1023); 
    int8_t sign = (dnum.reg>>63)? -1:1;
    mantissa = (uint32_t)(((dnum.reg & ~((uint64_t)0xFFF<<52)) | (((uint64_t)0b1<<52)))>>(52-exponent));
    num = mantissa * sign;
    return num;
}

uint32_t get_decimal_part(double x)
{
    __double_number dnum;
    dnum.num=x;
    int32_t num=0;
    uint64_t mantissa;
    uint16_t exponent = (uint16_t)(((dnum.reg & ~ ((uint64_t)0x1<<63))>>52)-1023); 
    mantissa = (uint64_t)((dnum.reg & ~((uint64_t)0xFFF<<52))) | (uint64_t)0b1<<51;
    mantissa = mantissa<<(12+exponent);
    for(uint32_t i=0;i<DOUBLE_FRAC_PRECISION;i++)
    {
        if(mantissa >> (63-i) & 0b1){
            num += (LARGEST_FRAC >> i);
        }
    } 
    return num;
}
