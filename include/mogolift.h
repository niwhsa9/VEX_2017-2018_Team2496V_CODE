#include "ports.h"
#include "subsystem.h"

#ifndef MOGOLIFT_H
#define MOGOLIFT_H

class MogoLift : Subsystem{
    public:
      MogoLift(const char *name, int motors[10], int revField[10],
  		int num, int sensors[10], char id);

  		void debug();
  		void iterateCtl();
  		int eStop();
      void init();
      void moveMax();
      void moveMin();
      void setEm(int speed);


    private:

      //drive ports
      int _lm;
      int _rm;

      int _lstop;
      int _rstop;

      int _lpot;
      int _rpot;


};
#endif
