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
      drive->move(65, 127, 1, DRIVE_MIN_SPEED, 2000);
      mogolift->moveMax();
      drive->move(37, 127, -1, DRIVE_MIN_SPEED+7, 2000);
      drive->turn(180, 70, -1);
      //drive->move(6, 127, 1, DRIVE_MIN_SPEED + 7, 1000);
      drive->turn(45, 70, 1);
      drive->move(9, 127, 1, DRIVE_MIN_SPEED + 7, 1000);
      drive->turn(90, 70, -1);
      drive->move(25, 127, 1, 127, 1000);
      drive->move(12, 127, -1, 127, 500);
      drive->move(12, 30, 1, 30, 500);

      drive->move(8, 70, -1, DRIVE_MIN_SPEED, 500);
      drive->turn(90, 70, -1);
      drive->move(6, 70, -1, DRIVE_MIN_SPEED, 500);
      drive->turn(90, 70, -1);
      mogolift->moveMin

      //drive->move(35, 127, 1, 127, 2000);
      //drive->move(12, 127, 1, DRIVE_MIN_SPEED);


  }
