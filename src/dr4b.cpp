
#include "dr4b.h"

DR4B::DR4B(const char *name, int motors[10],	int revField[10],
  const int num, int sensors[10], const char id=255):
  Subsystem(name, motors, revField, num, sensors, id)
  {};
/*
* Read potentiometer on specified side
*/
int DR4B::getHeight(char h) {
//  printf("MOTOR 1 %d", _motors[1]);
  if(h=='l') {
    //printf("\n %d", _revField[2]);
    return encoderGet(_le);
  } else {
    return encoderGet(_re);
  }
}

/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void DR4B::init() {
  _l = _motors[0];
  _r = _motors[1];
  _re = encoderInit(D_LIFT_ENC_R2,D_LIFT_ENC_R1, true); //CHANGE FROM HARDCODE
  _le = encoderInit(D_LIFT_ENC_L2, D_LIFT_ENC_L1, true); //CHANGE FROM HARDCODE
  setPID(3.4, 0.0, 0.0, 1000000);
  setAltPID(0.0, 0.0, 0.0);
  desiredLift = 0;
}

/*
* Set desiredLift value used in moveTo()
* and iterateCtl()
/

/*
* Move lift to value speified by desiredLift
* start on seperate thread for continious control
* in autonomous mode
*/


/*
* Ensure that both feedback potentiometers
* are functional
*/

/*
* Secondary control set, no control loop
*/
void DR4B::backup() {
  if(joystickGetDigital(2,6, JOY_UP)){
    setAll(127);
  } else if (joystickGetDigital(2,6,JOY_DOWN)){
    setAll(-127);
  } else setAll(0);
  if(joystickGetDigital(2,5, JOY_UP)){ //rm
     motorSet(6, 40);
    //setMotor(1, 127);
  } else motorSet(6, 0);
//  setAll(80);
}

/*
* Debug
*/
void DR4B::debug() {
  printf("LEFT %d \n", getHeight('l')-startLiftL);
  printf("RIGHT %d \n", getHeight('r')-startLiftR);
}

/*
* Emergency stop all motors and deallocate
* memory to be called on failure event
*/
int DR4B::eStop() {
  setAll(0);
  //delete this; //PROS delete functionality lacking
  return 0;
}

/*
* Main proportional/derrivitave control loop with user input
* TODO: Integral component
*/
void DR4B::iterateCtl() {
  int speed = 0;
  if(joystickGetDigital(2,6, JOY_UP)){
    speed = 120;
  } else if (joystickGetDigital(2,6,JOY_DOWN)){
    speed = -120;
  } else speed = 0;
  //if(desiredLift<=0) desiredLift = 0;
  float error = (desiredLift-getHeight('r'));
  float rightMotor = desiredLift;//PID(error);
  float leftMotor = desiredLift;//PID(getHeight('r') - getHeight('l'));

  //printf("speed %f  error %f \n", rightMotor, error);
  //printf("right %f  left %f \n", rightMotor , leftMotor);
  setMotor(0, speed);
  setMotor(1, speed);
}
