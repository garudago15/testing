// This code uses motor driver L298N and encoder module

#define ENCODEROUTPUT 352 // pulse per rotation value (by experiment/data sheet)

const int ENCODER_IN = 3; // Output from encoder
const int MOTOR_PIN_A = 6; // MOTOR HIGH PIN
const int MOTOR_PIN_B = 7; // MOTOR LOW PIN
const int MOTOR_PIN_PWM = 10;

double set_speed = 150;
double e_speed = 0; //error of speed = set_speed - rpm
double e_speed_pre = 0;  //last error of speed
double e_speed_sum = 0;  //sum error of speed
double pwm_pulse = 0;     //this value is 0~255
double kp = 0.25;
double ki = 0.28;
double kd = 10;


volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
boolean measureRpm = false;
int motorPwm = 0;

void setup() {

  Serial.begin(9600);//Initialize the serial port
  EncoderInit();//Initialize the module
  
   pinMode( MOTOR_PIN_A , OUTPUT);
   pinMode( MOTOR_PIN_B , OUTPUT);

   digitalWrite(MOTOR_PIN_A,HIGH);
   digitalWrite(MOTOR_PIN_B,LOW);

   encoderValue = 0;
   previousMillis = millis();
}

void loop() {
  // Update RPM value on every second

  // PID
  e_speed = set_speed - rpm;
  pwm_pulse = e_speed*kp + e_speed_sum*ki + (e_speed - e_speed_pre)*kd;
  e_speed_pre = e_speed;  //save last (previous) error
  e_speed_sum += e_speed; //sum of error
  if (e_speed_sum >100) e_speed_sum = 100;
  if (e_speed_sum <-100) e_speed_sum = 100;

  //UPDATE SPEED
  if (pwm_pulse <255 & pwm_pulse >0){
    analogWrite(MOTOR_PIN_PWM,pwm_pulse);  //set motor speed  
  }
  else{
    if (pwm_pulse>255){
      analogWrite(MOTOR_PIN_PWM,255);
    }
    else{
      analogWrite(MOTOR_PIN_PWM,0);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////

    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
    
       
    
        // Revolutions per minute (RPM) =
        // (total encoder pulse in 1s / motor encoder output) x 60s
        rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);
    
        // Only update display when there have readings
        if ( rpm > 0) {
          
    
    
          Serial.println(rpm);
        
        }
        
        encoderValue = 0;
  }
  

}

void EncoderInit()
{
 // Attach interrupt at encoder pin on each rising signal
  attachInterrupt(digitalPinToInterrupt(ENCODER_IN), updateEncoder, RISING);
}


void updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from encoder pin
  encoderValue++;
}
