## Introduction
Just as every team should document their robot, we feel that every team should document the code that goes along with it.

Historically, we have used RobotC in 2496, but this year we wanted to try using raw C++ with the PROS library and GCC toolchain. We did this because we think that it will allow us to accomplish the following:

- Increase runtime efficiency and speed
- Allow for better organization
  - Separate files
  - Headers to define structure
- Provide a more flexible development environment
  - Not locked into RobotC editor
  - Can use Unix based operating systems
  - Gives us access to any C99/C++ tools and features
- Make code more reusable for future years
  - Object oriented design
  - Subsystem based
- Increase speed of development and testing

But most importantly, we think that we have a lot to learn from PROS, as C/C++ are languages that are widely used in the professional software engineering and computer science fields. We have very specific objectives in mind when it comes to development:
 - Minimize failure at competition (stability)
 - Make code as reusable and readable as possible
 - Have protocols to ensure the safety of our team, other teams, and the robot
 - Use good practice, conform to standards, and document!

In this notebook, we will document our code's structure, the signifigant changes made to the code, algorithms used, and the development process. What we will not include however, is testing data regarding the robot specifically, this can be found in our main notebook. We also aren't including the full code, as it spans hundreds of lines split into nearly a dozen files. The full code can be found at:
