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



void autonomous() {
/*
  //lift->desiredLift = 600;
  //lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  lift->setSpeed(100);
  delay(500);
  lift->setSpeed(15);
  drive->move(18.0, 50, 1, 2000);

  integrator->setEm(-100);
  delay(1000);
  integrator->setEm(0);
  lift->setSpeed(-40);
  delay(300);
  lift->setSpeed(0);
  claw->setDesired(-100);
  delay(1000);
  claw->setDesired(0);
  drive->move(12.0, 70, -1, 2000);
  */

}
