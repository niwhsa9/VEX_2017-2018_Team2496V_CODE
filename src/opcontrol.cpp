#include "main.h"
#include "ports.h"
#include "robot.h"

extern "C" { //Make compatible with C
void operatorControl() {

	if(isSubInit!=true) { //Ensure subsystems were created
		subsystemInit();
	}
	/* MAIN CONTROL LOOP */
	while (1) {
		if(lift->safe()) {  		//Lift P(ID) control
			lift->iterateCtl();
		} else { 							//Direct control
			lift->backup();
		}
		/*************************
		* HERE DOWN NEEDS UPDATE *
		**************************/
		


		if (joystickGetDigital(1, 5, JOY_UP) && joystickGetDigital(1, 5, JOY_DOWN)) {
                        motorSet(M_CLAW, 30);
                }
		else if(joystickGetDigital(1, 5, JOY_UP)) {
			motorSet(M_CLAW, 80);
		} else if (joystickGetDigital(1, 5, JOY_DOWN)) {
			motorSet(M_CLAW, -80);
		} else {
			motorSet(M_CLAW, 0);
		delay(10);
		}
	}
}}
