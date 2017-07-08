#ifndef PORTS_H
#define PORTS_H
/* PORT MAP */
//Digital sensors (1-12)
#define D_DRIVE_ENC_R1 2
#define D_DRIVE_ENC_R2 3
#define D_DRIVE_ENC_L1 5
#define D_DRIVE_ENC_L2 6

//analog sensors (1-10)
#define A_LIFT_POT_R 3
#define A_LIFT_POT_L 2
#define A_DRIVE_GYRO 1

//motor (1-10)
#define M_LIFT_TR 7
#define M_LIFT_TL 4
#define M_LIFT_BR 8
#define M_LIFT_BL 3
#define M_DRIVE_BL 2
#define M_DRIVE_BR 9
#define M_DRIVE_FL 1
#define M_DRIVE_FR 10
#define M_CLAW 6

/* DR4B DEFINES */
#define A_UNPLUG 0
#define LOADER_PRESET 418
#define DR4B_THRESHOLD 5
#define DR4B_MAX 1395
#define DR4B_START_L 1275
#define DR4B_START_R 1302

/* DRIVE DEFINES */
#define DRIVE_TURN_THRESHOLD 2
#define DRIVE_MOVE_THRESHOLD 2
#define DRIVE_MIN_SPEED 15
#define PI 3.14159265358
#endif
