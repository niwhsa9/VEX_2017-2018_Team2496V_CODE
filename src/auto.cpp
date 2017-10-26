#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 1; //0
const char *autoModeStr[] = {
  "10 Mob G", "20 Mob G L", "20 Mob G R", "Avoid R", "Avoid L", "5 Mob G L"
};
int numAuto = 6;


  void autonomous() {/*
      for (int i = 0; i < 5; i++) {
        mogolift->moveMax();
        mogolift->moveMin();
      }*/
  //  drive->move(24, 127, -1, 4000);

      mogolift->moveMin();
      drive->move(40, 15, 1, 3000);
      mogolift->moveMax();
      drive->move(34, 40, -1, 3000);
      drive->turn(90, 70, 1);
      drive->move(17, 40, 1, 3000);
      drive->turn(90, 70, 1);
      drive->move(40, 127, 1, 127, 1500);
      drive->move(15, 127, -1, 3000);
      drive->move(10, 10, 1, 3000);
      drive->move(10, 20, -1, 3000);
      drive->turn(92, 70, 1); //pls be 90
      //drive->move(50, 10, -1, 2000);
      while(digitalRead(C_LIMIT) == true) drive->setDrive(-30, -30);
      drive->setDrive(10, -30);
      delay(500);
      drive->setDrive(0,0);
      mogolift->moveMin();
      drive->move(8, 15, 1, 2000);
    //  drive->turn(8, 70, -1);
      drive->move(40, 15, 1, 2000);
      mogolift->moveMax();
      drive->move(48, 20, -1, 2000);
      drive->move(3, 15, 1, 2000);
      drive->turn(90, 70, -1);
      drive->move(65, 45, 1, 15, 3000);
      mogolift->moveMin();
    //  drive->move(20, 20, -1, 1000);
      drive->move(12, 45, -1, 3000);
      //put down mogo

      mogolift->moveMax();
      drive->move(10, 15, 1, 3000);
      drive->move(10, 20, -1, 3000);
      drive->turn(90, 70, 1);
      //drive->move(50, 10, -1, 2000);
      while(digitalRead(C_LIMIT) == true) drive->setDrive(-30, -30);
      drive->setDrive(10, -30);
      delay(500);
      drive->setDrive(0,0);



    /*
      mogolift->moveMin();
      drive->move(40, 90, 1, 3000); //65
      drive->move(15, 15, 1, 3000); //65
      mogolift->moveMax();
      drive->move(36, 50, -1, 3000);
      delay(500);
      drive->turn(90, 70, -1);
      drive->move(6, 50, -1, 1000);
      drive->move(2, 50, 1, 2000);
      //drive->move(5, 127, -1, DRIVE_MIN_SPEED+7, 2000);

      drive->turn(45, 60, -1);
      //drive->move(6, 127, 1, DRIVE_MIN_SPEED + 7, 1000);
      //drive->turn(45, 70, 1);

      drive->move(23, 50, 1, 2000);
      drive->turn(90, 70, -1);

      drive->move(25, 127, 1, 1000);
      delay(500);
      drive->move(10, 127, -1, 127, 500);
      //out of 20
      delay(500);
      drive->move(15, 30, 1, 500);
      delay(500);
      drive->move(6, 70, -1, 20, 500);
      drive->turn(90, 70, 1);
      drive->move(50, 50, -1, 50, 2000);
      */


  }
