Note: We have finally decided on a four bar mobile goal system (please see primary notebook).

The following diagrams and photos show the sensor layout on our robot:
(circle sensors in picture)
(create pptx )

These sensors are detailed below:

** Drive **
2x Quad encoders 
- Autonomous position PID
- Drive train synchronization
- See section 6

2x Bump switches
- Used to bump robot into the fence during skills
and ensure that it is realligned for the next manuever 

** Gyroscope **
- Rotational position PID 
- See section 6 and 16

** Mogo 4 Bar Lift ** 

2x Limit switches
-Used to detect when mobile goal lift is in top position 
[code]

2x potentiometer 
- Used along with PHYSICAL stops to determine if lift has 
reached (or nearly reached) bottom position 
[code]



** LCD ** 
- Please see prior entry on LCD in section