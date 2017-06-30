#include "ports.h"
#include "subsystem.h"


class DR4B : Subsystem{
    public:
      DR4B(const char *name, const int *motors, const int *revField,
  			const int num, const int *sensors=(const int *)malloc(1), char id=255):
        Subsystem(name, motors, revField, num, _sensors, id)
        {init();};
      void moveTo(int position);
  		void debug();
  		void iterateCtl();//use a function pointer to loop through each subsystem and get this
  		int eStop();
      void init(int fr, int );

    private:
      int getHeight(char h);
      //Starting potentiometer values for each side of the lift
      int startLiftL;
      int startLiftR;
      //P loop constant
      const static float lK; //0.2f
      int liftSpeedL;
      int liftSpeedR;
      //desired position (as a zeroed potentiometer value)
      int desiredLift;
      int prevTime;
      //lift ports
      int _tr;
      int _br;
      int _tl;
      int _bl;
      //sensors
      int _lp;
      int _rp;
};
