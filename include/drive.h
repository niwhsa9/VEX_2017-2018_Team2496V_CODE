#include "ports.h"
#include "subsystem.h"

#ifndef DRIVE_H
#define DRIVE_H

class Drive : Subsystem{
    public:
      Drive(const char *name, int motors[10], int revField[10],
  		int num, int sensors[10], char id);

      void move(float distance, int speed, int direction, int minspeed, unsigned int max_time); //tranverse the z_axis fml
      void move(float distance, int speed, int direction, unsigned int max_time);
      void f_move(float distance, int speed, int direction);
      void setDrive(int left, int right);
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
      const static float t2K;

      const static float pK;  //F
      const static float dK;  //U
      const static float iK;  //K

      const static float dpK;  //F
      const static float ddK;  //U
      const static float diK;  //K

      const static int integ_limit;

      //drive ports
      int _fr1;
      int _br1;
      int _fl1;
      int _bl1;
      int _fr2;
      int _br2;
      int _fl2;
      int _bl2;

      //sensors
      int er1;
      int er2;
      int el1;
      int el2;
      int gy;

};
#endif
