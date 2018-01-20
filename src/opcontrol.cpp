#include "main.h"
#include "ports.h"
#include "robot.h"

int prevTime = 0;
int curTime = 0;

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
    lift->iterateCtl();
    mogolift->iterateCtl();
		claw->iterateCtl();
		drive->iterateCtl(); //Direct control
    integrator->iterateCtl();
		delay(10);
	}
}//}
