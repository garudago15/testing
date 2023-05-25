#include "mbed.h"
#include "../KRAI_library/JoystickPS3/JoystickPS3.h"
#include "../KRAI_library/servoKRAI/servoKRAI.h"

#define tx PC_10
#define rx PC_11
JoystickPS3 ps3(tx, rx);


#define servopin PC_9
servoKRAI myservo(servopin);


int main(){
    ps3.setup();
    myservo.calibrate(0.001, 60);
    
    while(true){
        // update data ps3
        ps3.olah_data();
        ps3.baca_data();

        if(ps3.getKotak()){
            myservo.position(-60);
        }
        if(ps3.getLingkaran()){
            myservo.position(60);
        }
        if(ps3.getSegitiga()){
            myservo.position(0);
        }
    }
}