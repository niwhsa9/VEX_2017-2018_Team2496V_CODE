#include "dr4b.h"

const float DR4B::lK= 0.2f;

int DR4B::getHeight(char h) {
  if(h=='l') {
    return analogRead(_sensors[0]);
  } else {
    return analogRead(_sensors[1]);
  }
}

void DR4B::init() {

  liftSpeedL = 127;
  liftSpeedR = 127;
  desiredLift = 0;
  startLiftL = analogRead(A_LIFT_POT_L);
	startLiftR = analogRead(A_LIFT_POT_R);
	prevTime = millis();
  _tr = 0;
  _br = 1;
  _tl = 2;
  _bl = 3;
}

void DR4B::moveTo(int position) {

}

void DR4B::iterateCtl() {
  int currentLiftL = analogRead(A_LIFT_POT_L) - startLiftL;
  int currentLiftR = analogRead(A_LIFT_POT_R) - startLiftR;
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
  	   desiredLift = LOADER_PRESET; //make a macro define 348
  	}
  }

  	if(desiredLift > 1620) desiredLift = 1620;
  	else if (desiredLift < 5) desiredLift = 5;

  	liftSpeedR = -(lK * (desiredLift-currentLiftR));
  	liftSpeedL = lK * (desiredLift-currentLiftL);

  	motorSet(M_LIFT_BR, liftSpeedR);
  	motorSet(M_LIFT_BL, liftSpeedL);
  	motorSet(M_LIFT_TR, liftSpeedR);
  	motorSet(M_LIFT_TL, liftSpeedL);

}
