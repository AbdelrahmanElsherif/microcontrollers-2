#ifndef UART_H
#define UART_H

void UART_init (void);
void UART1_Handler();
void send_byte(uint8_t one_byte);
void send_str(unsigned char *buffer);

#endif
