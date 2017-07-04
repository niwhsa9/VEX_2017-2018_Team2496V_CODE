
#include "dr4b.h"
const float DR4B::lK= 0.2f;
const float DR4B::dK = 0.05f;
/*
* Read potentiometer on specified side
*/
int DR4B::getHeight(char h) {
  if(h=='l') {
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

  liftSpeedL = DR4B_START_L;
  liftSpeedR = DR4B_START_R;
  desiredLift = 0;
  startLiftL = getHeight('l');
  startLiftR = getHeight('r');
  prevTime = millis();
  _tr = 0;
  _br = 1;
  _tl = 2;
  _bl = 3;
}

/*
* Set desiredLift value used in moveTo()
* and iterateCtl()
*/
void DR4B::setDesired(int position) {
  desiredLift = position;
}

/*
* Move lift to value speified by desiredLift
* start on seperate thread for continious control
* in autonomous mode
*/
void DR4B::moveTo() { //change position to percentage?
  int currentLiftL;
  int currentLiftR;
  while(abs(currentLiftR-desiredLift) >= DR4B_THRESHOLD && abs(currentLiftL-desiredLift) >= DR4B_THRESHOLD) {
    currentLiftL = getHeight('l') - startLiftL;
    currentLiftR = getHeight('r') - startLiftR;

    liftSpeedR = (lK * (desiredLift-currentLiftR));
    liftSpeedL = lK * (desiredLift-currentLiftL);

    setMotor(_br, liftSpeedR);
    setMotor(_bl, liftSpeedL);
    setMotor(_tr, liftSpeedR);
    setMotor(_tl, liftSpeedL);
  }
}

/*
* Ensure that both feedback potentiometers
* are functional
*/
bool DR4B::safe() {
  if(getHeight('l') != A_UNPLUG && getHeight('r') != A_UNPLUG) {
    return true;
  } else return false;
}

/*
* Secondary control set, no control loop
*/
void DR4B::backup() {
  if(joystickGetDigital(1,6, JOY_UP)){
    setAll(80);
  } else if (joystickGetDigital(1,6,JOY_DOWN)){
    setAll(-80);
  }
}

/*
* Debug
*/
void DR4B::debug() {
  printf("LEFT %d", getHeight('l')-startLiftL);
  printf("RIGHT %d", getHeight('r')-startLiftR);
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
* Main proportional control loop with user input
* TODO: PID
*/
void DR4B::iterateCtl() {
  int currentLiftL = getHeight('l') - startLiftL;
  int currentLiftR = getHeight('r') - startLiftR;
  if(joystickGetDigital(1,6, JOY_UP)){
    if((millis()- prevTime) >= 10) {
      prevTime = millis();
      desiredLift+=14;
    }
  } else if (joystickGetDigital(1,6,JOY_DOWN)){
    if((millis() - prevTime) >= 10) {
      prevTime = millis();
      desiredLift-=14;
    }
  } else if(joystickGetDigital(1,8, JOY_UP) || joystickGetDigital(1,8, JOY_LEFT) ||
  joystickGetDigital(1,8, JOY_RIGHT) || joystickGetDigital(1, 8, JOY_DOWN) ){
    if(millis() - prevTime >= 10) {
      prevTime = millis();
      desiredLift = LOADER_PRESET;
    }
  }
  if(desiredLift > DR4B_MAX) desiredLift = DR4B_MAX;
  else if (desiredLift < 5) desiredLift = 5;

  liftSpeedR = (lK * (desiredLift-currentLiftR));
  liftSpeedL = lK * (desiredLift-currentLiftL);

  setMotor(_br, liftSpeedR);
  setMotor(_bl, liftSpeedL);
  setMotor(_tr, liftSpeedR);
  setMotor(_tl, liftSpeedL);
}
