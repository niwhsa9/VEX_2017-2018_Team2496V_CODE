

In the past we have always done linear drive functions on each stick. This means that stick values
directly mapped to motor output speeds. Each stick followed the linear function 
y = x, as graphed below on the interval [-127, 127]. This is a fairly average control set. 

[Graph]

However, our driver was having difficulty at competition with precise manuevers (+-1 inch) involving cone 
placement on stationary goal, and desired a more fine tuned drive control. In order to achieve this, we
expieremented with two different ideas. Both were based on the concept of the joystick putting in less power 
over a wider range of motion, thus giving more fine control. 

[illustration]

However, the joystick should still allow for motors to achieve max power and other signifigant power levlels. 
All of these functions must be on the interval [-127, 127]




* Piecewise linear * 
[equation]

This would make the first ~60% of the total joystick motion reserved for extremely fine motor power control
while making the latter half as close as possible to the standard y =x curve.

This equation was determined because we decided on the initial equation of y = 1/3x. This worked nicely 
since it intersected the point (75, 25). From here, we used point slope form to find the remaining piece of the
line which would intersect 127, 127. This math is shown below:

this process was then duplicated for the negative portion of the graph. 

[graph]

Overall, we decided agianst this function because after testing the driver felt that the bottom speeds were simply
too slow and he didn't feel like he had control over higher speeds. 



* Sign preserving X squared * 
[equation] 

This makes the speeds follow a shallow curve for lower joystick inputs but then jump up rapidly toward the end of the 
joystick movement. It must be piecewise to preserve the sign, a fairly simple task in software

The equation was determined simply by normalization of joystick inputs (so that 1 was max), squaring (so that all numbers except
one [max] itself get smaller), then scaling back up to workable sizes. This equation is the following:

which simplifies to the equation listed above.

This was fairly effective, our driver liked the control but didn't feel that his top speeds were limited in any way. We
will most likely be using this from here on out. 


Here are all the equatiobs plotted on the same graph for comparison:
