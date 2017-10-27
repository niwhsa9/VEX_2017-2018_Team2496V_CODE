#include "drive.h"
const float Drive::zK= 0.00035f;
const float Drive::tK = 0.98f; //1.0
const float Drive::t2K = 2.5;

/* BEST SETTINGS SO FAR
P   3.0    =     =     =      =       =       5.0f
I   0.13   =     =     0.18   0.22    0.23    0.20f
D   0.0    =     =     5.0    8.0     8.2     18.5f
IL  20     25    =     20     =       =       =
N:  50     =    70     =      =       =       =

*/



const float Drive::pK = 5.0f; //3.0f
const float Drive::iK = 0.20f; //0.07f
const float Drive::dK = 18.5; //0.0
const int Drive::integ_limit = 20;

const float Drive::dpK = 0.6f; //3.0f
const float Drive::diK = 0.05f; //0.07f
const float Drive::ddK = 5; //0.0

Drive::Drive(const char *name, int motors[10], int revField[10],
int num, int sensors[10], char id=255):
  Subsystem(name, motors, revField, num, _sensors, id)
  {};


/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void Drive::init() {
  _fr1 = 0;
  _br1 = 1;
  _fl1 = 2;
  _bl1 = 3;
  _fr2 = 4;
  _br2 = 5;
  _fl2 = 6;
  _bl2 = 7;

  el1 = 0;
  el2 = 1;
  er1 = 2;
  er2 = 3;
  gy = 4;

  le = encoderInit(D_DRIVE_ENC_L1, D_DRIVE_ENC_L2, false);
  re = encoderInit(D_DRIVE_ENC_R1, D_DRIVE_ENC_R2, true); //CHANGE FROM HARDCODE

  gyro = gyroInit(A_DRIVE_GYRO, 0);

  //zK = 0.2;
  //tK = 0.2;
}

void Drive::setDrive(int left, int right) {

    setMotor(_bl1, left);
    setMotor(_bl2, left);

    setMotor(_br1, right);
    setMotor(_br2, right);

    setMotor(_fr1, right);
    setMotor(_fr2, right);

    setMotor(_fl1, left);
    setMotor(_fl2, left);
}

/*
* Callibrates gyroscope sensors,
* NEVER USE WITHIN LOOP, hogs resources
* and makes gyro unusuable
*/
void Drive::callibrateGyro() {
  gyroShutdown(gyro);
  gyro = gyroInit(A_DRIVE_GYRO, 0);
}

/*
* Move robot specified distance and direction through
* encoder count (SLEW). Take input parameter of distance
* in inches and speed
*/

void Drive::move(float distance, int speed, int direction, int minspeed,unsigned int max_time) {
  //Reset Encoders & initalize variables needed
  int start_time = millis();
  encoderReset(le);
  encoderReset(re);
  int v_le = 0;
  int v_re = 0;
  float lSpeed = 0;
  float rSpeed = 0;

  float ticks = (distance/(4*PI)) *  360; //distance/circumfrence = revolutions needed
                                          //360 ticks per revolution * revolutions needed = ticks

  //Check that robot isn't at the target within a threshold
  while((abs(ticks-v_le) >= DRIVE_MOVE_THRESHOLD && abs(ticks-v_re) >= DRIVE_MOVE_THRESHOLD) && (millis() - start_time) < max_time) {
      //Update current encoder values
      v_le = abs(encoderGet(le));
      v_re = abs(encoderGet(re));
    //  printf("r: %f   d: %f", rSpeed, ticks);
      //Speed is proportional to distance from target, so it stops without roll at the target
      if(v_le >= ticks/3) { //REMOVE
        lSpeed = (ticks-v_le) * speed * direction * zK;
        rSpeed = (ticks-v_re) * speed * direction * zK;
      } else {
        lSpeed = speed * direction;
        rSpeed = speed * direction;
      }
      //If speed falls below certain values, motors will stall without movement, stop this
      if(abs(lSpeed) <= minspeed) lSpeed = minspeed * direction;
      if(abs(rSpeed) <= minspeed) rSpeed = minspeed * direction;

      //Set motors accordingly
      setDrive((int)lSpeed, (int) rSpeed);
      delay(10);
  }
  setAll(0); //Disable motors
  }


void Drive::move(float distance, int speed, int direction, unsigned int max_time) {
    float ticks = (distance/(4*PI)) *  360;
    encoderReset(le);
    encoderReset(re);
    int v_le = 0;
    int v_re = 0;

    bool flag = false;
    long stime = millis();
    int ltime = 0;
    float lSpeed = 0;
    float rSpeed = 0;

    int integ_vle = 0;
    int integ_vre = 0;

    int integ_count = 0;

    int lerror = 0;
    int rerror = 0;
    int prevlError = 0;
    int prevrError = 0;
    //Check robot isn't at target within a threshold
    while(true) {
        //Grab integrated gyro value from PROS library
        v_le = abs(encoderGet(le));
        v_re = abs(encoderGet(re));

        lerror = ticks-v_le;
        rerror = ticks-v_re;
        integ_vle+= lerror;
        integ_vre+= rerror;
        integ_count++;

        lSpeed = ((lerror * dpK) + ((lerror-prevlError) * ddK) + (integ_vle * diK)) * ((float)speed/127.0) * direction;
        rSpeed = ((rerror * dpK) + ((rerror-prevrError) * ddK) + (integ_vre * diK)) * ((float)speed/127.0) * direction;

      //  printf("\ntarget %f vle: %d speed %f rle %d speed %f", ticks, v_le, lSpeed, v_re, rSpeed);
      printf("\ntarget: %f vle: %d speed: %f", ticks, v_le, lSpeed);
        setDrive((int)lSpeed, (int) rSpeed);
        prevlError = lerror;
        prevrError = rerror;

        if(integ_count >= integ_limit) {
          integ_vle = 0;
          integ_vre = 0;
          integ_count = 0;
        }


        if(millis()-stime >= max_time) break;
        delay(10);
    }
    setAll(0);  //Disable motors

}

/*
* Turn robot specified angle in degrees. Direction is 1 for positive, -1 for negative
*/
void Drive::turn(float degrees, int speed, char direction) {
  bool flag = false;
  long stime = millis();
  int ltime = 0;
  gyroReset(gyro);
  float lSpeed = 0;
  float rSpeed = 0;
  int cur_gyro = 0;
  int integ_gyro = 0;
  int integ_count = 0;
  int error = 0;
  int prevError = 0;
  //Check robot isn't at target within a threshold
  while(true) {
      //Grab integrated gyro value from PROS library
      cur_gyro = abs(gyroGet(gyro));
      error = degrees - cur_gyro;
      integ_gyro+= error;
      integ_count++;

      lSpeed = ((error * pK) + ((error-prevError) * dK) + (integ_gyro * iK)) * ((float)speed/127.0) * direction;
      rSpeed = lSpeed * -1;

      printf("\ngyro: %d speed %f", cur_gyro, lSpeed);
      setDrive((int)lSpeed, (int) rSpeed);
      prevError = error;

      if(integ_count >= integ_limit) {
        integ_gyro = 0;
        integ_count = 0;
      }

      //undef
      if(abs(integ_gyro - degrees) < DRIVE_TURN_THRESHOLD && flag == false) {
         flag = true;
         ltime = millis();
      } else if(abs(integ_gyro - degrees) < DRIVE_TURN_THRESHOLD && flag == true) {
          if(millis()-ltime >= 1020) break; //3020 plz
          else flag = false;
      }
      if(millis()-stime >= 1600) break;
      delay(10);
  }
  setAll(0);  //Disable motors

}



/*
* Debug
*/
void Drive::debug() {
  //printf("LEFT %d", );
  //printf("RIGHT %d", getHeight('r')-startLiftR);
    printf("\nLEFT %d", encoderGet(le));
    printf("\nRIGHT %d", encoderGet(re));
}

/*
* Emergency stop all motors and deallocate
* memory to be called on failure event
*/
int Drive::eStop() {
  setAll(0);
  return 0;
}



/*
* Main control loop with user input
*/
void Drive::iterateCtl() {
  int js[2];
  float speed[2];
  js[0] = joystickGetAnalog(1,3); //l
  js[1]  =  joystickGetAnalog(1, 2); //r
  for(int i = 0; i < 2; i++) {
	/*
      if(js[i] > -75 && js[i] < 75)
	 speed[i] = (0.3333) * js[i];
      else if(js[i] >= 75) speed[i] = 1.96153 * (js[i]-75) + 25;
      else speed[i] = 1.96153 * (js[i] + 75) - 25;*/
      int dir = 1;
      if(js[i] < 0) dir = -1;
      speed[i] = (((float)js[i]/127) * ((float)js[i]/127)) * 127 * dir;

  }
  int left =(int) speed[0];
  int right = (int) speed[1];

//  printf("left %d", left);
//  printf("right %d", right);
setDrive(left, right);
}
