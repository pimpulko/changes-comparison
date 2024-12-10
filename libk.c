/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2020, Anuradha Weeraman
 *
 * C++ version 0.4 char* style "itoa", Copyright Lukás Chmela
 * Released under GPLv3.
 * http://www.strudel.org.uk/itoa/
 */

#include "libk.h"
#include "tty.h"


//pridane
void* memcpy(void * restrict d, const void * restrict s, size_t n) {
  char *dest = d;
  const char *src = s;

  for (size_t i = 0; i < n; i++) {
    dest[i] = src[i];
  }

  return dest;
}

//tiez pridane
void* memset(void *s, int c, size_t n) {
  unsigned char *ch = s;
  for (size_t i = 0; i < n; i++)
    ch[i] = (char) c;
  return s;
}

//upravene
size_t strnlen(const char *str, size_t maxlen) {
  size_t sz = 0;
  if (str == NULL) return 0;
  while (str[sz] != '\0' && sz++ < maxlen-1);
  return sz;
}

//pridane
char* strncpy(char * restrict dest, const char * restrict src, size_t n) {
  size_t i = 0;

  for (; src[i] != '\0' && i < n; i++)
    dest[i] = src[i];

  for (; i < n; i++)
    dest[i] = '\0';

  return dest;
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
