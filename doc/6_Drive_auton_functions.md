## Drive Autonomous Functions

[Code here]
[Code Here]

While driving to a specified distance and turning a certain amount may not seem this way, they are actually very similar tasks. The code is almost identical, with two exceptions.
1. Different feedback device, gyro for turn, encoders for moved
2. The parameter for move() is in a different unit then the feedback. Distance in inches must be converted into encoder ticks.

They are similar because they both use the concept of a "slew". This is where the robot moves, but as it nears the target it applies less and less speed. This allows it to come to a gentle stop, without rolling past the target. This is preferable over a sudden break, which could alter the robots orientation or position. A slew is very similar to a proportional loop, but just doesn't have a constant involved.

This code may require a future change, where the robot doesn't start the slew until its reached some percentage of its final destination. This will help so that it still reaches the destination quickly, but stops at the end. We will test this to find out.
