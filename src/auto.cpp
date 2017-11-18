#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 1; //0
const char *autoModeStr[] = {
  "10 POINT L", "10 POINT R", "20 POINT L", "20 POINT R"
};
int numAuto = 4;
TaskHandle lftTsk;

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

    TaskHandle upckTsk = taskCreate(unpack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    if(autoMode == 0 || autoMode == 1) {
      int dir = 1;
      if(autoMode == 1) dir = -1;
      delay(500);
      drive->move(52, 127, -1, 2200);
      lift->setDesired(400);
      delay(600);
      drive->move(42, 127, 1, 2200);
      drive->turn(180, 80, -1 * dir);
      drive->move(11, 127, -1, 1000);
      drive->turn(30, 80, 1 * dir);
      lift->setDesired(470);
      drive->move(17, 127, -1, 1400);
      lift->setDesired(0);
      drive->move(40, 127, 1, 3000);
    }
    if(autoMode == 2 || autoMode == 3) {
      int dir = 1;
      if(autoMode == 2) dir = -1;
      delay(500);
      drive->move(52, 127, -1, 2200);
      lift->setDesired(500);
      delay(600);
      drive->move(42, 127, 1, 2200);
      drive->turn(180, 80, -1 * dir);
      drive->move(11, 60, -1, 1000);
      drive->turn(45, 80, 1 * dir);
      drive->move(17, 60, -1, 1000);
      drive->turn(90, 50, -1 * dir);
      drive->move(30, 127, -1, 127, 2000);
      lift->setDesired(0);
      delay(300);
      drive->move(30, 127, 1, 2000);

    }
    //if(lftTsk != NULL) taskDelete(lftTsk);

}
