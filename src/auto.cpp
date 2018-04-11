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
      lift->iterateCtl();
      integrator->iterateCtl();
      delay(10);
    }
  }

  void mogoDown(void *) {
    stackHeight = 4;
    stage = 1;
    delay(200);
    mogolift->setEm(-90);
    delay(1100);
    mogolift->setEm(-20);
  }

  void secondCone(void *) {
    stage = 1;
    delay(800);
    claw->setDesired(-20);
    delay(300);
    claw->setDesired(0);
  }
  void simIntakeMogo(void *) {
    mogolift->setEm(90);
    delay(1000);
    mogolift->setEm(0);
    claw->setDesired(-30);
    delay(200);
    stackHeight = 4;
    stage = 1;
    delay(200);
    dCmd = millis();
  }


void autonomous() {

  if(digitalRead(1) && digitalRead(3)) {
    //29 pt 00
    lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    taskCreate(mogoDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    delay(600);
    drive->move(50, 60, 1, 2000);
    mogolift->setEm(90);
    stackHeight = 0;
    delay(1100);
    stage = 1;
    delay(500);
    delay(300);
    mogolift->setEm(0);
    claw->setDesired(-30);
    delay(200);
    stackHeight = 4;
    stage = 1;
    delay(200);
    dCmd = millis();
    stage = 0;
    stackHeight = 3;
    claw->setDesired(0);
    delay(200);
    drive->move(16, 30, 1, 1000);

    claw->setDesired(120);
    delay(300);
    taskCreate(secondCone, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    drive->move(50, 120, -1, 2000);
    if(digitalRead(2) == false) drive->turn(45, 127, -1);//drive->clugyencTurn(270, 80, -1, 1000);
    else drive->turn(45, 127, 1);//drive->encTurn(270, 80, -1, 1000);
    drive->move(27, 80, -1, 1300);
    if(digitalRead(2) == false) drive->turn(90, 127, -1);//drive->clugyencTurn(470, 80, -1, 700);
    else drive->turn(90, 127, 1);//drive->encTurn(470, 80, -1, 700);
    delay(100);
    taskCreate(mogoDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    drive->move(40, 127, 1, 1500);
    mogolift->setEm(100);
    drive->move(40, 127, -1, 1000);
    mogolift->setEm(0);
    taskDelete(lftTsk);
} else if(digitalRead(1) ==false  && digitalRead(3) == false) {
  //STATIONARY 11
  lift->setSpeed(100);
  delay(500);
  lift->setSpeed(15);
  drive->move(18.0, 50, 1, 2000);

  integrator->setEm(-100);
  delay(1000);
  integrator->setEm(0);
  lift->setSpeed(-40);
  delay(600);
  lift->setSpeed(0);
  claw->setDesired(-100);
  delay(1000);
  claw->setDesired(0);
  drive->move(12.0, 70, -1, 2000);
}

else if(digitalRead(1) == false && digitalRead(3)){
    //21 PT
    lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    taskCreate(mogoDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    delay(600);
    drive->move(50, 60, 1, 2000);
    mogolift->setEm(90);
    stackHeight = 0;
    delay(1100);
    stage = 1;
    delay(500);
    mogolift->setEm(0);
    claw->setDesired(-90);
    delay(300);
    dCmd = millis();
    stage = 0;
    stackHeight = 3;
    claw->setDesired(0);
    delay(200);
    drive->move(16, 30, 1, 1000);

    claw->setDesired(120);

    //stack second cone
    delay(300);
    stage = 1;
    delay(800);
    claw->setDesired(-100);
    delay(400);
    claw->setDesired(0);
    stage = 0;
    stackHeight++;
    dCmd = millis()-100;
    delay(400);
    drive->move(24, 30, 1, 1000);
    claw->setDesired(100);
    delay(300);
    //stack third cone
    taskCreate(secondCone, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

    drive->move(58, 120, -1, 2000);
    if(digitalRead(2) == false) drive->turn(190, 127, 1);//drive->clugyencTurn(270, 80, -1, 1000);
    else drive->turn(190, 127, -1);//drive->encTurn(270, 80, -1, 1000);
      taskCreate(mogoDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    //drive->setDrive(127, 20);
    delay(1000);
  //  drive->setDrive(127, 20);
    drive->move(30, 70, -1, 1000);
    taskDelete(lftTsk);

}


}
