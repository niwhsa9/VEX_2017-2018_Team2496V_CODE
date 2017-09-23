#include "dr4b.h"
const float DR4B::lK= 0.2f;
const float DR4B::dK = 0.05f;

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

  liftSpeedL = DR4B_START_L;
  liftSpeedR = DR4B_START_R;
  desiredLift = 0;
  startLiftL =  DR4B_START_L;
  startLiftR =  DR4B_START_R;
  prevTime = millis();
  prevErrorL = 0;
  prevErrorR = 0;
  _tr = 0;
  _br = 1;
  _tl = 2;
  _bl = 3;
  prevOpComplete = true;
  safety = false;
}

/*
* Set desiredLift value used in moveTo()
* and iterateCtl()
*/
void DR4B::setDesired(int position) {
  prevOpComplete = false;
  desiredLift = position;
}

void DR4B::unpack() {
  setDesired(435);
  while(!prevOpComplete) moveTo();
  setDesired(50);
  while(!prevOpComplete) {
    //printf("height %d", getHeight('l'));
    moveTo();
  }

}

/*
* Move lift to value speified by desiredLift
* start on seperate thread for continious control
* in autonomous mode
*/
void DR4B::moveTo() { //change position to percentage?
  int currentLiftL=0;
  int currentLiftR=0;
  prevErrorL = 0;
  prevErrorR = 0;
//  while(/*abs(currentLiftR-desiredLift) >= DR4B_THRESHOLD && abs(currentLiftL-desiredLift) >= DR4B_THRESHOLD*/1) {

    currentLiftL = getHeight('l') - startLiftL;
    currentLiftR = getHeight('r') - startLiftR;
      printf("debug %d", currentLiftL);

    int curErrorR = (desiredLift-currentLiftR);
    int curErrorL = (desiredLift-currentLiftL);

    liftSpeedR = (lK * curErrorR) + (dK * (curErrorR-prevErrorR));
    liftSpeedL = (lK * curErrorL) + (dK * (curErrorL-prevErrorL));

    prevErrorL = curErrorL;
    prevErrorR = curErrorR;

    setMotor(_br, liftSpeedR);
    setMotor(_bl, liftSpeedL);
    setMotor(_tr, liftSpeedR);
    setMotor(_tl, liftSpeedL);

    if(abs(currentLiftL-desiredLift) <= DR4B_THRESHOLD) {
      prevOpComplete = true;
      setAll(0);
    }
    //delay(10);
//  }
}

/*
* Ensure that both feedback potentiometers
* are functional
*/
bool DR4B::safe() {
  if(getHeight('l') != A_UNPLUG && getHeight('r') != A_UNPLUG && safety != true) {
    return true;
  } else return false;
}

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
  if(joystickGetDigital(1, 7, JOY_LEFT)) safety = true;

  int currentLiftL = getHeight('l') - startLiftL;                                         //Get lift heights in zeroed potetiometer values
  int currentLiftR = getHeight('r') - startLiftR;
  if(joystickGetDigital(1,6, JOY_UP)){                                                    //Take input as close to fixed sample rate
    if((millis()- prevTime) >= 10) {
      prevTime = millis();
      desiredLift+=14;                                                                    //Increase desired position when given corresponding input
    }
  } else if (joystickGetDigital(1,6,JOY_DOWN)){                                           //Take input as close to fixed sample rate
    if((millis() - prevTime) >= 10) {
      prevTime = millis();
      desiredLift-=14;                                                                    //Decrease desired position when given corresponding input
    }
  } else if(joystickGetDigital(1,8, JOY_UP)){
    if(millis() - prevTime >= 10) {
      prevTime = millis();
      desiredLift = LOADER_PRESET;
    }
  } else if(joystickGetDigital(1, 8, JOY_DOWN)) {
    if((millis() - prevTime) >= 10) {
      prevTime = millis();
      desiredLift-=5;                                                                    //Decrease desired position when given corresponding input
    }
  } else if(joystickGetDigital(1,8, JOY_RIGHT)){
    if(millis() - prevTime >= 10) {
      prevTime = millis();
      desiredLift = STATIONARY_PRESET;
    }
  }
  if(desiredLift > DR4B_MAX) desiredLift = DR4B_MAX;                                      //Bounds check, do not try to force lift past physical limit
  else if (desiredLift < 5) desiredLift = 5;

  int curErrorR = (desiredLift-currentLiftR);                                             //Calculate error between desired and actual
  int curErrorL = (desiredLift-currentLiftL);
                                                                                          //Add proportional and derrivitave components for control outpt
  liftSpeedR = (lK * curErrorR) + (dK * (curErrorR-prevErrorR));

  liftSpeedL = liftSpeedR;
  //liftSpeedL = (lK * curErrorL) + (dK * (curErrorL-prevErrorL));
                                                                                          /**                                                               **
                                                                                          * Proportional: constant x error. Apply more correction for larger *
                                                                                          * error                                                            *
                                                                                          *------------------------------------------------------------------*                                                 *
                                                                                          * Derrivitave: constant x instantaneous rate of change.            *
                                                                                          * Apply more correction with larger change                         *
                                                                                          **                                                                **/

  prevErrorL = curErrorL;                                                                 //Set prevError storage to now used current error information
  prevErrorR = curErrorR;

  setMotor(_br, liftSpeedR);                                                              //Set motors according to calculated input from PD loop
  setMotor(_bl, liftSpeedL);
  setMotor(_tr, liftSpeedR);
  setMotor(_tl, liftSpeedL);
}
