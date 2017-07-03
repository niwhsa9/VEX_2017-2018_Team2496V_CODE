#include "main.h"
#include "ports.h"
#include "dr4b.h"

extern "C" { //Make compatible with C
void operatorControl() {

	//* LIFT INITALIZATION *//
	int liftMotors[] = {M_LIFT_TR, M_LIFT_BR, M_LIFT_TL, M_LIFT_BL};
	int liftRev[] = {1, 1, -1, -1};
	int liftSensors[] = {A_LIFT_POT_L, A_LIFT_POT_R};
	DR4B lift(
		"Double Reverse Four Bar",
		liftMotors,
		liftRev,
		4,
		liftSensors,
		0
	);
	lift.init();

	/* MAIN CONTROL LOOP */
	while (1) {
		if(lift.safe()) {  		//Lift P(ID) control
			lift.iterateCtl();
		} else { 							//Direct control
			lift.backup();
		}
		/*************************
		* HERE DOWN NEEDS UPDATE *
		**************************/
		motorSet(M_DRIVE_BL, joystickGetAnalog(1, 3));
		motorSet(M_DRIVE_BR, -joystickGetAnalog(1, 2));
		motorSet(M_DRIVE_FR, -joystickGetAnalog(1, 2));
		motorSet(M_DRIVE_FL, joystickGetAnalog(1, 3));


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
