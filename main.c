#include <avr/io.h>
#include <avr/interrupt.h>

void UART_Init(unsigned int ubrr);
void UART_Transmit(unsigned char data);
unsigned char UART_Receive(void);

int main(void) {
	unsigned int ubrr = 51;
	UART_Init(ubrr);
	sei();
	while (1) {
	}
}

void UART_Init(unsigned int ubrr) {
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

ISR(USART_RXC_vect) {
	unsigned char receivedChar = UART_Receive();
	if (receivedChar >= 'a' && receivedChar <= 'z') {
		receivedChar -= 32;
		} else {
		receivedChar += 1;
	}
	UART_Transmit(receivedChar);
}

void UART_Transmit(unsigned char data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

unsigned char UART_Receive(void) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}
