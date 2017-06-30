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
  startLiftL = getHeight('l');
	startLiftR = getHeight('r');
	prevTime = millis();
  _tr = 0;
  _br = 1;
  _tl = 2;
  _bl = 3;
}

void DR4B::moveTo(int position) {

}

bool DR4B::safe() {
  if(getHeight('l') != A_UNPLUG && getHeight('r') != A_UNPLUG) {
    return true;
  } else return false;
}

void DR4B::backup() {
  
}

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
  	   desiredLift = LOADER_PRESET; //make a macro define 348
  	}
  }

  	if(desiredLift > 1620) desiredLift = 1620;
  	else if (desiredLift < 5) desiredLift = 5;

  	liftSpeedR = (lK * (desiredLift-currentLiftR));
  	liftSpeedL = lK * (desiredLift-currentLiftL);

  	setMotor(_br, liftSpeedR);
  	setMotor(_bl, liftSpeedL);
  	setMotor(_tr, liftSpeedR);
  	setMotor(_tl, liftSpeedL);
}
