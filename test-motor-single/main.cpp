#include "mbed.h"
#include "../KRAI_library/Motor/Motor.h"
#include "../KRAI_library/encoderKRAI/encoderKRAI.h"

DigitalOut led1(LED1);
// DigitalOut led2(LED2);

static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}


// ---------------------------------------------------------------------

#define PWM PA_10
#define FWD PB_3
#define REV PB_5

#define CHA PB_4
#define CHB PB_14
#define PPR 105

// --------------------------------------------------------------------

encoderKRAI enc(CHA ,CHB ,PPR ,Encoding::X4_ENCODING);

// --------------------------------------------------------------------

Motor motor(PWM, FWD, REV); 
int currentsudut = 0;

int millis_ms() {
    return (us_ticker_read() / 1000);
}

// -------------------------------------------------------------------

#define TS 50  // 50ms
int now; // time

float speedRPM;
float currentSudut, speedSudut;
float speedPulse, tmpPulse;
int tmp_sudut;

// ------------------------------------------------------------------

// main() runs in its own thread in the OS
int main() {
    now = millis_ms();
    tmpPulse = enc.getPulses();
    currentSudut = (enc.getPulses() * 360 / PPR);

    while (true) {

        motor.speed(1);
        // Looping

        while (millis_ms() -  now > TS)
        {
            speedPulse = (float(enc.getPulses() - tmpPulse)/TS) * 1000; // pulse / s
            tmpPulse = enc.getPulses(); //pulse
            now = millis_ms(); // ms
        }

        speedRPM = speedPulse / PPR * 60; // pulse/s / Pulse/rotation = rotation/s
        speedSudut = speedPulse * 360 / PPR;
        printf("Pulse : %d Millis (ms) : %d Pulse Speed : %.2f Speed RPM : %.2f Speed Sudut : %.2f \n", enc.getPulses(), millis_ms(),speedPulse, speedRPM, speedSudut);
        
    }
}