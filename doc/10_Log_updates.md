## Started Autonomous

We started working on autonomous (routes and trials are detailed in primary notebook) and made some code changes after tests. The following are some quick updates

- A f_move() function was added (short for full speed move). This is practically identical to the move() function but without the proportional speeds. Instead, it goes full speed all the way to target, and executes a break by spinning wheels the opposite direction for a short burst.

- During all autonomous programs (we plan on having multiple) the lift will have its own thread as well as the claw. This will allow for synchronous operation of subsystem and drive, allowing us to do more in autonomous. This means auton will take 3 threads in most cases, unless no claw operation is needed.

- A lift unpack thread (to unfold our mobile goal intake) is also necessary at the start of most autonomous, but can be deleted once the operation is complete and replaced with lift thread.

- Deleting ANY threads during autonomous seems to abruptly cancel autonomous action, the reason for this is unknown

- We noticed a bug where after autonomous runs to completion, it restarts after a short delay

- When working with the LCD, pointer strings were causing crashing. We are observing a pattern ;).  


The following are the actual autonomous programs we wrote. The routes and other information are documented more in our primary notebook. Those are beyond the scope of this notebook. While very robot specific, these are included since they are raw code. They aren't commented because all components have been commented in the past, and the function calls are fairly implicit. Remember, move(inches, speed, direction) and turn(degrees, speed, direction)

** Backup autonomous (mobile goal in 10 point)**


** Primary autonomous (mobile goal in 20 point) **
