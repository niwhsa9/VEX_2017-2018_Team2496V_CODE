#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 0;
const char *autoModeStr[] = {
  "Primary", "Secondary"
};
int numAuto = 2;
/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

  void autonomous() {
      if(autoMode == 0) {
        /*
        drive->turn(181, 1);
        delay(5000);
        drive->move(36, 100, 1); */
        drive->move(36, 100, 1);
        drive->turn(90, -1);
        drive->move(36, 100, 1);
        drive->turn(90, -1);
        drive->move(36, 100, 1);
        drive->turn(90, -1);
        drive->move(36, 100, 1);
        drive->turn(90, -1);
      }
  }
