#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define OFF 0
#define ON 1

int nivelUmidade = 0;
int temp = 0;
int contadorms = 0;
int numero = 0;
int contadorms2 = 0;
int tempvar = 0;
int temp2 = 0;

int botaoPress()
{
	if (PINB & (1 << PB0))
	{
		while (PINB & (1 << PB0))
		{
			_delay_ms(1);
		}
		return 1;
	}
	return 0;
}

void desidrata()
{
	tempvar = 1;
	contadorms2 = 0;
	while (tempvar == 1)
	{
		_delay_ms(1);
		contadorms2++;
		if (nivelUmidade == 4 && contadorms2 == 5000)
		{
			PORTB &= ~(1 << PB2);
			nivelUmidade = 3;
			contadorms2 = 0;
		}
		else if (nivelUmidade == 3 && contadorms2 == 5000)
		{
			PORTB &= ~(1 << PB3);
			nivelUmidade = 2;
			contadorms2 = 0;
		}
		else if (nivelUmidade == 2 && contadorms2 == 5000)
		{
			PORTB &= ~(1 << PB4);
			nivelUmidade = 1;
			contadorms2 = 0;
		}
		else if (nivelUmidade == 1 && contadorms2 == 5000)
		{
			PORTB &= ~(1 << PB5);
			nivelUmidade = 0;
			contadorms2 = 0;
			tempvar = 0;
		}
	}
}

int main(void)
{

	DDRB |= (1 << PB5); // seta PB5 como saída
	DDRB |= (1 << PB4);
	DDRB |= (1 << PB3);
	DDRB |= (1 << PB2);
	DDRB &= ~(1 << PB0);  // seta PB0 como entrada
	PORTB &= ~(1 << PB0); // desabilita pull up

	while (1)
	{
		nivelUmidade = 0;
		temp = botaoPress();
		if (nivelUmidade == 1)
		{
			PORTB &= ~(1 << PB4); // desliga
			PORTB &= ~(1 << PB3); // desliga
			PORTB &= ~(1 << PB2); // desliga
		}
		else if (nivelUmidade == 2)
		{
			PORTB &= ~(1 << PB3); // desliga
			PORTB &= ~(1 << PB2); // desliga
		}
		else if (nivelUmidade == 3)
		{
			PORTB &= ~(1 << PB2); // desliga
		}
		contadorms = 0;

		while (temp == 1)
		{

			_delay_ms(1);
			contadorms++;

			if (contadorms == 1)
			{
				PORTB &= ~(1 << PB5); // desliga
				PORTB &= ~(1 << PB4); // desliga
				PORTB &= ~(1 << PB3); // desliga
				PORTB &= ~(1 << PB2); // desliga
			}
			if (contadorms == 1000)
			{
				nivelUmidade = 0;
				PORTB ^= (1 << PB5); // liga
				PORTB ^= (1 << PB4); // liga
				PORTB ^= (1 << PB3); // liga
				PORTB ^= (1 << PB2); // liga
			}
			else if (contadorms == 2000)
			{
				PORTB &= ~(1 << PB5); // desliga
				PORTB &= ~(1 << PB4); // desliga
				PORTB &= ~(1 << PB3); // desliga
				PORTB &= ~(1 << PB2); // desliga
			}
			else if (contadorms == 3000)
			{
				PORTB ^= (1 << PB5); // liga
				PORTB ^= (1 << PB4); // liga
				PORTB ^= (1 << PB3); // liga
				PORTB ^= (1 << PB2); // liga
				nivelUmidade = 1;
			}
			else if (contadorms == 4000)
			{
				PORTB &= ~(1 << PB4); // desliga
				PORTB &= ~(1 << PB3); // desliga
				PORTB &= ~(1 << PB2); // desliga
			}
			else if (contadorms == 5000)
			{
				PORTB ^= (1 << PB4); // liga
				PORTB ^= (1 << PB3); // liga
				PORTB ^= (1 << PB2); // liga
			}
			else if (contadorms == 6000)
			{
				PORTB &= ~(1 << PB3); // desliga
				PORTB &= ~(1 << PB2); // desliga
				nivelUmidade = 2;
			}
			else if (contadorms == 7000)
			{
				PORTB ^= (1 << PB3); // liga
				PORTB ^= (1 << PB2); // liga
			}
			else if (contadorms == 8000)
			{
				PORTB &= ~(1 << PB3); // desliga
				PORTB &= ~(1 << PB2); // desliga
			}
			else if (contadorms == 9000)
			{
				PORTB ^= (1 << PB3); // liga
				PORTB ^= (1 << PB2); // liga
				nivelUmidade = 3;
			}
			else if (contadorms == 10000)
			{
				PORTB &= ~(1 << PB2); // desliga
			}
			else if (contadorms == 11000)
			{
				PORTB ^= (1 << PB2); // liga
			}
			else if (contadorms == 12000)
			{
				nivelUmidade = 4;
				desidrata();
				temp = 0;
			}
		}
	}
}
