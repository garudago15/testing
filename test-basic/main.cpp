#include "mbed.h"

// PinMode
DigitalOut led1(LED1);

// Serial
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd){
    return &serial_port;
}

// clock
int clock1 = us_ticker_read();
int clock2 = us_ticker_read();

int main(){
    int now;
    while(true){
        now = us_ticker_read();
        if(now - clock1 > 1 * 1e6){
            printf("%d\n", now);
            clock1 = now;
        }
        if(now - clock2 > 0.5 * 1e6){
            led1 = !led1;
            clock2 = now;
        }
    }
}