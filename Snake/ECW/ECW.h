extern void stop_watchdog();

extern void adc_init();

extern int adc_read();

extern void usart_init();

extern char usart_receive_char();

extern void usart_transmit_char(char ch);

extern void usart_transmit_string(char* str);

extern void usart_transmit_int_as_string(int i);

extern short charReceived;

extern void usart_init_async();

extern short usart_receive_char_async(char* ch);

extern void delay_us(int us);

extern void delay_ms(int ms);

extern void delay_s(int s);
