#include "drive.h"
#include "mogolift.h"

#ifndef ROBOT_H
#define ROBOT_H

extern Drive *drive;
extern MogoLift *mogolift;
/* Subsystem defines */
extern bool isSubInit;
void subsystemInit();

/* AUTON  */
extern int autoMode;
extern const char *autoModeStr[];
extern int numAuto;

#endif
