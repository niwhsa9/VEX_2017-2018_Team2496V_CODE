
#include "dr4b.h"

int prev = 0;
int prev2 = 0;
float rightMotor = 0;

DR4B::DR4B(const char *name, int motors[10],	int revField[10],
  const int num, int sensors[10], const char id=255):
  Subsystem(name, motors, revField, num, sensors, id)
  {};
/*
* Read potentiometer on specified side
*/
int DR4B::getHeight(char h) {

    return DR4B_START - analogRead(_sensors[0]);

}

/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void DR4B::init() {
  _l = _motors[0];
  _r = _motors[1];

  setPID(0.4, 0.0, 7.0, 1000000);
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
  /*if(millis() - prev >= 5000) {
    char PIDV[20];
    sprintf(PIDV, "%f %f %f", pK, iK, dK);
    writeJINXMessage(PIDV);
    prev = millis();
  }
  */
  if(millis() - prev2 >= 100) {
    //char actual[10];
    /*
    sprintf(actual, "%d", getHeight('l'));
    writeJINXData("actual", actual);

    char desired[10];
    sprintf(desired, "%d", desiredLift);
    writeJINXData("desired", desired); */


/*
    char de[10];
    sprintf(de, "%f", d);
    writeJINXData("derrivative", de);

    char pe[10];
    sprintf(pe, "%f", p);
    writeJINXData("proportional", pe);
*/
/*
  char spedz[10];
  sprintf(spedz, "%f", rightMotor);
  writeJINXData("spedz", spedz);
    prev2 = millis();
*/
  //printf("\n %f", rightMotor);
  }
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

void DR4B::moveTo() {
  if(desiredLift<=0) desiredLift = 0;
  //if(joystickGetDigital(2, 7, JOY_DOWN)) desiredLift= 1000;
  float error = (desiredLift-getHeight('r'));
  rightMotor = PID(error);
  float leftMotor = rightMotor;
  //printf("height %d \n", getHeight('l'));

  //printf("speed %f  error %f \n", rightMotor, error);
  //printf("right %f  left %f \n", rightMotor , leftMotor);

  setMotor(0, leftMotor);
  setMotor(1, rightMotor);
}

/*
* Main proportional/derrivitave control loop with user input
* TODO: Integral component
*/
void DR4B::setSpeed(int speed) {
  setAll(speed);
}

void DR4B::iterateCtl() {
  int speed = 0;

  if(stage == 0) {
    if(millis() - dCmd >= 400) {
      desiredLift = 0 + offset;
    } else {
      desiredLift += 11;
    }
  }
  else if (stage == 1) {
    if(desiredLift - getHeight('c') <= INTEG_GO) stage = 2;
    desiredLift = ((stackHeight-1) * 100 + firstCone);
  } else if(stage == 4) {
    if(millis()- sCmd <= 200) desiredLift -= 8;
  }
  else if (stage == 3) {
    setMotor(0, joystickGetAnalog(2, 3));
    setMotor(1, joystickGetAnalog(2, 3));
    return;
    //desiredLift += (int)((float)joystickGetAnalog(2, 3)/5.0);
  }


  /*
  if(joystickGetDigital(2,6, JOY_UP)){
    speed = 120;
    desiredLift+=20;
  } else if (joystickGetDigital(2,6,JOY_DOWN)){
    desiredLift-=20;
    speed = -120;
  } else speed = 0; */

  if(desiredLift<=0) desiredLift = 0;
  //if(joystickGetDigital(2, 7, JOY_DOWN)) desiredLift= 1000;
  float error = (desiredLift-getHeight('r'));
  rightMotor = PID(error);
  float leftMotor = rightMotor;
  //printf("height %d \n", getHeight('l'));

  //printf("speed %f  error %f \n", rightMotor, error);
  //printf("right %f  left %f \n", rightMotor , leftMotor);
  if(stage == 0) {
    if(millis() - dCmd >= 430) {
        if(leftMotor > -10) {
          leftMotor = -10;
          rightMotor = -10;
        }
    }
  }

  setMotor(0, leftMotor);
  setMotor(1, rightMotor);



  //printf(height);
}

void DR4B::setConst(char c, float f) {
  Subsystem::setConst(c, f);
}
