/*
	CODE STRUCTURE
	  DR4B.h + DR4B.cpp
    Drive.h + Drive.cpp
    opcontrol.cpp
      - Teleop controlset, driver thread management
    subsystem.h + subsystem.cpp
    ports.h
    init.c
    main.h
    API.h
    Makefile
*/


#define A_LIFT_POT_R 3
#define A_LIFT_POT_L 2

#define M_LIFT_TR 7
#define M_LIFT_BR 8
#define M_LIFT_TL 4
#define M_LIFT_BL 3

#define M_DRIVE_BL 2
#define M_DRIVE_BR 9
#define M_DRIVE_FL 1
#define M_DRIVE_FR 10

#define M_CLAW 6


#define A_UNPLUG 0
#define LOADER_PRESET 418
#define DR4B_THRESHOLD 5
#define DR4B_MAX 1395
#define DR4B_START_L 1275
#define DR4B_START_R 1302
