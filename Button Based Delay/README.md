# Button Based Delay
Now that you have begun to familiarize yourself with the TIMER modules, why don't we make an interesting change to our code 
from the last lab.

## Task
Setup your microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of 
the buttons on board, a user should be able to set the delay or blinking rate of the LED by holding down a button. The duration in 
which the button is depressed should then become the new rate at which the LED blinks. As previously stated, you most likely will want 
to take advantage of the fact that TIMER modules exist and see if you can let them do a bulk of the work for you.

## MSP430G2553
On this board, the LED powers on blinking at 10Hz. When the button P1.3 is pressed, it starts blinking slower. Another press starts blinking
it slower, and slower again until it does not blink at all. Then one more button press turns it off. The way this works is the timer A
is initialized and set to up mode, setting a CCR0 value of 300 to change the period of the timer. Interrupts are enabled, and an if statement
is included for the button press. When the button is pressed, it changes to rising edge, clears the timer, and changes to continuous mode. 
When the button isn't pressed, the timer is stopped and the CCR0 value is set to the value of the timer at that point. It then changes to 
falling edge detect so that it can see if the button is pressed again. 
