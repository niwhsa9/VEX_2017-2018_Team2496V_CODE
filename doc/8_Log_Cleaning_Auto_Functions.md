## Cleaning Auto Functions

Today was mostly spent cleaning up our autonomous drive functions to make them as accurate as possible. We checked accuracy with what we call the "square test". The idea is you have the robot drive in a perfect square: (forward 36 inches, 90 degree turn) * 4

[code here]

If the functions are accurate, the robot will end up at almost exactly the same spot. This is much better then doing short measurements, because error accumulating over time tends to be more dramatic and noticeable then after one motion.

Through running this test, we tuned our drive constant to be 0.00035. We did notice that uneven tiles seemed to effect our motion, so we were careful with this. This is where our constant will stay unless a further change is needed. We also made the min speed 25. Once these changes were made, we had high precision test runs. Out of the 5 times we ran the square test, it was within +-2 inches of the starting position all 5 times.

We also noticed today that downloading code with the programming hardware kit is finicky, and you need to be relatively close to the robot (5 feet) to make sure the download is reliable, otherwise the code crashes on boot.

We started and finished on the LCD diplay, which is relatively simple. The LCD display is documented on the next section.

Finally, we learned how to multi-thread with the PROS library. We will make use of this for our autonomous, which is documented in the main notebook.

[code here]
