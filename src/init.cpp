#include "main.h"
#include "ports.h"
#include "robot.h"
bool isSubInit = false;
DR4B* lift;
Drive* drive;
Claw* claw;
char *prevText1, *prevText2;
int prevButtonEvent = millis();

void subsystemInit() {
  /* LIFT INITALIZATION */
  int liftMotors[10] = {M_LIFT_TR, M_LIFT_BR, M_LIFT_TL, M_LIFT_BL};
  int liftRev[10] = {-1, -1, 1, 1};

  //while(1) printf("%d", liftRev[2]);
  int liftSensors[10] = {A_LIFT_POT_L, A_LIFT_POT_R};
  lift = new DR4B("", liftMotors, liftRev, 4, liftSensors, 0);
  lift->init();

  //HERE DOWN BROKEN
  int driveMotors[10] = {M_DRIVE_FR, M_DRIVE_BR, M_DRIVE_FL, M_DRIVE_BL};
  int driveRev[10] = {-1, -1, 1, 1};
  int driveSensors[10] = {D_DRIVE_ENC_L1, D_DRIVE_ENC_L2, D_DRIVE_ENC_R1, D_DRIVE_ENC_R2, A_DRIVE_GYRO};
  drive = new Drive("", driveMotors, driveRev, 4, driveSensors, 1); //4 ports, 6 motors
  drive->init();

  int clawMotors[] = {M_CLAW};
  int clawRev[] = {1};
  int clawSensors[] = {I2C_CLAW_ENC};
  claw = new Claw("", clawMotors, clawRev, 1, clawSensors, 2);
  claw->init();
  isSubInit = true;
}


/* HANDLES USER INPUT THROUGH LCD */
void checkInput() {
  //middle button: recalibrate gyro
  //left or right: change auton
  int cT = millis();
  if(cT - prevButtonEvent >= 500) {
  if(lcdReadButtons(uart2) == 2) {
    lcdSetText(uart2, 1, "Calibrating Gyro");
    drive->callibrateGyro();
    lcdSetText(uart2, 1, "FINISHED!");
    delay(200);
  } else if (lcdReadButtons(uart2) == 1) autoMode--;
  else if (lcdReadButtons(uart2) == 4) autoMode++;
  else if (lcdReadButtons(uart2) == 7) printf("ALIVE AT %d", powerLevelMain());
  }  else return;
  prevButtonEvent = cT;
  autoMode = (autoMode < 0) ? 0 : autoMode;
  autoMode = (autoMode >= numAuto) ? numAuto : autoMode;
  return; //explicit for readibility
}
/* CLEARS/DISPLAYS VALUES */
void updateLCD() {
    /*
    gyro value (2), (1), IME claw (2), (1), Quad left (2), (1), Quad right(2), (1), Battery (3)
    [G][V][][C][V][][R][V][][L][V][][B][V][V][]
    [<][A][U][T][O][M][O][D][E][>][][][][][][]
    */
    char *line1, *line2;
    int cw;
    //uchar a = (uchar)claw->_sensors[0];
    imeGet(0, &cw);
    sprintf(
      line1, "G%d1.0 C%d1.0 L%d1.0 R%d1.0 B%d1.4", gyroGet(drive->gyro),
      cw, encoderGet(drive->le), encoderGet(drive->re), powerLevelMain()
    );
    sprintf(line2, "<%s>", autoModeStr[autoMode]);
    lcdSetText(uart2, 1, line1);
    lcdSetText(uart2, 2, line2);
}


 extern "C" {
    void __libc_init_array();
} //MAKE EXTERN C ENCOMPASS ENTIRE THING
void initializeIO() {
    //watchdogInit();
    __libc_init_array();
}



void initialize() {
  //printf("starting");

  setTeamName("2496V"); //BHS Robopatty V
  //imeInitializeAll(); //REMOVE ME
  subsystemInit();
/*
  lcdInit(uart2);
  lcdSetBacklight(uart2, true);
  lcdClear(uart2);
  updateLCD();
  while(!isEnabled()) {
    checkInput();
    updateLCD();
    delay(20);
  } */
}
