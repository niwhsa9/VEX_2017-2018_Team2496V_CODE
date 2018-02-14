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

  //lift->desiredLift = 600;
  //lftTsk = taskCreate(liftCtl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  if(digitalRead(1)) {
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
} else if(digitalRead(1) == false){
    integrator->setEm(20);
    lift->setSpeed(40);
    delay(300);
    lift->setSpeed(15);
    mogolift->setEm(-90);
    delay(1100);
    mogolift->setEm(-20);
    drive->move(55, 127, 1, 3000);
    drive->move(8, 40, 1, 600);
  //  drive->move(float distance, int speed, int direction, int minspeed, unsigned int max_time)
    mogolift->setEm(90);
    delay(1100);
    mogolift->setEm(0);
    drive->move(47, 127, -1, 3000);
    if(digitalRead(2) == false) drive->encTurn(710, 127, -1, 2000);
    else drive->clugyencTurn(710, 127, -1, 2000);
    drive->move(20, 60, 1, 300);
    lift->setSpeed(-60);
    delay(700);
    claw->setDesired(-127);
    delay(200);
    claw->setDesired(0);
    lift->setSpeed(40);
    delay(200);
    lift->setSpeed(15);
    mogolift->setEm(-90);
    delay(800);
    mogolift->setEm(0);
    drive->move(18, 127, -1, 4000);
}


}
