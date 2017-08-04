#include "ports.h"
#include "subsystem.h"

#ifndef DR4B_H
#define DR4B_H

class DR4B : Subsystem{
    public:
      DR4B(const char *name, int motors[10], int revField[10],
  		const int num, int sensors[10], const char id);
      void moveTo();
  		void debug();
  		void iterateCtl();
      void backup();
  		int eStop();
      void init();
      bool safe();
      void setDesired(int position);
      void unpack();
      int getHeight(char h);
      bool prevOpComplete;
      bool safety;

    private:


      //Starting potentiometer values for each side of the lift
      int startLiftL;
      int startLiftR;

      const static float lK; //P loop constant
      const static float dK; //D loop constant
      //Lift operating speed
      int liftSpeedL;
      int liftSpeedR;

      int desiredLift; //desired position (as a zeroed potentiometer value)
      int prevTime;

      //lift ports
      int _tr;
      int _br;
      int _tl;
      int _bl;

      //sensors
      int _lp;
      int _rp;

      int prevErrorL;
      int prevErrorR;
};
#endif
