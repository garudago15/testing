/* mbed Microcontroller Library
 * Copyright (c) 2023 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "led4Pin/led4Pin.h"

// DEFINE LED
#define red PC_10
#define green PC_9
#define blue PC_8
LED4 RGB(red, green, blue);

int main()
{
    while (true)
    {
        RGB.setColor("RED");
    }
    
    return 0;
}