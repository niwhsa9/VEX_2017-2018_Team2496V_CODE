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
      drive->turn(180, 127, 1);
      //drive->move(36, 127, 1);


  }
