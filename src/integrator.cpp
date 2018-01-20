#include "integrator.h"


Integrator::Integrator(const char *name, int motors[10], int revField[10],
int num, int sensors[10], char id=255):
  Subsystem(name, motors, revField, num, _sensors, id)
  {};


/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void Integrator::init() {
  _m = 0;

}




/*
* Debug
*/
void Integrator::debug() {

}

/*
* Emergency stop all motors and deallocate
* memory to be called on failure event
*/
int Integrator::eStop() {
  setAll(0);
  return 0;
}



void Integrator::setEm(int speed) { setAll(speed); }
/*
* Main control loop with user input
*/
void Integrator::iterateCtl() {
  if(joystickGetDigital(2, 5, JOY_UP)) setAll(90);
  else if(joystickGetDigital(2, 5, JOY_DOWN)) setAll(-90);
  else setAll(0);
}
