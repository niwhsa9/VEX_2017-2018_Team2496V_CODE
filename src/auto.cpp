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
      drive->move(40, 15, 1, 1500);
      mogolift->moveMax();
      drive->move(34, 40, -1, 1500);
      drive->turn(90, 70, 1);
      drive->move(17, 40, 1, 1500);
      drive->turn(90, 70, 1);
      drive->move(40, 127, 1, 127, 1500);
      drive->move(15, 127, -1, 1500);
      drive->move(10, 10, 1, 1500);
      drive->move(10, 20, -1, 1500);
      drive->turn(92, 70, 1); //pls be 90
      //drive->move(50, 10, -1, 2000);
      while(digitalRead(C_LIMIT) == true) drive->setDrive(-30, -30);
      while(digitalRead(D_RIGHT_BUMP) == true) drive->setDrive(7, -30);
      drive->setDrive(-25, -25);
      delay(2000);
      drive->setDrive(0,0);
      mogolift->moveMin();
      drive->move(8, 15, 1, 1500);

      //drive->turn(8, 70, 1);
      drive->move(40, 15, 1, 1500);
      mogolift->moveMax();
      drive->move(48, 20, -1, 3000);
      drive->move(3, 15, 1, 1500);
      drive->turn(90, 70, -1);
      drive->move(65, 38, 1, 23, 3000); //DIS ONE
      mogolift->moveMin();
      mogolift->setEm(40);
    //  drive->move(20, 20, -1, 1000);
      drive->move(10, 20, -1, 3000);
      //put down mogo

      mogolift->moveMax();
      drive->move(10, 10, 1, 1500);
      drive->move(10, 10, -1, 1500);
      drive->turn(90, 70, 1);
      //drive->move(50, 10, -1, 2000);
      while(digitalRead(C_LIMIT) == true) drive->setDrive(-30, -30);
      while(digitalRead(D_RIGHT_BUMP) == true) drive->setDrive(7, -30);
      drive->setDrive(-25, -25);
      delay(2000);
      drive->setDrive(0,0);

      drive->move(35, 15, 1, 2400);
      drive->turn(44, 70, 1);
      mogolift->moveMin();
      drive->move(68, 15, 1, 2700);
      mogolift->moveMax();
      drive->turn(90, 70, -1);
      drive->move(17, 20, 1, 1500);
      drive->turn(90, 70, 1);
      drive->move(25, 127, 1, 127, 1500);
    }
