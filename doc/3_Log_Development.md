## Initial Development

When we started in early June, we used RobotC for our initial tests. These were quick scripts, and the important bits are documented in the primary notebook (See pages ). All of our old RobotC functions from previous seasons and this one is now considered legacy, and is not documented in this book unless it is relevant or ported to PROS. Our summer meeting schedule included June and August, giving us July to develop the actual code outside of school. Since we weren't familiar with C++, we spent a good amount of that time learning the language first. During development, we could only check our work through compilation, but not having access to the robot meant no runtime tests. Obviously, this is not ideal, and led to many issues later on. However, runtime tests (described on the next section) were done later. The development timeline is logged below. Code was compiled each day after changes were made. There were few major problems with getting code to compile. Most issues were runtime, which we discovered later. This is documented in section 4.

**5/20/17-5/27/17:** We learned C++ object oriented basics. Specifically, syntax specifics like constructors, pointers, inheritance. Many of the concepts are similar to Java, a language we already knew. We did this through writing simple test programs with C++11, not with PROS.

**5/27/17:** Started development, settled on using the "Subsystem" organization. Since all subsystems on the robot are similar in their core (contain motors, sensors, reverse values) they all inherit from a pure virtual base class, which defines these basic properties and some basic functionality. For example, the setAll() function activates all the motors at the specified speed, while automatically reversing them as needed without need for specification with the function call. The commented subsystem base class is pasted below:
[CODE HERE]
It also lets us have very clean and minimalist looking core files like in opcontrol.cpp:
[CODE HERE]

**5/29/17-6/2/17:** Created and implemented DR4B child class of Subsystem. This class contains the properties and control functions for our Double Reverse 4 Bar lift. The control loop algorithm was ported from our original RobotC version, which is shown in our main book on page (). This class is documented extensively (See 5).

**6/3/17-6/4/17** Independence day weekend, didn't really do much. However, DR4B's proportional control loop (based on the original RobotC version) is now a proportional and derivative control (See 5). We are not going to do a full PID for now because the integral constant takes a lot of time to tune in, and our first competition in September probably won't give us enough test time. Another thing was that pointer initialization was used for the DR4B object so that it is accessible in multiple files. This means that memory must be deleted manually.

**6/5/17-6/8/17** Created and implemented Drive child class of Subsystem. This was fairly straightforwad for operator control functions, but auton functions for turning and moving specified distances are more complicated. (See 6)

**6/8/17-6/10/17** Created and implemented Claw child class of Subsystem. Very basic functionality. (See 7) Also added LCD display code. (See 8).
