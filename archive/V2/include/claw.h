#include "ports.h"
#include "subsystem.h"

#ifndef CLAW_H
#define CLAW_H

class Claw: Subsystem{
    public:
      Claw(const char *name, int motors[10], int revField[10],
  			int num, int sensors[10], char id);
      void moveTo();
      void setDesired(int des);
  		void debug();
  		void iterateCtl();
  		int eStop();
      void init();
      void hold();

    private:
      //drive ports
      int _cm;

      //sensors
      int enc;

      //misc.
      int desired;
};
#endif
