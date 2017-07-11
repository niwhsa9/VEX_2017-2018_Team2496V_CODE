#include "dr4b.h"
#include "drive.h"
#include "claw.h"

#ifndef ROBOT_H
#define ROBOT_H

extern DR4B *lift;
extern Drive *drive;
extern Claw *claw;
/* Subsystem defines */
extern bool isSubInit;
void subsystemInit();

/* AUTON  */
extern int autoMode;
extern const char *autoModeStr[];
extern int numAuto;

#endif
