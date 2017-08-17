#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 2; //0
const char *autoModeStr[] = {
  "10 Mob G", "20 Mob G L", "20 Mob G R", "Avoid R", "Avoid L",
};
int numAuto = 5;

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
        //delay(3000); //REMOVE ME
        drive->move(47, 127, 1);
        drive->turn(140, 100, 1); //140
        drive->move(20, 50, -1, 2500); //25k
        drive->turn(45, 60, 1);
        drive->move(6, 40, -1); //6
        drive->turn(37, 60, 1); //45

        drive->f_move(23, 127, -1); //overload
        lift->setDesired(0);
        drive->f_move(20, 127, 1);


        taskDelete(upckTsk);
        taskDelete(lftTsk);
      }
      else if(autoMode == 2) {
        TaskHandle upckTsk = taskCreate(unpack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        TaskHandle lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        delay(500);
        drive->move(48, 127, -1);
        lift->setDesired(450);
        delay(300);
        drive->move(47, 127, 1);
        drive->turn(140, 100, -1); //140
        drive->move(20, 50, -1, 2500); //25k
        drive->turn(45, 60, -1);
        drive->move(6, 40, -1); //6
        drive->turn(37, 60, -1); //45
        drive->f_move(23, 127, -1); //overload
        lift->setDesired(0);
        drive->f_move(20, 127, 1);
        taskDelete(upckTsk);
        taskDelete(lftTsk);
      }
      else if(autoMode == 3 || autoMode == 4) {
        int dir = 1;
        if(autoMode == 4) dir = -1;
        claw->setDesired(127);
        //claw->hold();
        drive->move(6, 50, 1);
        TaskHandle upckTsk = taskCreate(unpack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        TaskHandle lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        delay(1000);
        claw->hold();
        lift->setDesired(1100);
        delay(500);
        drive->move(7 , 50, 1);
        lift->setDesired(800);
      //  while(!lift->prevOpComplete);
        delay(1000);
        claw->setDesired(-60);
        //lift->setDesired(1100);
        delay(500);
        //while(!lift->prevOpComplete);
        claw->setDesired(0);
        drive->move(6, 50, -1);
        drive->turn(100, 100, -1 * dir);
        lift->setDesired(50);
        drive->f_move(65, 127, -1);

        delay(2000);
        taskDelete(upckTsk);
        taskDelete(lftTsk);
      }
  }
