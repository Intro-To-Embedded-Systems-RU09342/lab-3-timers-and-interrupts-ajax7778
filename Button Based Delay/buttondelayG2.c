/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    BCSCTL3 = LFXT1S_2;                        //tells MC to use internal crystal
    P1DIR |= BIT0;                          //set P1.0 as out
    P1DIR &= ~BIT3;                        //set P1.3 as in
    P1DIR |= BIT6;                             //set P1.6 to out
    P1IE |=  BIT3;                            // P1.3 interrupt enabled
    P1IES |= BIT3;                            // P1.3 falling edge
    P1REN |= BIT3;                            // Enable Pull Up on SW2 (P1.3)
    P1OUT |= BIT3;                              //sets pull up resistor
    P1IFG &= ~BIT3;                           // P1.3 IFG cleared

    //set up timer
    TA0CTL = TASSEL_1 + ID_1 + MC_1; //Timer 0 control = ACLK, divide by 2, count up to CCR0

    //set up CCR1
    CCTL0 =CCIE;  //enable capture compare interrupt
    CCR0 = 300; //change period

    _BIS_SR(LPM0_bits + GIE);   //enable global interrupt
    return 0;
}

//interrupt routine for timer
#pragma vector =TIMER0_A0_VECTOR
__interrupt void TIMER0_A1(void)
{

    P1OUT ^= BIT0; //toggle P1.0 LED

}


//interrupt routine for button
#pragma vector =PORT1_VECTOR
__interrupt void Button_down(void)
{
    if (P1IES & BIT3) //if falling edge
    {
        P1IES &=~BIT3; //change to rising edge
        TACTL=TACLR; //clear timer
        TA0CTL = TASSEL_1 + ID_1 + MC_2; //change to continuous
        P1OUT |= BIT6; //checks to see if we're in the if statement
    }

    else
    {
        P1OUT &= ~BIT6; //turn off if statement test LED
        TA0CTL = MC_0; // stop timer
        CCR0 = TA0R; //set CCR0 to current timer value
        TACTL |= TACLR; //clear timer
        TA0CTL = TASSEL_1 + ID_1 + MC_1; //change to up mode
        P1IES |= BIT3; //change to falling edge detect
    }

    P1IFG &= ~BIT3; // clear interrupt flag
}
