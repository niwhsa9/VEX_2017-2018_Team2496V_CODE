## TEAM 2496V BHS Robopatty Code Breakdown
While the specific files will change over time as our robot changes, this shows the general structure and the current state. All code is centered around "Subsystem", an abstract class that defines the basic behaviors shared by all subsystems on the robot: drive, lift, claw, etc. It gives generic properties for control and organization. This structure is inspired by FIRST robotics' "Command Based Programming" model. This basic organization shouldn't change much for the remainder of the year, but will be update as needed.

**Headers (.h)**
- *ports.h*
  - User defined equivalent of main.h, which isn't modified in the interest of seperating PROS code from user code
  - contains #define macros cortex port mapping
  - contains subsystem #define macros for various constants and such
- *subsystem.h*
  - Abstract base class containing mostly pure virtual functions that defines a basic motor system functionality for all motor systems to inherit from
- *main.h*
  - PROS predefined header with inclusion of the API and references to opcontrol(), auto(), and initalize() functions
- *api.h*
  - PROS predefined header with the library
- *robot.h*
  - contains references to subsystem instances initialized in init.cpp

**Headers (.h) + Source (.cpp)**
  - *DR4B.h + DR4B.cpp*
    - Contains lift subsystem child
    - Controls lift motors through P(ID) loop for auto and driver control
  - *Drive.h + Drive.cpp*
    - Contains tank drive drivetrain subsystem child
    - Controls drive motors (? with encoder master/slave ?) in driver control
    - Turn/drive distance functionalities for auto
  - *Claw.h + Claw.cpp*
    - Controls claw subsystem child with functionality for auto set position and driver operation and hold

**Source (.cpp/.c)**
  - *init.c*
    - Contains pregame code for LCD display & sensor debug including gyro and drive encoders
    - Gyro calibration
    - Subsystem initialization
    - Stops initialization thread for auto or opcontrol
  - *auto.c*
    - Autonomous code, handles autonomous thread creation/management
    - Autonomous failsafe thread
    - Stops autonomous threads for opcontrol
  - *opcontrol.cpp*
    - Driver control code, handles driver thread
    - Driver failsafe thread
    - Stops driver threads and deallocate waste memory
