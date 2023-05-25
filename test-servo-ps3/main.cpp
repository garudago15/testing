#include "mbed.h"
#include "../KRAI_library/JoystickPS3/JoystickPS3.h"
#include "../KRAI_library/servoKRAI/servoKRAI.h"

// Serial
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd){
    return &serial_port;
}

// DEFINE PS3
#define tx PC_10
#define rx PC_11
JoystickPS3 ps3(tx, rx);

// DEFINE SERVO
#define servopin PC_9
servoKRAI myservo(servopin);
int main(){
    ps3.setup();
    myservo.calibrate(0.001, 60);
    
    float pos = 0;
    bool prevUp, prevDown;
    prevUp = false; prevDown = false;
    while(true){
        // update data ps3
        ps3.olah_data();
        ps3.baca_data();

        // pos = myservo.read() * 120 - 60; // degree
        // printf("pos = %f, read = %f\n", pos, myservo.read());

        if(ps3.getKotak()){
            pos = -60;
        }
        if(ps3.getLingkaran()){
            pos = 60;
        }
        if(ps3.getSegitiga()){
            pos = 0;
        }
        if(ps3.getButtonDown()){
            if(!prevUp && pos >= -59){
                pos -= 1;
                prevUp = true;
            }
        }else{
            prevUp = false;
        }
        if(ps3.getButtonUp()){
            if(!prevDown && pos <= 59){
                pos += 1;
                prevDown = true;
            }
        }else{
            prevDown = false;
        }
        myservo.position(pos);
        printf("pos = %f, read = %f\n", pos, myservo.read());
    }
}