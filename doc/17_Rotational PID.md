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

 The process of adjusting these constants was far too long (having gone through HUNDREDS of iterations) too completely recall exact
 values for documentation. However, the relevant proccess and our strategy for constant tuning is explained below. 
0. Set all gains to 0. Set desired turn value to 90*.
1. Increase P so that the turn slightly overshoots the target (5-10*) and then stops, but cannot return due to P output being too low
for motors 
2. Now add the I term in order to help bring the robot back to the target after over shooting. This does make it overshoot more
(due to error accumlating during the reaching target phase of the turn) but then helps bring the robot to the intended value. This 
causes the robot to oscilate back and forth around the target tremndously for a few seconds. If it oscilates for more then a few seconds, decrease. If it does not reach the desired value and stops oscilating, increase. 
3. The integral oscilations are helpful for reaching the target, but not so nice because they eat up valuable time and tend to shake the robot which is bad for the motors (rapid direction change), causes gyroscope drift to accumulate, and makes the robot drift horizontally
if on omni-directional wheels. This can be fixed with derrivative which serves as a dampener. Add in the D term. 
4. Increase D such that the robot applies "breaks" as it nears the target and slows tremndously. If the robot stops in the middle of the turn. Decrease D because stopping probably means the D has become too high and is counteracting the proportionality too strongly. If the robot is still oscilating at the integral, increase D. 
5. Continue to modify D so that integral oscilations do not exceed 1-3 and the robot still is within 1-2 degrees of the target. If the robot is not quite reaching the target with an increased D, consider increasing P. 


//integral totally different based on the max range because 



** Future Improvements **
We implemented the same system for our linear movement (to replace move()) and we came to an important realization:

The PID source code is practically identical for turning, driving, and lift height alike. The only changes will be the four constants 
discussed above. Because of the need for PID on so many sub systems and its reusability, the code really should not be a function of
a child class, but rather another parent class or functionality of Subsystem itself. We will most likely create a pid() function in the
super class Subsystem for clean code and reusablity. 

In addition, more accurate methods for numerical integration exist than the one we currently have limited by cortex sample rate. We will most likely attempt an implementation of trapezoid rule as an upgrade to the PID library. 

Yikes that was a long log. Fingers are bleeding. Control theory is super cool black magic ;) 
