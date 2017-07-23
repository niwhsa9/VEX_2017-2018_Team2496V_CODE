#include "drive.h"
const float Drive::zK= 0.2f;
const float Drive::tK = 0.05f;

Drive::Drive(const char *name, int motors[10], int revField[10],
int num, int sensors[10], char id=255):
  Subsystem(name, motors, revField, num, _sensors, id)
  {};


/*
* Initalize variables needed for operation,
* ALWAYS EXPLICITLY call this after initalization.
*/
void Drive::init() {
  _fr = 0;
  _br = 1;
  _fl = 2;
  _bl = 3;

  el1 = 0;
  el2 = 1;
  er1 = 2;
  er2 = 3;
  gy = 4;

  le = encoderInit(_sensors[el1], _sensors[el2], false);
  re = encoderInit(_sensors[er1], _sensors[er2], true);
  gyro = gyroInit(_sensors[gy], 0);
}

/*
* Callibrates gyroscope sensors,
* NEVER USE WITHIN LOOP, hogs resources
* and makes gyro unusuable
*/
void Drive::callibrateGyro() {
  gyroShutdown(gyro);
  gyro = gyroInit(_sensors[gy], 0);
}

/*
* Move robot specified distance and direction through
* encoder count (SLEW). Take input parameter of distance 
* in inches and speed
*/
void Drive::move(float distance, int speed, int direction) {
  //Reset Encoders & initalize variables needed
  encoderReset(le);                                              
  encoderReset(re);
  int v_le = 0;
  int v_re = 0;
  int lSpeed = 0;
  int rSpeed = 0;
 
  float ticks = (distance/(4*PI)) *  360; //distance/circumfrence = revolutions needed
                                          //360 ticks per revolution * revolutions needed = ticks

  //Check that robot isn't at the target within a threshold
  while(abs(ticks-v_le) >= DRIVE_MOVE_THRESHOLD && abs(ticks-v_re) >= DRIVE_MOVE_THRESHOLD) {
      //Update current encoder values
      v_le = abs(encoderGet(le));
      v_re = abs(encoderGet(re));

      //Speed is proportional to distance from target, so it stops without roll at the target
      lSpeed = (ticks-v_le) * speed * direction;
      rSpeed = (ticks-v_re) * speed * direction;

      //If speed falls below certain values, motors will stall without movement, stop this
      if(abs(lSpeed) <= DRIVE_MIN_SPEED) lSpeed = DRIVE_MIN_SPEED * direction;
      if(abs(rSpeed) <= DRIVE_MIN_SPEED) rSpeed = DRIVE_MIN_SPEED * direction;

      //Set motors accordingly 
      setMotor(_bl, lSpeed);
      setMotor(_br, rSpeed);
      setMotor(_fr, rSpeed);
      setMotor(_fl, lSpeed);
  }
  setAll(0); //Disable motors
}

/*
* Turn robot specified angle in degrees. Direction is 1 for positive, -1 for negative
*/
void Drive::turn(char direction, float degrees) {
  //Reset gyro & initalize variables
  gyroReset(gyro);
  int lSpeed = 0;
  int rSpeed = 0;
  int integ_gyro = 0;

  //Check robot isn't at target within a threshold
  while(abs(integ_gyro - degrees) > DRIVE_TURN_THRESHOLD) {
      //Grab integrated gyro value from PROS library
      integ_gyro = gyroGet(gyro);
      
      //Speed is proportional to distance from target, so it stops without roll at the target
      lSpeed = (degrees-integ_gyro) * direction;
      rSpeed = lSpeed * -1;

      //If speed falls below certain values, motors will stall without movement, stop this
      if(abs(lSpeed) <=DRIVE_MIN_SPEED) lSpeed = DRIVE_MIN_SPEED * direction; 
      if(abs(rSpeed) <= DRIVE_MIN_SPEED) rSpeed = DRIVE_MIN_SPEED * direction;

      //Set motors accordingly 
      setMotor(_bl, lSpeed);
      setMotor(_br, rSpeed);
      setMotor(_fr, rSpeed);
      setMotor(_fl, lSpeed);
  }
  setAll(0);  //Disable motors
}

/*
* Debug
*/
void Drive::debug() {
  //printf("LEFT %d", );
  //printf("RIGHT %d", getHeight('r')-startLiftR);
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
  setMotor(_bl, joystickGetAnalog(1, 3));
  setMotor(_br, joystickGetAnalog(1, 2));
  setMotor(_fr, joystickGetAnalog(1, 2));
  setMotor(_fl, joystickGetAnalog(1, 3));
}
