#include "ports.h"
#include "subsystem.h"

#ifndef CLAW_H
#define CLAW_H

class Claw: Subsystem{
    public:
      Claw(const char *name, const int *motors, const int *revField,
  			const int num, const int *sensors=(const int *)malloc(1), char id=255):
        Subsystem(name, motors, revField, num, _sensors, id)
        {init();};
      void moveTo();
      void setDesired(int des);
  		void debug();
  		void iterateCtl();
  		int eStop();
      void init();

    private:
      //drive ports
      int _cm;

      //sensors
      int enc;

      //misc.
      int desired;
};
#endif
