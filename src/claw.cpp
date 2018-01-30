#include "claw.h"

Claw::Claw(const char *name, int motors[10], int revField[10],
  int num, int sensors[10], char id=255):
  Subsystem(name, motors, revField, num, _sensors, id)
  {};

/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void Claw::init() {
  enc = 0;
  desired = 0;
  _cm = 0;
}

void Claw::setDesired(int des) {
  setMotor(0, des);
  desired = des;
}

void Claw::hold() {
  setMotor(0, 30);
}
/*
* Move claw to value speified by desired
* start on seperate thread for continious control
* in autonomous mode
*/
void Claw::moveTo() {

}


/*
* Debug
*/
void Claw::debug() {
  //printf("LEFT %d", );
  //printf("RIGHT %d", getHeight('r')-startLiftR);
}

/*
* Emergency stop all motors and deallocate
* memory to be called on failure event
*/
int Claw::eStop() {
  setAll(0);
  return 0;
}

/*
* Main control loop with user input
*/
void Claw::iterateCtl() {

  if (joystickGetDigital(1, 5, JOY_UP) && joystickGetDigital(1, 5, JOY_DOWN)) {
    setMotor(0, 30);
  }
  else if(joystickGetDigital(1, 5, JOY_UP) || joystickGetDigital(2, 8, JOY_LEFT)) {
    setMotor(0, 50);
    lastBtn = true;
  } else if (joystickGetDigital(1, 5, JOY_DOWN) || joystickGetDigital(2, 8, JOY_DOWN)) {
    setMotor(0, -50);
    lastBtn = false;
  } else if(joystickGetDigital(1, 8, JOY_DOWN)) setMotor(0, 9);
  else {
       if(lastBtn == true) setMotor(0, 17);
       else setMotor(0, 9);

  }
}
