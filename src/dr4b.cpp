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
    return analogRead(_sensors[0]);
  } else {
    return analogRead(_sensors[1]);
  }
}

/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void DR4B::init() {
  _l = _motors[0];
  _r = _motors[1];
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
  if(joystickGetDigital(1, 7, JOY_RIGHT)) {
    safety = false;
    desiredLift = 0;
  }
  if(joystickGetDigital(1,6, JOY_UP)){
    setAll(80);
  } else if (joystickGetDigital(1,6,JOY_DOWN)){
    setAll(-80);
  } else setAll(0);
  if(joystickGetDigital(1,5, JOY_UP)){ //rm
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
  backup();
}
