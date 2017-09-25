We started reformatting the code for V2. The V1 src and include directories in their 
state as of 9/8/2017 have been moved into the archive directory. As such, the 
following directory structure is in use: 

- src
- include 
- archive

We then went on to delete DR4B.h, DR4B.cpp, Claw.h, Claw.cpp, and any other references
in these in the code. We modified Drive.h and Drive.cpp to account for the 8 motor changes,
these are shown below:

[code here]

We also added a MogoLift child class of Subsystem. For the time being, this isn't shown 
since the PID hasn't been added. It will likely be a similar PID code to the DR4B, but
we'll actually have the integral component this time (emoji) 
