#include "main.h"
#include "ports.h"
#include "robot.h"

int autoMode = 1; //0
const char *autoModeStr[] = {
  "10 POINT L", "10 POINT R", "20 POINT L", "20 POINT R"
};
int numAuto = 4;
TaskHandle lftTsk;

  void liftCtl(void *) {
    while(1) {
      lift->moveTo();
      delay(10);
    }
  }



void autonomous() {

}
