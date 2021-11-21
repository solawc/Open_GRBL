#include "unittest_transport.h"
#include <output_export.h>



#ifdef __GNUC__
void output_start(unsigned int baudrate __attribute__((unused)))
#else
void output_start(unsigned int baudrate)
#endif
{
    unittest_uart_begin();
}

void output_char(int c)
{
    unittest_uart_putchar(c);
}

void output_flush(void)
{
    unittest_uart_flush();
}

void output_complete(void)
{
   unittest_uart_end();
}