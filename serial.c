#include <stdint.h>
#include "serial.h"
#include "io.h"

void init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
   outb(PORT + 4, 0x0F);
   return 0;
   }
   
int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}

void write_serial(int c) {
   while (is_transmit_empty() == 0);
   
   //////////////
   // if (c == '\0'){
//    	c = '\n';		  //toto je preto aby v serial print v terminali mal (\n a nie \0)
//    	}
	///////////////
   outb(PORT,c);
}