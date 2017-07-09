#include "main.h"
#include "ports.h"
#include "robot.h"
bool isSubInit = false;
DR4B *lift;
Drive *drive;
Claw *claw;

void subsystemInit() {
  /* LIFT INITALIZATION */
  int liftMotors[] = {M_LIFT_TR, M_LIFT_BR, M_LIFT_TL, M_LIFT_BL};
  int liftRev[] = {1, 1, -1, -1};
  int liftSensors[] = {A_LIFT_POT_L, A_LIFT_POT_R};
  lift = new DR4B("Double Reverse Four Bar", liftMotors, liftRev, 4, liftSensors, 0);
  lift->init();
  /* DRIVE INITALIZATION */
  int driveMotors[] = {M_DRIVE_FR, M_DRIVE_BR, M_DRIVE_FL, M_DRIVE_BL};
  int driveRev[] = {-1, -1, 1, 1};
  int driveSensors[] = {D_DRIVE_ENC_L1, D_DRIVE_ENC_L2, D_DRIVE_ENC_R1, D_DRIVE_ENC_R2, A_DRIVE_GYRO};
  drive = new Drive("Drive", driveMotors, driveRev, 4, driveSensors, 1); //4 ports, 6 motors
  drive->init();
  /*CLAW INITALIZATION*/
  int clawMotors[] = {M_CLAW};
  int clawRev[] = {1};
  int clawSensors[] = {I2C_CLAW_ENC};
  claw = new Claw("Claw", clawMotors, clawRev, 1, clawSensors, 2);
  claw->init();


  isSubInit = true;
}

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
 extern "C" {
void initializeIO() {
    watchdogInit();
}


/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
  setTeamName("2496V");
  imeInitializeAll();
  subsystemInit();
}
}
