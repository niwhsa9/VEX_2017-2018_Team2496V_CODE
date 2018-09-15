#include "drive.h"
#include "dr4b.h"
#include "claw.h"
#include "mogolift.h"
#include "integrator.h"

#ifndef ROBOT_H
#define ROBOT_H

extern Drive *drive;
extern DR4B *lift;
extern Claw *claw;
extern MogoLift *mogolift;
extern Integrator *integrator;
/* Subsystem defines */
extern bool isSubInit;

void subsystemInit();

extern TaskHandle lftTsk;

/* AUTON  */
extern int autoMode;
extern const char *autoModeStr[];
extern int numAuto;


#endif
