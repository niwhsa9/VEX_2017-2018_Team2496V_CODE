#ifndef PORTS_H
#define PORTS_H
/* PORT MAP */
//I2C Device ID's
#define I2C_CLAW_ENC 0

//Digital sensors (1-12)
#define D_DRIVE_ENC_R1 1
#define D_DRIVE_ENC_R2 2
#define D_DRIVE_ENC_L1 3
#define D_DRIVE_ENC_L2 4

#define D_RIGHT_BUMP 6
#define D_LEFT_BUMP 7

#define D_LEFT_LIMIT 5
#define D_RIGHT_LIMIT 8

#define C_LIMIT 9

//analog sensors (1-10)
#define A_LIFT_POT_R 2
#define A_LIFT_POT_L 1
#define A_DRIVE_GYRO 3

//motor (1-10)

#define M_DRIVE_BL1 7
#define M_DRIVE_BR1 1
#define M_DRIVE_FL1 5
#define M_DRIVE_FR1 3
#define M_DRIVE_BL2 10
#define M_DRIVE_BR2 2
#define M_DRIVE_FL2 6
#define M_DRIVE_FR2 4

#define M_MOGO_L 9
#define M_MOGO_R 8


/* DRIVE DEFINES */
#define LIFT_MIN_L 7
#define LIFT_MIN_R 2707
#define LIFT_TARGET_THRESHOLD 10

#define DRIVE_TURN_THRESHOLD 1
#define DRIVE_MOVE_THRESHOLD 1
#define DRIVE_MIN_SPEED 14
#define TURN_MIN_SPEED 25
#define TURN_MIN_LOW_SPEED 18
#define PI 3.14159265358
#endif
