#ifndef PORTS_H
#define PORTS_H
/* PORT MAP */
//I2C Device ID's

//Digital sensors (1-12)
#define D_DRIVE_ENC_R1 0
#define D_DRIVE_ENC_R2 0
#define D_DRIVE_ENC_L1 0
#define D_DRIVE_ENC_L2 0
#define D_LIFT_ENC_R1 0
#define D_LIFT_ENC_R2 0
#define D_LIFT_ENC_L1 0
#define D_LIFT_ENC_L2 0


//analog sensors (1-10)
#define A_DRIVE_GYRO 1

//motor (1-10)
#define M_LIFT_R 0
#define M_LIFT_L 0
#define M_DRIVE_BL 0
#define M_DRIVE_BR 0
#define M_DRIVE_FL 0
#define M_DRIVE_FR 0
#define M_CLAW 0
#define M_MOGO_L 0
#define M_MOGO_R 0
#define M_INTEG 0




/* DRIVE DEFINES */
#define DRIVE_TURN_THRESHOLD 2
#define DRIVE_MOVE_THRESHOLD 2
#define DRIVE_MIN_SPEED 35
#define TURN_MIN_SPEED 32
#define PI 3.14159265358
#endif
//7L
