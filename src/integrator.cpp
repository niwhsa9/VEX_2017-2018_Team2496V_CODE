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
  printf("\n int %d \n",analogRead(4));
  int speed = 0;
    if(stage < 2) {
      if(analogRead(4) > INTEG_BOT) speed = -127;
      else if(analogRead(4) <= INTEG_BOT) speed = -14;

    } else if(stage == 2) {
      if(analogRead(4) < INTEG_TOP) speed = 127;
      else if(analogRead(4) >= INTEG_TOP) {
      speed = 20;
      if(stage != 4) {
        //stage = 4;
        sCmd = millis();
      }
      //clawSet(-50);
    }
  } else if (stage == 3){
    if(joystickGetDigital(2, 5, JOY_UP)) speed = 127;
    else if(joystickGetDigital(2, 5, JOY_DOWN)) speed = -127;
    else speed = 0;
    manualLock = false;
  }
 setAll(speed);

  /*
  if(joystickGetDigital(2, 5, JOY_UP)) setAll(90);
  else if(joystickGetDigital(2, 5, JOY_DOWN)) setAll(-90);
  else setAll(0);
  printf("%d \n", analogRead(4));*/
}
