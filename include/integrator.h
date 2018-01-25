#include "ports.h"
#include "subsystem.h"

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

class Integrator : Subsystem{
    public:
      Integrator(const char *name, int motors[10], int revField[10],
  		int num, int sensors[10], char id);

  		void debug();
  		void iterateCtl();
  		int eStop();
      void init();
      void setEm(int speed);
      void setStack(int stck, int stg);

    private:

      //drive ports
      int _m;

      int _pot;

};
#endif
