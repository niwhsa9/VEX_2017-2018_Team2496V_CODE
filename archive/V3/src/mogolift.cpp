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


  _lstop = D_LEFT_LIMIT;
  _rstop = D_RIGHT_LIMIT;

  _lpot = A_LIFT_POT_L;
  _rpot = A_LIFT_POT_R;


  pinMode(_lstop, INPUT);
    pinMode(_rstop, INPUT);

}




/*
* Debug
*/
void MogoLift::debug() {
  printf("\nLEFT LIM %d", digitalRead(_lstop));
  printf("\nRIGHT LIM %d", digitalRead(_rstop));
  printf("\nLEFT POT %d", analogRead(_lpot));
  printf("\nRIGHT POT %d", analogRead(_rpot));
}

/*
* Emergency stop all motors and deallocate
* memory to be called on failure event
*/
int MogoLift::eStop() {
  setAll(0);
  return 0;
}

void MogoLift::moveMax() {
    setAll(90);
    /*
    while(digitalRead(_lstop) == true && digitalRead(_rstop) == true) {
        if(digitalRead(_lstop)) {
          //setMotor(_lm, 100);
        } else setMotor(_lm, 0);

        if(digitalRead(_rstop)) {
          //setMotor(_rm, 100);
        } else setMotor(_rm, 0);

    }*/
    while(digitalRead(_lstop) == true) {
      continue;
    }
    setAll(0);

}

void MogoLift::moveMin() {/*
  while(abs(analogRead(A_LIFT_POT_L) - LIFT_MIN_L) >= LIFT_TARGET_THRESHOLD && abs(analogRead(A_LIFT_POT_R) - LIFT_MIN_R) >= LIFT_TARGET_THRESHOLD) {
      if(abs(analogRead(A_LIFT_POT_L) - LIFT_MIN_L) >= LIFT_TARGET_THRESHOLD) {
        setMotor(_lm, -90);
      } else setMotor(_lm, 0);

      if(abs(analogRead(A_LIFT_POT_R) - LIFT_MIN_R) >= LIFT_TARGET_THRESHOLD) {
        setMotor(_rm, -90);
      } else setMotor(_rm, 0);

  }*/
  setAll(-90);
  while(abs(analogRead(A_LIFT_POT_L)- LIFT_MIN_L)  >= LIFT_TARGET_THRESHOLD) {
    continue;
  }
  setAll(0);

}

void MogoLift::setEm(int speed) { setAll(speed); }
/*
* Main control loop with user input
*/
void MogoLift::iterateCtl() {
  if(joystickGetDigital(1, 6, JOY_UP)) setAll(90);
  else if(joystickGetDigital(1, 6, JOY_DOWN)) setAll(-90);
  else setAll(0);
}
