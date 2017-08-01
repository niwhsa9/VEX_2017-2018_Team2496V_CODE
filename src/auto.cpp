#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 0;
const char *autoModeStr[] = {
  "Primary", "Secondary"
};
int numAuto = 2;


  void autonomous() {
      if(autoMode == 0) {
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
