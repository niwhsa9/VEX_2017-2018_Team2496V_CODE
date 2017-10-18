## Log Failsafe: Max Time

A quick log today, but important. We ocasionally
expierence unexplainable behavior during autonomous
where drive move operations continue without stopping.
This probably has to do with the encoders not reading correctly.
When our coach observed this, he suggested that we
add a fallback failsafe to our move function: a max
time. The function will now move until it hits the target,
OR exceeds the max time allocated for its execution.
This can keep autonomous running and prevent crashes
from sensor failure or other problems.
