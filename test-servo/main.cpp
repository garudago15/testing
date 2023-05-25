#include "mbed.h"
#include "../KRAI_library/servoKRAI/servoKRAI.h"

#define servopin PC_9
servoKRAI myservo(servopin);
int main(){
    myservo.calibrate(0.001, 60);
    while(true){
        myservo.position(60);
        wait_us(1000000);
        myservo.position(-60);
        wait_us(1000000);
    }
}