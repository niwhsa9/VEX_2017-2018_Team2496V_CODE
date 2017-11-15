** Background ** 

With our new 8 motor drive train, it became immediately obvious that our old proportional + min speed system for gyro based turns 
(shown on section ) is no longer effective. We will use a full PID control loop to accomplish these turns. This
should make our turns more accurate and faster. This loop is a library function that should be used for ALL future robots without 
much modification. 

** A VERY Simple PID theory (in our words) **
Please note: we are not graduate electrical engineers, so our knowledge of PID and control theory as a subject is extremely limited 
and the concepts explained below are to the best of our understanding. They are simplified and in our words, but may not properly convey 
the full scope of the subject. Most of us have not even taken Calculus yet and thus the math is explained in terms of engineering/real world application but much of the important theory is lost in this explanation. 

PID, an acronym for Proportional, Integral, Derrative, is an important control loop that has many real world applications such as keeping airplanes straight, movements on robots, cruise control in cars, and temperature control in a 3d printer's bed. The purpose of a control loop is to obtain consistent and accurate output despite variables in enviornment such as voltage levels or obstructions such as friction. It combines the outpu tof three different controlers with an assigned importance on each (in the form of a constant) and produces a cumulative output. 

The loop is run at high speed to control some sort of "plant", which is the is a process that takes input to produce some output based on the input. The plant is monitored by some sort of feedback device. The controller takes in an input of "error" on each iteration. This error is equal to the value of the feedback device subtracted from the desired value of the plant (desired - actual). Error is than used differently in each controller to produce output settings that will be summed then applied to the plant in effort to reduce error. Each controller also has an associated constant which changes its weight in the final output as well as help scale the output appropriately to actually apply input within the range of the plant's acceptable inputs. This is shown in the following diagram:

https://oscarliang.com/ctt/uploads/2013/10/PID-three-algorithms.jpg

Each controllers effects are explained below given the input of "error":
Proportional - This one is exactly what it sounds like. It produces an output value proportional to the error. More error: applies more output. Less error: applies less output. This is the bulk of the controller and does 80% of the job. Proportional can get you close to the target, but close sometimes won't cut it. 

Integral - Integral in mathematics is simply explained as the area under a curve. For error, this means that integral is the sum of error over time (sumError += curError). This is useful encompasses a total behavior over time of the plant compared to immediate error like proportional. Integral can be used to filter out anomallies in data and also to provide the ability to overcome small error (by building up) that the proportional cannot handle. 

Derivative - Derivative in mathematics is simply explained as the instantaenous rate of change. This can be obtained from subtracting  Derrivitive is very useful for preventing large build up and overshooting the target from the P and I components. Derravitive is able to monitor the change being applied and essentially predict the plant response in order to reduce the change so the plant does not over compensate. It is worth noting that instantaneous ROC in a microprocessor is limited by the speed that it can iterate the loop. 

These three controllers compliment each other perfectly, making up for the weakpoints of one another. When combined correctly, the outcome is a very accurate control that gets even closer to desired values as time progresses. This is shown below. 

https://upload.wikimedia.org/wikipedia/commons/thumb/a/a3/PID_varyingP.jpg/320px-PID_varyingP.jpg

It starts off very innacuratly as the P overshoots and the I and D do not have enough data to be relevant as the control is still starting. Howevr, the I quickly starts to dial it in and the D dampens the osccilations. 

** PID in VEX ** 
We use a pid because turning (among other things) is a complex problem in VEX due to the the fact that resistance from the friction stalls motors at low speeds that a proportional alone would produce. 

In our case, the following explain our application of PID:
The plant - is the robot's drivetrain that takes an input of speed and outputs robot movement 
The feedback device - is the gyroscope IMU sensor to measure angle.
The desired value - is the angle we want the robot to turn 
The actual value - is the gyroscopes reading as an angle in degrees

The constants must help scale so that outputs match motor speeds -127, 127 and also give appropriate emphasis on each componenet

There are four primary factors that we need to adjust. 
  1. Proportional Constant kP
  2. Integral Constant kI
  3. Derrivative Constant kD
  4. Max integral limit
  
The goal is to accomplish as much as possible with P and then quickly finish off the turn with input from I and D. The max integral limit specifies how much integral data to store (
 

** Things to keep in mind ** 
- Because all four constants effect each other, they must be balanced accordingly and one change WILL effect others.
- We were sure to test the PID on multiple battery levels and 45*, 90*, and 180* turns to ensure accuracy and repeatability
in all situations. 
- Control loop programming requires a programmer to be mindful of real world implications. The most obvious example
is the motor speed bottom limits discussed in "PID in VEX"

** Our Code **
The code for this loop is shown and commented below:

** Constant Selection and Adjusting ** 

 The process of adjusting these constants was far too long (having gone through HUNDREDS of iterations) too completely recall exact
 values for documentation. However, the relevant proccess and our strategy for constant tuning is explained below. 
0. Set all gains to 0. Set desired turn value to 90*. Choose an integral limit that is fairly reasonable based on the problem. For the case of turning, the integral is most needed near the end of the turn for hitting the exact value after an overshoot from proportionality. We do NOT need integral during the initial movements otherwise the overshot will be ridculous. Because of this, it is best to have a lower integral limit (around 1/2 a second with cortex running at 100 hertz means a limit of 100). 
1. Increase P so that the turn slightly overshoots the target (5-10*) and then stops, but cannot return due to P output being too low
for motors 
2. Now add the I term in order to help bring the robot back to the target after over shooting. This does make it overshoot more
(due to error accumlating during the reaching target phase of the turn) but then helps bring the robot to the intended value. This 
causes the robot to oscilate back and forth around the target tremndously for a few seconds. If it oscilates for more then a few seconds, decrease. If it does not reach the desired value and stops oscilating, increase. 
3. The integral oscilations are helpful for reaching the target, but not so nice because they eat up valuable time and tend to shake the robot which is bad for the motors (rapid direction change), causes gyroscope drift to accumulate, and makes the robot drift horizontally
if on omni-directional wheels. This can be fixed with derrivative which serves as a dampener. Add in the D term. 
4. Increase D such that the robot applies "breaks" as it nears the target and slows tremndously. If the robot stops in the middle of the turn. Decrease D because stopping probably means the D has become too high and is counteracting the proportionality too strongly. If the robot is still oscilating at the integral, increase D. 
5. Continue to modify D so that integral oscilations do not exceed 1-3 and the robot still is within 1-2 degrees of the target. If the robot is not quite reaching the target with an increased D, consider increasing P. If the oscilations are overwhelming and are not being brought down, decrease I (very slightly). 
6. Once accuracy and repeatiblity have been achieved. Switch desired value.  Repeat steps 4 and 5 until turns on 45, 90, and 180 are all
excellent. 



** Future Improvements **
We implemented the same system for our linear movement (to replace move()) and we came to an important realization:

The PID source code is practically identical for turning, driving, and lift height alike. The only changes will be the four constants 
discussed above. Because of the need for PID on so many sub systems and its reusability, the code really should not be a function of
a child class, but rather another parent class or functionality of Subsystem itself. We will most likely create a genralized pid() function in the
super class Subsystem for clean code and reusablity. This will contain initalization paramters such as constants, integral limit, and
feedback device (for scaling). Its primary function will receive the error (target-actual) and then output a value based on the PID. 

In addition, more accurate methods for numerical integration exist than the one we currently have limited by cortex sample rate. We will most likely attempt an implementation of trapezoid rule as an upgrade to the PID library. 

Another cool feature to add to the Subsystem base class would be the ability to output data from the cortex to our development laptop using JINX (a PROS tool). This could let us take PID tests and graph the data in excel to show us how each term helped correct to the target and the overall actual position compared to the target. 

Yikes that was a long log. Fingers are bleeding. Control theory is super cool black magic ;) 
