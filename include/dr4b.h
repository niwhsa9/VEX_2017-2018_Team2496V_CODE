#include "ports.h"
#include "subsystem.h"

class DR4B : Subsystem{
    public:
      DR4B(const char *name, const int *motors, const int *revField,
  			const int num, const int *sensors=(const int *)malloc(1), char id=255):
        Subsystem(name, motors, revField, num, _sensors, id)
        {init();};
      void moveTo();
  		void debug();
  		void iterateCtl();
      void backup();
  		int eStop();
      void init( );
      bool safe();
      void setDesired(int position);

    private:
      int getHeight(char h);

      //Starting potentiometer values for each side of the lift
      int startLiftL;
      int startLiftR;

      const static float lK; //P loop constant

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
};
