#include "mbed.h"
#include "../KRAI_library/Motor/Motor.h"
#include "../KRAI_library/encoderKRAI/encoderKRAI.h"
#include "../KRAI_library/pidLo/pidLo.h"
#include "../KRAI_library/JoystickPS3/joystickPS3.h"

// Serial
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}

// Define Pins
#define PWM PA_10
#define FWD PB_3
#define REV PB_5

#define CHA PB_4
#define CHB PB_14

#define tx PC_10
#define rx PC_11

#define KP 0.015
#define KI 0.001
#define KD 0
#define TS 50 // Time Sampling (s)

#define MAXOUT 1
#define VFF 0
#define RPF 1000
#define MAXIN 1000

#define PPR 105 // Pulse per Rotation

// Declare motor, encoder, joystickPS3, dan PID
encoderKRAI enc(CHA ,CHB ,PPR ,Encoding::X4_ENCODING);
Motor motor(PWM, FWD, REV); 
JoystickPS3 ps3(tx, rx);
pidLo PID(KP, KI, KD, TS, MAXOUT, VFF, RPF, MAXIN);

// Fungsi Millis dalam ms
int millis_ms(){
    return us_ticker_read() * 1000;
}


// Setup Variabel PID
int targetRPM;
float pwm;

// -------------------------------------------------------------------

int now; // time

float speedRPM;
float currentSudut, speedSudut;
float speedPulse, tmpPulse;
int tmp_sudut;

// ------------------------------------------------------------------

int main() {
    ps3.setup();

    now = millis_ms();
    tmpPulse = enc.getPulses();
    currentSudut = (enc.getPulses() * 360 / PPR);

    while(true){
        // -- PS3 Controller Loop --
        ps3.olah_data();
        ps3.baca_data();

        if(ps3.getKotak()){
            targetRPM = 100;
        }
        if(ps3.getLingkaran()){
            targetRPM = 200;
        }
        if(ps3.getSegitiga()){
            targetRPM = 300;
        }


        // OLAH DATA ENCORDER
        while (millis_ms() -  now > TS)
        {
            speedPulse = (float(enc.getPulses() - tmpPulse)/TS) * 1000; // pulse / s
            tmpPulse = enc.getPulses(); //pulse
            now = millis_ms(); // ms
        }

        // Olah data kecepatan RPM dan sudut
        speedRPM = speedPulse / PPR * 60; // pulse/s / Pulse/rotation = rotation/s
        speedSudut = speedPulse * 360 / PPR;

        printf("Triangle: %d ", ps3.getSegitiga());
        printf("Pulse : %d Millis (ms) : %d Pulse Speed : %.2f Speed RPM : %.2f Speed Sudut : %.2f Target RPM : %d \n", enc.getPulses(), millis_ms(),speedPulse, speedRPM, speedSudut, targetRPM);
        motor.speed(0.5);

    }
}