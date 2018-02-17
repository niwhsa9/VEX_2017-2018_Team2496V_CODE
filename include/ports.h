#ifndef PORTS_H
#define PORTS_H
/* PORT MAP */
//I2C Device ID's

//Digital sensors (1-12)
#define D_DRIVE_ENC_R1 2
#define D_DRIVE_ENC_R2 3
#define D_DRIVE_ENC_L1 11
#define D_DRIVE_ENC_L2 12

//analog sensors (1-10)
#define A_DRIVE_GYRO 5
#define A_LIFT_POT 3
#define A_INTEG_POT 4
//motor (1-10)
#define M_LIFT_R 8
#define M_LIFT_L 3
#define M_DRIVE_BL 9
#define M_DRIVE_BR 2
#define M_DRIVE_FL 6
#define M_DRIVE_FR 5
#define M_CLAW 4
#define M_MOGO_L 10
#define M_MOGO_R 1
#define M_INTEG 7



/* DRIVE DEFINES */
#define DR4B_START 2520
#define LOADER_PRESET 425
#define INTEG_TOP 3000
#define INTEG_BOT 890
#define INTEG_GO 300

extern int stackHeight;
extern int stage;
extern int dCmd;
extern int sCmd;
extern int offset;
extern int manualLock;
extern int firstCone;
void clawSet(int des);

#define DRIVE_TURN_THRESHOLD 2
#define DRIVE_MOVE_THRESHOLD 2
#define DRIVE_MIN_SPEED 35
#define TURN_MIN_SPEED 32
#define PI 3.14159265358
#endif
//7L
