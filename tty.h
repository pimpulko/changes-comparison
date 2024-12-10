#ifndef TTY_H
#define TTY_H

//#include "types.h"
#include <stdint.h>
#include "serial.h"
//#include "multiboot.h"


#define COLUMNS                 80
#define LINES                   24
#define ATTRIBUTE               7
#define VIDEO                   0xB8000

//void clear_screen(void);
void print(char *str);
void putchar(int c);
void cls (void);
#endif
