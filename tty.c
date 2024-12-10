#include <stddef.h>
#include "multiboot.h"
#include "tty.h"
#include "serial.h"

static int xpos;
static int ypos;
static volatile unsigned char *video;

void cls (void)
{
  int i;

  video = (unsigned char *) VIDEO;
  
  for (i = 0; i < COLUMNS * LINES * 2; i++)
    *(video + i) = 0;

  xpos = 0;
  ypos = 0;
}

void putchar (int c)
{
  if (c == '\n' || c == '\r')
    {
    newline:
      xpos = 0;
      ypos++;
      if (ypos >= LINES)
        ypos = 0;
	  write_serial('\r');
	  write_serial('\n');
      return;
    }

  *(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
  *(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

  xpos++;
  if (xpos >= COLUMNS)
    goto newline;
  write_serial(c);
}

// void clear_screen(void) {
//   for (int i=0; i<(ROWS*COLS); i++) {
//     matrix[i].ch = 0;
//     matrix[i].clr = 15;
//   }
// }

void print(char *str) {
  for (int i=0; str[i] != '\0'; i++) {
    putchar(str[i]);
  }
}
