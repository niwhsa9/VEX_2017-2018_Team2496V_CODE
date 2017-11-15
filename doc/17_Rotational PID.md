** Background ** 

With our new 8 motor drive train, it became immediately obvious that our old proportional + min speed system for gyro based turns 
(shown on section ) is no longer effective. We will use a full PID control loop to accomplish these turns. This
should make our turns more accurate and faster. This loop is a library function that should be used for ALL future robots without 
much modification. 

** PID theory **

** PID in VEX ** 



There are four primary factors that we need to adjust. 
  1. Proportional Constant kP
  2. Integral Constant kI
  3. Derrivative Constant kD
  4. Max integral range max_integ 
 

** Things to keep in mind ** 
- Because all four constants effect each other, they must be balanced accordingly and one change WILL effect others.
- We were sure to test the PID on multiple battery levels and 45*, 90*, and 180* turns to ensure accuracy and repeatability
in all situations. 
- Control loop programming requires a programmer to be mindful of real world implications. The most obvious example
is the motor speed bottom limits discussed in "PID in VEX"

** Our Code **
The code for this loop is shown and commented below:

** Constant adjusting ** 

 The process of adjusting these constants was far too long (having gone through HUNDREDS of iterations) too completely recall for 
 documentation. However, the relevant proccess and our strategy for constant tuning is explained below. 
0. Set all gains to 0 
1. Increase P so that the 



//integral totally different based on the max range because 



** Future Improvements **
We implemented the same system for our linear movement (to replace move()) and we came to an important realization:

The PID source code is practically identical for turning, driving, and lift height alike. The only changes will be the four constants 
discussed above. Because of the need for PID on so many sub systems and its reusability, the code really should not be a function of
a child class, but rather another parent class or functionality of Subsystem itself. We will most likely create a pid() function in the
super class Subsystem for clean code and reusablity. 

In addition, more accurate methods for numerical integration exist than the one we currently have limited by cortex sample rate. We will most like
attempt an implementation of trapezoid rule as an upgrade to the PID library. 
