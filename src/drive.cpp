#include "drive.h"
const float Drive::zK= 0.2f;
const float Drive::tK = 0.05f;

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
* Move robot specified distance and direction through
* encoder count (SLEW)
*/
void Drive::move(float distance, int speed, int direction) { //change position to percentage?
  encoderReset(le);
  encoderReset(re);
  int v_le = 0;
  int v_re = 0;
  int lSpeed = 0;
  int rSpeed = 0;
  //distance/circumfrence = revolutions needed
  //360 ticks per revolution * revolutions needed = ticks needed
  float ticks = (distance/(4*PI)) *  360;
  while(abs(ticks-v_le) >= DRIVE_MOVE_THRESHOLD && abs(ticks-v_re) >= DRIVE_MOVE_THRESHOLD) {
      v_le = abs(encoderGet(le));
      v_re = abs(encoderGet(re));
      lSpeed = (ticks-v_le) * speed * direction;
      rSpeed = (ticks-v_re) * speed * direction;
      if(abs(lSpeed) <= DRIVE_MIN_SPEED) lSpeed = DRIVE_MIN_SPEED * direction;
      if(abs(rSpeed) <= DRIVE_MIN_SPEED) rSpeed = DRIVE_MIN_SPEED * direction;

      setMotor(_bl, lSpeed);
      setMotor(_br, rSpeed);
      setMotor(_fr, rSpeed);
      setMotor(_fl, lSpeed);
  }
  setAll(0);
}

/*
* Ensure that both feedback potentiometers
* are functional
*/
void Drive::turn(char direction, float degrees) {
  gyroReset(gyro);
  int lSpeed = 0;
  int rSpeed = 0;
  int integ_gyro = 0;

  while(abs(integ_gyro - degrees) > DRIVE_TURN_THRESHOLD) {
      integ_gyro = gyroGet(gyro);
      lSpeed = (degrees-integ_gyro) * direction;
      rSpeed = lSpeed * -1;
      if(abs(lSpeed) <=DRIVE_MIN_SPEED) lSpeed = DRIVE_MIN_SPEED * direction; //NOT OPTIMIZED
      if(abs(rSpeed) <= DRIVE_MIN_SPEED) rSpeed = DRIVE_MIN_SPEED * direction;

      setMotor(_bl, lSpeed);
      setMotor(_br, rSpeed);
      setMotor(_fr, rSpeed);
      setMotor(_fl, lSpeed);
  }
  setAll(0);
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
