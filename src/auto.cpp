#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 1; //0
const char *autoModeStr[] = {
  "10 Mob G", "20 Mob G L", "20 Mob G R", "Avoid R", "Avoid L", "5 Mob G L"
};
int numAuto = 6;


  void autonomous() {
      //mogolift->moveMin();
      //delay(1000);
      //mogolift->moveMax();
      //delay(5000);
      //drive->turn(45, 70, 1);
      mogolift->moveMin();
      drive->move(72, 127, 1, DRIVE_MIN_SPEED);
      mogolift->moveMax();
      //drive->move(12, 127, 1, DRIVE_MIN_SPEED);


  }
