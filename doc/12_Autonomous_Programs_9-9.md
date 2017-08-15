## Autonomous Programs 9-9 Regional

We wrote earlier that we wouldn't have any specific autonomous information other then the code in this notebook. However, we changed our minds. The information is rather spread in our primary log, and we want some of the most important stuff (code, map, duration, stats, etc.) in one place. Here is the documentation for all of our autons for our first regional.

** 20 Point Mobile Goal**

- Valid Start Pos: Red (left, right) Blue (left, right)
- Runtime: 11.2 seconds on avg battery
- Directions:
 1. Unpack mobile goal intake by moving the lift up and down
 2. Move 48 inches at full speed back to the mobile goal
 3. Lift up 33%
 4. Move 44 inches back to the start position (but avoid hitting the bar)
 5. Turn 135 degrees right
 6. Move 20 inches backward
 7. Turn 45 degrees to the right
 8. Move another 6 inches backward
 9. Turn 37 degrees to the right
 10. Move (at full power) back 15 inches
 11. Lift down 0%
 12. Move (at full power) forward 20 inches
- Map:
- Preload: ignored, placed in such a way that it is discarded
- Success Rate: ~90% with 30 trials
- Total points: 20
- Notes: Failures often resulted in scoring in the 10 point zone. This is still a good outcome for us.

** Stationary Goal **
  - Valid Start Pos: Blue(left), Red (right)
  - Runtime: 4 seconds (to score) on avg battery
  - Directions:

  - Map:
  - Preload: used to score on stationary
  - Success rate: 60% with 5 trials
  - Total points: 2 min, 7 max (highest stack)
  - Notes: Not enough trials, success rate can probably be raised. Also, it will probably work in all 4 start pos.


** 10 Point mobile goal **

- Valid Start Pos: Blue (left), Red (Right)
- Runtime: 10 seconds on avg battery
- Directions:
- Map:
- Preload: ignored, placed in such a way that its discarded
Success Rate: 95%+ with dozens of trials
Total points: 10
Notes: won't work on side with loader because it hits the loader. 
