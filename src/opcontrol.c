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
#include "ports.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

int startLiftL;// = analogRead(A_LIFT_POT_L);
int startLiftR;// = analogRead(A_LIFT_POT_R);
const float lK = 0.2f;
int liftSpeedL = 127;
int liftSpeedR = 127;
int desiredLift = 0;
int prevTime;// = millis();
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
	} else if(joystickGetDigital(1,8, JOY_UP)){
		if(millis() - prevTime) >= 10) {
			prevTime = millis();
			desiredLift = 348; //make a macro define
		}
	}

	if(desiredLift > 1620) desiredLift = 1620;
	else if (desiredLift < 5) desiredLift = 5;
	//else if (desiredLift-currentLiftL >= 200) desiredLift = currentLiftL+200;
	//else if (desiredLift-currentLiftL <= -200) desiredLift =currentLiftL -200;

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
	prevTime = millis();
	while (1) {
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
                        motorSet(M_CLAW, 15);
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
