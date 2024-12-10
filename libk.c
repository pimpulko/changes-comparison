// Treba tu dorobit to MEMCPY a aj dalsie
// v ODYSSEY ma "putchar" v Libk.c ale je to iba to iste ako to "printc" co ma v tty.c
// a ja mam na to iba funkciu putchar, ktora je v tty.c

#include "libk.h"
#include "tty.h"

size_t strlen(char *str) {
  size_t sz = 0;
  while (str[sz++] != '\0');
  return sz;
}

void itoa (char *buf, int base, int d)
    {
      char *p = buf;
      char *p1, *p2;
      unsigned long ud = d;
      int divisor = 10;

      /* If %d is specified and D is minus, put ‘-’ in the head. */
      if (base == 'd' && d < 0)
        {
          *p++ = '-';
          buf++;
          ud = -d;
        }
      else if (base == 'x')
        divisor = 16;

      /* Divide UD by DIVISOR until UD == 0. */
      do
        {
          int remainder = ud % divisor;

          *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
        }
      while (ud /= divisor);

      /* Terminate BUF. */
      *p = 0;

      /* Reverse BUF. */
      p1 = buf;
      p2 = p - 1;
      while (p1 < p2)
        {
          char tmp = *p1;
          *p1 = *p2;
          *p2 = tmp;
          p1++;
          p2--;
        }
    }


void printf (const char *format, ...)
{
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;
  
  while ((c = *format++) != 0)
    {
      if (c != '%')
        putchar (c);
      else
        {
          char *p, *p2;
          int pad0 = 0, pad = 0;
          
          c = *format++;
          if (c == '0')
            {
              pad0 = 1;
              c = *format++;
            }

          if (c >= '0' && c <= '9')
            {
              pad = c - '0';
              c = *format++;
            }

          switch (c)
            {
            case 'c':
            	itoa (buf, c, *((int *) arg++));
        	p = buf;
        	if (p == 0x0A) {
          	putchar('.');  // Replace newline with '.'
        	} else {
          	putchar(p);    // Otherwise, print the character normally
        	}
        	break;
            
            case 'd':
            case 'u':
            case 'x':
              itoa (buf, c, *((int *) arg++));
              p = buf;
              goto string;
              break;

            case 's':
              p = *arg++;
              if (! p)
                p = "(null)";

            string:
              for (p2 = p; *p2; p2++);
              for (; p2 < p + pad; p2++)
                putchar (pad0 ? '0' : ' ');
              while (*p)
                putchar (*p++);
              break;

            default:
              putchar (*((int *) arg++));
              break;
            }
        }
    }
}


