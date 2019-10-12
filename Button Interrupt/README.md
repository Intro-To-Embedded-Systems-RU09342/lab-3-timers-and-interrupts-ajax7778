# Button Interrupt
Last lab you were introduced to the idea of "Polling" where in you would constantly check the status of the P1IN register to see if something has changed. While your code may have worked, it ends up spending a ton of time just checking something that has not changed. What we can do instead is use another two registers available to us from the GPIO peripheral, P1IE and P1IES, to allow our processor to just chill out and wait until something happens to act upon it. Without spending too much space on this README with explanations, what makes these interrupts tick is the following code:

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
}
While you still need to initialize the Ports to be interrupt enabled and clear the flags, this "Pragma Vector" tells the compiler that when a particular interrupt occurs, run this code.

## MSP430FR6989
For this board, the button interrupt was gathered from an existing sample code. There are multiple important protocols when it comes to 
creating an interrupt that are shown in this code. The interrupt allows for an LED to blink when a button is pressed. This triggers an interrupt, which allows for the code above to be executed. This is the interrupt code. The board then enters into low power mode 4. 

## MSP430G2553
This board works with interrupts very similarly to the 6989, but the LED and switch ports are different. But in both cases, the board initializes the output pins, clears the interrupt flags, enables the interrupt on the LED, then executes the interrupt service routine (ISR). This board also enters low power mode 4 upon execution of the ISR.
