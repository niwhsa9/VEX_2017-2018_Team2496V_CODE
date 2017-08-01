## Auton Function Tests

Today is our first day back at routine practice. The objective of the day for code is to test
the autonomous "move" and "turn" functions in Drive class and callibrate them with the correct values so the robot's
autonomous motion is accurate. We are about to test the functions for the first time with some simple
code. We also quickly recognized that the LCD code was causing a crash, so we removed it for later
testing.

** Test **

  - 90 degree turn at 127 (slew)
  - 5 second wait
  - 12 inch forward movement at 127 speed (slew)

** Result (Trial 1): **
- No part of this worked. Our first debug step was to print out the _sensors[] elements being used
(gyroscope and encoders) to see if the elements are properly populated, since we had a similar
problem with the motors. It turned out, they weren't. This is odd behavior, because the values
are fine in DR4B (made apparent from PID working), which is also a child of Subsystem. We decided
to worry about this later, and move on with testing by
 just hardcoding these values as constants. Its not clean
but the _subsystem[] array isn't being used for anything in the super class (unlike _motor) so it dosen't break anything.

[code here]

** Result (Trial 2): **

- After this change, the functions "worked". The turn was nearly perfect (1-2 degrees off) but the
forward motion was off by a significant amount. We believe this to a simple problem:
even with the slew code, 12 inches isn't enough distance for the motors to start 127 max speed, then
slow down again to stop. We changed the test parameters slightly.

** Test (Revision) **

  ...
- 24 inch forward movement at 100 speed (slew)

** Result (Trial 3): **

- The move still didn't work at all. It was significantly off. We checked the code for problems, and
discovered that the variables used to calculate the speed needed based on position were actually
integers not floats. Obviously, calculations cannot be done very accurately with integers
(since decimal values are truncated) so we changed these. We will now try again.

** Result (Trial 4): **

- This seemed to have little effect. Upon printing the speed values calculated during the movement,
it became clear what the issue was: there was no constant involved in the control loop, and the
calculated values weren't scaled very appropriately to be motor speeds [0-127]. Since encoder value
ticks are usually in 100s, and max speed is also usually in 100s, values could be in the 10 ** 4
area. An example of this is shown below, by taking values at a specific moment in the forward motion.

[code example]

In this example, you can see how the old way of calculating speeds makes little sense.
We are adding a constant for this function so that it has more resasonable values. This will stop the
robot from rolling past the target (which happens at high speeds)

** Result (Trial 5): **

- move() is now much more accurate after a couple minutes of dialing in the constant. It
now usually only a few inches past target. We will work on this more later.

It was around this time we noticed a strange problem. The robot would seemingly randomly stop
responding to our joystick and get locked into whatever the last command was. (Such as running drive forward)
Even after power-cycling, changing keys, batteries, and joystick, the problem persisted. The Cortex
ROBOT light blinked a slow red. (Very ominous :( ). The VEXNET light blinked green, showing there
was still technically a connection with the joystick. We consulted our mentor for help, and he
helped us find the cortex user guide that contains information on light codes and their meanings.

https://drive.google.com/file/d/1TYjjR8QGzV4AbpMDkkVYoE-CGWIYwsfQQESiAmxMUcOISNy4i_9tH4cBP66v5qFLXgt4lsX1IIwZI0qE/view

These lights indicate a "Fault: User Microprocessor issue". Using this error, we did a google search
and found this VexForum post:

https://www.vexforum.com/index.php/25513-red-blinking-light-error/0

Where the poster had the exact same error. One suggestion was to try and disable the IME line, which
is highly susceptible to static shock, and often causes faults like this. We tried this, it didn't
work. We will keep brainstorming.

Through good luck, the very next thing we tried solved our issue. We removed the string pointers from the
code, thinking it may be a memory exception. This seems to be the case, as the problem stopped occuring.
However, it is still off concern to us as this may mean our programming is pushing the cortex too hard,
and is at the limit of available memory. It may require us to do some optimization soon such as freeing
unused memory or replacing integers with chars when possible (4 byte -> 1 byte).

[code here]

We spend the remaining time tuning constants and min speeds. We ended with a drive constant of 0.0008f; In addition, we added a feature to the
move function that runs the Robot at full speed until it reaches a certain percentage of the
target, only then activiating the proportional control. This allows it to reach the target faster.
This was discussed in entry 6.
