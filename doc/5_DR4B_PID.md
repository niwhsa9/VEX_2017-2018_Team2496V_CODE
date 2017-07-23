## DR4B PID

[CODE HERE]

A control loop like this accomplishes a number of things:
1. Keeps both sides of the lift (which are seperate gear towers) synced
2. Helps hold the lift at the desired position no matter how much weight is added. This is useful so the heavy mobile goal dosen't require the operator to constantly adjust the lift higher
3. Prevents motors from burning out unlike "hold buttons"
4. Gives great accuracy during autonomous (and precision)

For autonomous, a similar function is used. The joystick input is removed and the desired value is manually set through a seperate function, NOT passed as a parameter. The function is to be started on its own thread for autonomous. This is done because the control must continue to operate even when the lift reaches the target for the described reasons above.
