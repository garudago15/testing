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
#define TS 0.005 // Time Sampling (s)

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

int millis_ms(){
    return us_ticker_read() * 1000;
}

float currentPulse, currentSudut;
float prevPulse, prevSudut;
float speedPulse, speedSudut; // Kecepatan sudut (derajat/s) dan kecepatan pulse (pulse/s)
float currentRPM; // RPM sekarang
float targetRPM = 0;
float pwm;

int now; // Waktu sekarang (ms)
int timer1 = millis_ms(); //ms
int timer2 = millis_ms(); //ms

int main() {
    ps3.setup();
    prevPulse = 0;
    motor.speed(0.5);

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


        // get current data
        now = millis_ms();
        currentPulse = enc.getPulses();
        // currentSudut = currentPulse * 360 / PPR;

        if(now - timer1 >= TS){
            // get current speed
            speedPulse = (prevPulse - currentPulse) / TS; // pulse / ms
            // speedSudut = (prevSudut - currentSudut) / TS; // derajat / ms
            // convert satuan
            speedPulse = speedPulse * 1000; // pulse/s
            // speedSudut = speedSudut * 1000; // derajat/s

            currentRPM = speedPulse / PPR * 60; //rotation per minute

            // update prevSudut dan prevPulse
            // prevSudut = currentSudut;
            prevPulse = currentPulse;

            timer1 = millis_ms();
        }
        pwm = PID.createpwm(targetRPM, currentRPM, 0.5);
        motor.speed(pwm);

        if(now - timer2 >= 100){
            // printf("Sudut: %*d", 4, currentSudut);
            // printf(" | RPM: %*d.2f", 5, currentRPM);
            printf("Pulse: %d | RPM : %.2f | TargetRPM : %.2f \n", currentPulse, currentRPM, targetRPM);
            
            timer2 = millis_ms();
        }

    }
}