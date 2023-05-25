#include "mbed.h"
#include "../../KRAI_library/Motor/Motor.h"
#include "../../KRAI_library/encoderKRAI/encoderKRAI.h"

DigitalOut led1(LED1);
// DigitalOut led2(LED2);

static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}


// ---------------------------------------------------------------------

#define PWM PB_8
#define FWD PB_3
#define REV PA_14

#define CHA PA_13
#define CHB PA_12
#define PPR 537.6

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

        motor.speed(0.4);
        // Looping

        while (millis_ms() -  now > TS)
        {
            speedPulse = (float(enc.getPulses() - tmpPulse)/TS);
            tmpPulse = enc.getPulses();
            now = millis_ms();
        }

        speedRPM = speedPulse / PPR;
        speedSudut = speedPulse * 360 / PPR;
        printf("Pulse : %d Millis (ms) : %d Pulse Speed : %.2f Speed RPM : %.2f Speed Sudut : %.2f \n", enc.getPulses(), millis_ms(),speedPulse, speedRPM, speedSudut);
        
    }
}