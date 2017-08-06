#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 1; //0
const char *autoModeStr[] = {
  "Primary", "Secondary"
};
int numAuto = 2;

bool unpacked = false;

  void liftCtl(void *) {
    while(1) {
      lift->moveTo();
      delay(10);
    }
  }

  void unpack(void *) {
    lift->unpack();
  }


  void autonomous() {
      if(autoMode == 0) {
        TaskHandle upckTsk = taskCreate(unpack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        TaskHandle lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        delay(500);
        drive->move(48, 127, -1);
        lift->setDesired(450);
        delay(300);
        drive->move(36, 127, 1);
        drive->turn(180, 100, 1);
        drive->move(30, 127, -1);
        lift->setDesired(10);
        delay(300);
        drive->move(24, 127, 1);

        //drive->turn(180, -1);
        taskDelete(upckTsk);
        taskDelete(lftTsk);

      } else if(autoMode == 1) {
        TaskHandle upckTsk = taskCreate(unpack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        TaskHandle lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        delay(500);
        drive->move(48, 127, -1);
        lift->setDesired(450);
        delay(300);
        drive->move(44, 127, 1); //42
        drive->turn(135, 100, 1);
        drive->move(20, 50, -1);
        drive->turn(45, 60, 1);
        drive->move(6, 40, -1); //6
        drive->turn(37, 60, 1); //45

        drive->f_move(15, 127, -1); //overload
        lift->setDesired(0);
        drive->f_move(20, 127, 1);
        /*
        drive->move(14, 127, -1);
        drive->turn(45, 70, -1);
        drive->move(18, 40, -1);
        drive->turn(90, 127, 1);
        */

        //drive->turn(180, -1);
        taskDelete(upckTsk);
        taskDelete(lftTsk);
      }
  }
