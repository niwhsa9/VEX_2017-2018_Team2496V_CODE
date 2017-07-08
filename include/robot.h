#include "dr4b.h"
#include "drive.h"

#ifndef ROBOT_H
#define ROBOT_H

extern DR4B *lift;
extern Drive *drive;
/* Subsystem defines */
extern bool isSubInit;
void subsystemInit();

#endif
