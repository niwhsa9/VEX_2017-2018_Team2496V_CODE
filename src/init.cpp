#include "main.h"
#include "ports.h"
#include "robot.h"
#include "JINX.h"
bool isSubInit = false;
DR4B* lift;
Drive* drive;
Claw* claw;
MogoLift* mogolift;
Integrator* integrator;
int prevButtonEvent = millis();
char page = 0;
char numPages = 5;

void subsystemInit() {
  /* LIFT INITALIZATION */
  int liftMotors[10] = {M_LIFT_L, M_LIFT_R};
  int liftRev[10] = {1, -1};

  //while(1) printf("%d", liftRev[2]);
  int liftSensors[10] = {A_LIFT_POT};
  lift = new DR4B("", liftMotors, liftRev, 2, liftSensors, 0);
  lift->init();

  int driveMotors[10] = {M_DRIVE_FR, M_DRIVE_BR, M_DRIVE_FL, M_DRIVE_BL};
  int driveRev[10] = {-1, -1, -1, -1};
  int driveSensors[10] = {D_DRIVE_ENC_L1, D_DRIVE_ENC_L2, D_DRIVE_ENC_R1, D_DRIVE_ENC_R2, A_DRIVE_GYRO};
  drive = new Drive("", driveMotors, driveRev, 4, driveSensors, 1); //4 ports, 6 motors
  drive->init();

  int clawMotors[] = {M_CLAW};
  int clawRev[] = {1};
  int clawSensors[] = {};
  claw = new Claw("", clawMotors, clawRev, 1, clawSensors, 2);
  claw->init();

  int mogoMotors[10] = {M_MOGO_L, M_MOGO_R};
  int mogoRev[10] = {1, -1};
  int mogoSensors[10] = {};
  mogolift = new MogoLift("", mogoMotors, mogoRev, 2, mogoSensors, 2); //4 ports, 6 motors
  mogolift->init();

  int integMotors[10] = {M_INTEG};
  int integRev[10] = {1};
  int integSensors[10] = {A_INTEG_POT};
  integrator = new Integrator("", integMotors, integRev, 1, integSensors, 1); //4 ports, 6 motors
  integrator->init();

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
          sprintf(line2, "<|%s|>", autoModeStr[autoMode]);
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
  setTeamName("2496V");              //BHS Robopatty V :D
  initJINX(stdout);
  delay(100);
  taskCreate(JINXRun, TASK_DEFAULT_STACK_SIZE, NULL, (TASK_PRIORITY_DEFAULT));
  subsystemInit();                   //Initalize subsystems for autonomous
  lcdInit(uart2);                    //Initalize LCD display
  lcdSetBacklight(uart2, true);      //Enable the backlight to make text more visible
  lcdClear(uart2);                   //Clear any bargled text or weirdness
  updateLCD();
  while(!isEnabled()) {              //Routinely update LCD values and check for USER
                                     //input on the buttons while pre-auton is active
    checkInput();
    updateLCD();
  //  printf("page %d \n", page);
    delay(100);
  }
}
