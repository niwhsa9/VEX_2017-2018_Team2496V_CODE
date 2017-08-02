#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 0;
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
        TaskHandle lftTsk = taskCreate(unpack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        drive->move(48, 127, -1);
        taskDelete(lftTsk);
        lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

        delay(5000);

        //taskDelete(scheduler);
        /*

        drive->move(36, 100, 1);

        delay(500);
        drive->turn(90, -1);
        delay(500);
        drive->move(36, 100, 1);
          delay(500);
        drive->turn(90, -1);
        delay(500);
        drive->move(36, 100, 1);
          delay(500);
        drive->turn(90, -1);
        delay(500);
        drive->move(36, 100, 1);
          delay(500);
        drive->turn(90, -1);  */

        drive->move(48, 127, -1);
      }
  }
