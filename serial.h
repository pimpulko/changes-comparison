#ifndef SERIAL_H
#define SERIAL_H

#define PORT 0x3f8

void init_serial();
int is_transmit_empty();
void write_serial(int c);


#endif