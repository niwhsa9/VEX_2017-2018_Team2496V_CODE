#include "main.h"
#include "ports.h"
#include "robot.h"
#include "JINX.h"

int prevTime = 0;
int curTime = 0;

int stackHeight = 0;
int stage = 0;
int dCmd = millis();
int offset = 0;
int manualLock = true;
int firstCone = 0;

bool r6U = false;
bool r6D = false;

bool p6U = false;
bool p6D = false;

void clawSet(int des) {
  claw->setDesired(des);
}


void displayVoltage() {
  if(curTime - prevTime >= 10000) {
    char line1[16];
      char line2[16];
    sprintf(line1, "< Battery >");
    sprintf(line2, "%fV", (float)powerLevelMain()/1000);
    lcdSetText(uart2, 1, line1);
    lcdSetText(uart2, 2, line2);
    prevTime = curTime;
  }
}

void operatorControl() {
  lcdSetBacklight(uart2, false);
	if(isSubInit!=true) { //Ensure subsystems were created
		subsystemInit();
	}
	while (1) {
		curTime = millis();
    if(joystickGetDigital(1, 6, JOY_UP) && !r6U) {
      stackHeight++;
      stage = 1;
    }
    else if(joystickGetDigital(1, 6, JOY_DOWN) && !r6D) {
      stage = 0;
      dCmd = curTime;
      manualLock = true;
    }
    if(joystickGetDigital(2, 6, JOY_UP) && !p6U) {
      stackHeight++;
    } else if(joystickGetDigital(2, 6, JOY_DOWN) && !p6D) {
      stackHeight--;
    } else if(joystickGetDigital(2, 8, JOY_RIGHT)) stackHeight = 0;

    if(joystickGetDigital(2, 7, JOY_RIGHT)) {
      stackHeight = 0;
      stage = 0;
      dCmd = curTime;
      manualLock - true;
      offset = 0;
    }

    if(joystickGetDigital(2, 8, JOY_UP)) {
      offset = 0;
      firstCone = 50;
    }
    if(joystickGetDigital(2, 8, JOY_LEFT)) {
      offset = LOADER_PRESET;
      firstCone = 110;
    }
    if(joystickGetDigital(2, 8, JOY_DOWN)) offset = LOADER_PRESET;

    if(abs(joystickGetAnalog(2, 3)) >= 10 ||
    joystickGetDigital(2, 5, JOY_UP) || joystickGetDigital(2, 5, JOY_DOWN)) stage = 3;

    printf("%d \n", stackHeight);
    r6U = joystickGetDigital(1, 6, JOY_UP);
    r6D = joystickGetDigital(1, 6, JOY_DOWN);
    p6U = joystickGetDigital(2, 6, JOY_UP);
    p6D = joystickGetDigital(2, 6, JOY_DOWN);


    lift->iterateCtl();
    mogolift->iterateCtl();
		claw->iterateCtl();
		drive->iterateCtl(); //Direct control
    integrator->iterateCtl();
    lift->debug();
		delay(10);
    //writeJINXMessage("jinx test");
	}
}//}
