#include "mbed.h"
#include "../KRAI_library/JoystickPS3/JoystickPS3.h"

// --------------  SETUP SERIAL  --------------
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}

// -------------- DEFINE STIK --------------
#define tx PC_10
#define rx PC_11
JoystickPS3 ps3(tx, rx);

// DEFINE LED
DigitalOut led(LED1);

int main()
{
    ps3.setup();
    led = 0;
    while (true)
    {
        // Pengolahan dan Update data
        ps3.olah_data();
        ps3.baca_data();

        // Print Input Controller
        printf("RX : %d RY : %d LX : %d LY : %d", ps3.getRX(), ps3.getRY(), ps3.getLX(), ps3.getLY());
        printf("R1 : %d R2 : %d L1 : %d L2 : %d ", ps3.getR1(), ps3.getR2(), ps3.getL1(), ps3.getL2());
        printf("Kotak : %d Silang : %d Lingkaran : %d Segitiga : %d ", ps3.getKotak(), ps3.getSilang(), ps3.getLingkaran(), ps3.getSegitiga());
        printf("Up : %d Left : %d Right : %d Down : %d ", ps3.getButtonUp(), ps3.getButtonLeft(), ps3.getButtonRight(), ps3.getButtonDown());
        printf("Start : %d Select : %d \n", ps3.getStart(), ps3.getSelect());
        // Jika R1 ditekan, LED1 nyala.
        if (ps3.getR1())
        {
            led = 1;
        } else {
            led = 0;
        }
    }
    
}