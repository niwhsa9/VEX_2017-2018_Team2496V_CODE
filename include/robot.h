#include "drive.h"
#include "dr4b.h"
#include "claw.h"
#include "mogolift.h"

#ifndef ROBOT_H
#define ROBOT_H

extern Drive *drive;
extern DR4B *lift;
extern Claw *claw;
extern MogoLift *mogolift;
/* Subsystem defines */
extern bool isSubInit;
void subsystemInit();

/* AUTON  */
extern int autoMode;
extern const char *autoModeStr[];
extern int numAuto;


#endif
