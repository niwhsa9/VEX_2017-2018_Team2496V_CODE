## First Test
The following describe the issues and fixing process we encountered on our first runs of the new code. We had two dates to test, each one we discovered new problems, and debugged them until things worked. By the end of the second day, we were fairly successful.

** Day 1 6/12/17: **
- Upon starting the code, we encountered an instant SegmentationFault, which usually indicates an attempt to use pointers which aren't pointing to anything. In general, it indicates illegal read/write
  1. We eventually realized that the issue was the function __libc_init_array();. This apparently needs to be called explicitly in an extern "C"{} block. We saw this in a VexForum post from one of the PROS creators. The function is used by C to initalize static arrays declared in code.

**Day 2 6/17/17:**
- We noticed that setters in the constructor were defined in header, so moved them to src file, since its good practice
  1. This caused had compilation issues with    __cxa_pure_virtual() function
  2.  We hacked this a bit using the following code, its not clean, but it will do for the time being: [code here]
- None of the setMotor() function calls worked
  1. debugging made it clear that _motors[] array wasn't properly populated
  2. We checked that _motors[] received correct values in constructor, it did
  3. We took a guess that pointer arrays were the problem, perhaps the memory locations are lost or wiped?
  4. We changed pointers in constructor to static array sizes, this needs to be changed in the future. We will do further investigation. [code here]
- Now using hardcoded constants for DR4B start values used in control loop instead of values at startup

**Results:** On the first day, we resolved the segmentation faults. By the end of two days, everything in opcontrol worked. We should be ready to go for autonomous and other tests.
