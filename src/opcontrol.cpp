#include "main.h"
#include "ports.h"
#include "robot.h"

//extern "C" { //Make compatible with C
void operatorControl() {

	if(isSubInit!=true) { //Ensure subsystems were created
		subsystemInit();
	}
	/* MAIN CONTROL LOOP */
	while (1) {
		if(lift->safe()) {  		//Lift P(I)D control
			lift->iterateCtl();
		} else { 							//Direct control
			lift->backup();
		}
		drive->iterateCtl(); //Direct control
		
		claw->iterateCtl(); //Direct control */
		//printf("alive");
		delay(10);
	}
}//}
