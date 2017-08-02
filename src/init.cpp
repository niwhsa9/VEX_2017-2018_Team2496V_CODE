#include "main.h"
#include "ports.h"
#include "robot.h"
bool isSubInit = false;
DR4B* lift;
Drive* drive;
Claw* claw;
int prevButtonEvent = millis();
char page = 0;
char numPages = 5;

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
  if(cT - prevButtonEvent >= 300) {
    if (lcdReadButtons(uart2) == 1) page--;
    else if (lcdReadButtons(uart2) == 4) page++;
    else if (lcdReadButtons(uart2) == 7) printf("ALIVE AT %d", powerLevelMain());
    page = (page < 0) ? 0 : page;
    page = (page >= numPages) ? numPages-1 : page;

    if(page == 1 && lcdReadButtons(uart2) == 2) {
      lcdSetText(uart2, 1, "Calibrating Gyro");
      drive->callibrateGyro();
      lcdSetText(uart2, 1, "FINISHED!");
      delay(500);
    }
    if(page == 4) {
      if (lcdReadButtons(uart2) == 3) autoMode--;
      else if (lcdReadButtons(uart2) == 6) autoMode++;
      autoMode = (autoMode < 0) ? 0 : autoMode;
      autoMode = (autoMode >= numAuto) ? numAuto : autoMode;
    }
    prevButtonEvent = cT;
  }


  return; //explicit for readibility
}
/* CLEARS/DISPLAYS VALUES */
void updateLCD() {

    char line1[16];
    char line2[16];

    switch(page) {
        case 0:
          sprintf(line1, "< Battery >");
          sprintf(line2, "%fV", (float)powerLevelMain()/1000);
          break;
        case 1:
          sprintf(line1, "< Gyroscope >");
          sprintf(line2, "%d", gyroGet(drive->gyro));
          break;
        case 2:
          sprintf(line1, "< L Encoder >");
          sprintf(line2, "%d ", encoderGet(drive->le));
          break;
        case 3:
          sprintf(line1, "< R Encoder >");
          sprintf(line2, "%d ", encoderGet(drive->re));
          break;
        case 4:
          sprintf(line1, "< Auto Mode >");
          sprintf(line2, "<| %s |>", autoModeStr[autoMode]);
          break;
        default:
          sprintf(line1, "BROKEN");
          sprintf(line2, "BROKEN");
          break;
    };

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

  lcdInit(uart2);
  lcdSetBacklight(uart2, true);
  lcdClear(uart2);
  //lcdSetText(uart2, 1, "test");

  updateLCD();
  while(!isEnabled()) {
    //printf("%d \n", page);
    checkInput();
    updateLCD();
    delay(100);
  }
}
