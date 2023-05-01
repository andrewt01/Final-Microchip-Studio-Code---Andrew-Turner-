#include "Serial_lib2.h"


/* Parameters assigned in IO.H
ATmega1284P
USART0_RX_vect
UDR0
UCSR0A
RXC0
TXC0
UDRE0
U2X0 (I don't think we use this one)
UCSR0B
RXCIE0
TXCIE0  (I would have to check to see if we use this)
RXEN0
TXEN0
UCSR0C
UMSEL01 UMSEL00 (both set = 0 for asyncronous operation)
UPM00,UPM01 (we don't set these)
USBS0
UBRR0L, UBRR0H   Baud rate calculation is the same.
*/

//// UART Rx Interrupt
//ISR( USART0_RX_vect ) {
	//PCData = UDR0;
	////NewSerialData = 1;
//}


FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);




void USART_vInit(void) {
	stdout = &mystdout;
	
	// Set baud rate
	UBRR0H = (unsigned char) (USART_UBBR_VALUE >> 8);
	UBRR0L = (unsigned char) USART_UBBR_VALUE;

	// set double speed on UART to improve baud rate error
	//UCSR0A = (1 << U2X0);
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);  //| (1 << RXCIE0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1<<USBS0)| (3 << UCSZ00);
	//UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	/* Set frame format: 8data, 1stop bit */
    //UCSR0C |=  (3 << UCSZ00);
	// Set frame format to 8 data bits, no parity UPM01 UPM00 = 0, 1 stop bit USBSn = 0
}

  void USART_vSendByte(uint8_t u8Data)
  {
	  while ((UCSR0A & (1<<UDRE0) == 0)) ;
	  // Transmit data
	  UDR0 = u8Data;  
  }

uint8_t USART_vReceiveByte(void) {
	// Wait until a byte has been received
	while ((UCSR0A & (1 << RXC0)) == 0)
	;
	// Return received data
	return UDR0;
}


int uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);

	//insert code cut / pasted from data sheet.
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
	return 0;
}

uint8_t serialCheckRxComplete(void)
{
	return ((UCSR0A & (1 << RXC0))); // nonzero if serial data is available to read.
}
