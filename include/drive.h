#include "ports.h"
#include "subsystem.h"

#ifndef DRIVE_H
#define DRIVE_H

class Drive : Subsystem{
    public:
      Drive(const char *name, int motors[10], int revField[10],
  		int num, int sensors[10], char id);

      void move(float distance, int speed, int direction); //tranverse the z_axis fml
      void move(float distance, int speed, int direction, unsigned int max_time);
      void f_move(float distance, int speed, int direction);
      //rename that sheet ^^^
  		void debug();
  		void iterateCtl();
  		int eStop();
      void init();
      void turn(float deg, int speed, char dir);
      void callibrateGyro();
      Encoder le;
      Encoder re;
      Gyro gyro;

    private:

      const static float zK; //Drive constant
      const static float tK; //Turn constant

      //drive ports
      int _fr;
      int _br;
      int _fl;
      int _bl;

      //sensors
      int er1;
      int er2;
      int el1;
      int el2;
      int gy;

};
#endif
