#include "ports.h"
#include "subsystem.h"

#ifndef DRIVE_H
#define DRIVE_H

class Drive : Subsystem{
    public:
      Drive(const char *name, const int *motors, const int *revField,
  			const int num, const int *sensors=(const int *)malloc(1), char id=255):
        Subsystem(name, motors, revField, num, _sensors, id)
        {init();};
      void move(float distance, int speed, int direction); //tranverse the z_axis fml
      //rename that sheet ^^^
  		void debug();
  		void iterateCtl();
  		int eStop();
      void init();
      void turn(char dir, float deg);
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
