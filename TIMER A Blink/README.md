# TIMER A Blink
The TIMER peripherals can be used in many situations thanks to it flexibility in features. For this lab, you will be only 
scratching the surface as to what this peripheral can do.

## MSP430FR6989
This board's timer code was gathered from the existing TI resource explorer code. Timer A is chosen and the interrupt is enabled on
the timer. The capture and compare value for this timer (CCR0) is set to 50000, and the control mode is set to continuous, meaning
that each time the timer counts to the CCR0 value, an interrupt is enabled. The device enters low power mode 0 on execution. The only 
change made to the existing code was to initialize the second LED to Timer A so that the two LEDs would blink at the same time. 

## MSP430G2553
The code for this board was also found on the resource explorer. The same thing is done as with the 6989, including the same CCR0 value. 
However, more changes were made to this code. The second LED was added, allowing both LEDs to be connected to Timer A. The mode of the timer
was changed from Continuous mode to Up/Down mode, which counts up to the CCR0 value, then back down to 0. The clock was also divided by 4
to make the blinks slower. 
