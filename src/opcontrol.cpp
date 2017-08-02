#include "main.h"
#include "ports.h"
#include "robot.h"

int prevTime = 0;
int curTime = 0;
//extern "C" { //Make compatible with C
void operatorControl() {
  lcdSetBacklight(uart2, false);

	if(isSubInit!=true) { //Ensure subsystems were created
		subsystemInit();
	}
	/* MAIN CONTROL LOOP */
	while (1) {
		curTime = millis();
		if(lift->safe()) {  		//Lift P(I)D control if potentiometers are plugged in
			lift->iterateCtl();
		} else { 							//Direct control otherwise
			lift->backup();
		}
		drive->iterateCtl(); //Direct control
		claw->iterateCtl(); //Direct control

		if(curTime - prevTime >= 10000) {
			char line1[16];
    	char line2[16];
			sprintf(line1, "< Battery >");
			sprintf(line2, "%fV", (float)powerLevelMain()/1000);
			lcdSetText(uart2, 1, line1);
			lcdSetText(uart2, 2, line2);
			prevTime = curTime;
		}
		delay(10);
	}
}//}
