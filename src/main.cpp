#include<avr/io.h>
#include <util/delay.h>

void my_delay_ms(unsigned long time_ms);
int main(void)
{
    // CLAB TASK 1 --------------------------------------
    // connect LEDs to PORTD and set the pins to output mode 
    DDRD = (1 << PORTD3)| (1 << PORTD4); //LED on at PD3 and PD4
    // CLAB TASK 1 --------------------------------------
    // set up Timer0 in a CTC mode (TCCCR0A register) so that 
    // it reaches the max vaule at every 1ms (TCCR0B, OCR0A)
    TCCR0B = (1 << CS01)|(1 << CS00);  //timer 0 prescaler = Clock/64, TCC0B: (CS02, CS01, CS00) = (011)
    TCCR0A = (1 << WGM01);  //Set up CTC Mode for timer 0
    
    while(1)
    {
        // CLAB TASK 1 --------------------------------------
        // blink the LED here at 1Hz using my_delay_ms()
			  PORTD |= (1 << PORTD3); //turn on LED1
	  	 	my_delay_ms(500);
  
	  	 	PORTD &=~(1 << PORTD3);  //LED1 off
	  	 	my_delay_ms(500);
		}
}

void my_delay_ms(unsigned long time_ms)
{
    // CLAB TASK 1 --------------------------------------
    // poll/wait the register TIFR0 to check the OCF0A-bit
    // Once OCF0A-bit is set, write ‘1’ to clear the bit
    // increment a millisecond counter
    // repeat until the millisecond counter reaches time_ms
    unsigned long num_ms_count = 0;
    while (num_ms_count < time_ms) {
      while ((TIFR0 & (1<<TOV0)) != (1 << TOV0));
      TIFR0 &= (1<<TOV0);
      num_ms_count++;
    }
}