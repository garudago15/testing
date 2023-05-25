/* mbed Microcontroller Library
 * Copyright (c) 2023 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "../../KRAI_library/JoystickPS3/JoystickPS3.h"

// -------------- SETUP LED --------------
DigitalOut led1(LED1);
// DigitalOut led2(LED2);


// --------------  SETUP SERIAL  --------------
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}


// -------------- DEFINE STIK --------------
#define tx PC_12
#define rx PD_2

JoystickPS3 ps3(tx, rx);


// DEFINE LED

DigitalOut led(LED1);



int main()
{
    ps3.setup();
    led = 0;

    while (true)
    {
        ps3.olah_data();
        if (ps3.readable())
        {
            printf("RX : %d RY : %d LX : %d LY : %D ", ps3.getRX(), ps3.getRY(), ps3.getLX(), ps3.getLY());
            printf("R1 : %d R2 : %d L1 : %d L2 : %d ", ps3.getR1(), ps3.getR2(), ps3.getL1(), ps3.getL2());
            printf("Kotak : %d Silang : %d Lingkaran : %d Segitiga : %d ", ps3.getKotak(), ps3.getSilang(), ps3.getLingkaran(), ps3.getSegitiga());
            printf("Up : %d Left : %d Right : %d Down : %d ", ps3.getButtonUp(), ps3.getButtonLeft(), ps3.getButtonRight(), ps3.getButtonDown());
            printf("Start : %d Select : %d ", ps3.getStart(), ps3.getSelect());

            // PRINT JIKA BACA DATA
            if(ps3.baca_data()){
                printf(" Sedang Baca \n");
            }

            // JIKA R1 DITEKAN LED NYALA
            if (ps3.getR1())
            {
                led = 1;
            } else {
                led = 0;
            }
            
        }
        
        
    }
    
}