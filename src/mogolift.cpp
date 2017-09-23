#include "mogolift.h"


MogoLift::MogoLift(const char *name, int motors[10], int revField[10],
int num, int sensors[10], char id=255):
  Subsystem(name, motors, revField, num, _sensors, id)
  {};


/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void MogoLift::init() {
  _lm = 0;
  _rm = 1;

}




/*
* Debug
*/
void MogoLift::debug() {
  //printf("LEFT %d", );
  //printf("RIGHT %d", getHeight('r')-startLiftR);
}

/*
* Emergency stop all motors and deallocate
* memory to be called on failure event
*/
int MogoLift::eStop() {
  setAll(0);
  return 0;
}

/*
* Main control loop with user input
*/
void MogoLift::iterateCtl() {
  if(joystickGetDigital(1, 5, JOY_UP)) setAll(90);
  else if(joystickGetDigital(1, 5, JOY_DOWN)) setAll(-90);
  else setAll(0);
}
