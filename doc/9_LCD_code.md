## LCD Code

One important tool we have on our robot is the LCD screen. The screen is written to via the UART
bus, but this serial communication is for the most part handled by the PROS library.

We originally planned on having a single screen display all the data we needed, but
this turned out to be cluttered.
Now we use a "pages" type display for our LCD that uses software selectable panels as the active
display to free up space.
The left and right button on the screen are used to switch
pages. Each page contains different information, critical for debugging problems with our robot.

The LCD allows us to check that all sensors read, robot is ready to go, and the correct settings are
chosen before a match.

We have the following pages for the pre autonomous mode:

1. Battery
  - See main battery power in volts
2. Gyroscope
  - See gyroscope value
  - Calibrate gyro with center button
3. L Encoder
  - See left encoder value
4. R Encoder
  - See right encoder value
5. Auto Mode
  - See active autonomous
  - Change active autonomous using center + (left or right).


With gyros and encoders, we get quick feedback before a match. This lets us find problems like
unplugged devices the easy way, preventing autonomous failure.

In driver control, the LCD light is turned off to decrease current (amp) usage and the LCD displays the
battery level, updated infrequently (every 20s). While not particularly useful information
during the match, immediately after a match or back at the pit this helps us keep track
of batteries that need to be switched without a voltmeter.

[diagrams here]

[code here]
