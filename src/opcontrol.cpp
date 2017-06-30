/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "ports.h" //header file with #define macros for all motor/sensor ports

//Starting potentiometer values for each side of the lift
int startLiftL;
int startLiftR;

//P loop constant
const float lK = 0.2f; //0.2f
int liftSpeedL = 127;
int liftSpeedR = 127;

//desired position (as a zeroed potentiometer value)
int desiredLift = 0;
int prevTime;
void liftCtlIterate() {
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
			desiredLift = 418; //make a macro define 348
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
void operatorControl() {
	startLiftL = analogRead(A_LIFT_POT_L);
	startLiftR = analogRead(A_LIFT_POT_R);
	printf("LEFT %d", analogRead(A_LIFT_POT_L));
	printf("RIGHT %d", analogRead(A_LIFT_POT_R));
	prevTime = millis();
	while (1) {
		if((int)millis%100 == 0) { //debug
			printf("LEFT %d", analogRead(A_LIFT_POT_L));
        		printf("RIGHT %d", analogRead(A_LIFT_POT_R));
		}
		if(analogRead(A_LIFT_POT_L) != A_UNPLUG && analogRead(A_LIFT_POT_R) != A_UNPLUG) {
			liftCtlIterate();
		} else {
			//no loop controll here
		}
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
}

