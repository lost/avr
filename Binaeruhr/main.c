/*
 * main.c
 *
 *  Created on: 12.07.2012
 *      Author: lost
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sec PORTB
#define min PORTC
#define std PORTD
#define TIMER_START 0
#define STD_START 12
#define MIN_START 35

char i = 0;
char h = STD_START;


int main(void)
{
	DDRB = 0xFF;						// PORTB = Ausgang = Sekunden
	DDRC = 0xFF;						// PORTC = Ausgang = Minuten
	DDRD = 0xFF;						// PORTD = Ausgang = Stunden

    //Timer0 (8Bit-Timer) initialiesiern
	TCCR0 |= (1<<CS00) | (1<<CS02);		//Timer0
    TCNT0 = TIMER_START;	//Startwert des Timer0
    TIMSK |= (1<<TOIE0);	//interrupts erlauben

    //Interrups ein
    sei();

    sec = 0;
    min = MIN_START;
    std = STD_START;

    do {
    	//eventuell noch taster
    	/*
    	 * if (Taster 1 (D4) zu)
    	 *     delay 2sec;
    	 *
    	 * if (Taster 1 (D4) zu){
    	 *     DDRD |= (1<<PD5) //D5 zu taster
    	 * }
    	 */
    } while (1); // Mainloop
}

ISR (TIMER0_OVF_vect)
{
	i++;
	if(i>=20){
		i = 0;
		sec++;
		if(sec >= 60){
			sec = 0;
			min++;
		}

		if(min>=60){
			min = 0;
			h++;
		}

		if(h>24){
			h = 0;
		}
		char h1 = h;
		h1 = h1<<2;
		std = h1;
	}
}
