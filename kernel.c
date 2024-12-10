
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "multiboot.h"
#include "tty.h"
#include "serial.h"
#include "libk.h"
#include "io.h"
#include "hofno.h"

#include "boothdr.h"
#include "memory.h"

/* Global variable to store Multiboot information */
multiboot_info_t *mbi;

/* Macros. */

/* Check if the bit BIT in FLAGS is set. */
//  #define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

/* Forward declarations. */
void cmain(unsigned long magic, unsigned long addr);

/* Function to draw a pixel at (x, y) with the specified color */
void putpixel(int x, int y, uint32_t color) {
    void *fb = (void *)(uintptr_t)mbi->framebuffer_addr;
    multiboot_uint32_t *pixel = fb + mbi->framebuffer_pitch * y + 4 * x;
    *pixel = color;
}

// Tato funkcia zobrazi obrazok z toho array co je v header subore,
// ktory je vytvoreny z toho obrazku PPM
int splash()
{
	//struct fb_info *fbi = get_fb_info();
	size_t pad_cols = 0;
	size_t pad_rows = 0;

	if ((1024 - PPM_COLS) > 0) {
		if ((768 - PPM_ROWS) > 0) {
			pad_cols = (1024  / 2) - (PPM_COLS / 2);
			pad_rows = (768 / 2) - (PPM_ROWS / 2);
		}
	}

	for (int prows = 0; prows < PPM_ROWS; prows++) {
		for (int pcols = 0; pcols < PPM_COLS; pcols++) {

			size_t pos = ((prows * PPM_COLS) + pcols) * 3;
			size_t ci  = ((ppm_array[pos]   << 16) & 0xff0000) |
				     ((ppm_array[pos+1] << 8)  & 0xff00)   |
				      (ppm_array[pos+2]        & 0xff);

			putpixel(pad_cols + pcols, pad_rows + prows, ci);
		}
	}

	return 0;
}

//TOTO ZOBRAZUJE TEN KURZOR NA OBRAZOVKE
int kurzor2(int w, int h)
{
//putpixel( sirka,   vyska,    FARBA);
//  putpixel( X,       Y,     FARBA);
    putpixel(0+w, 0+h, 0x000000); // 1 riadok
    putpixel(0+w, 1+h, 0x000000); // 2 riadok
    putpixel(1+w, 1+h, 0x000000); // 2 riadok
    putpixel(0+w, 2+h, 0x000000); // 3 riadok
    putpixel(1+w, 2+h, 0xFFFFFF); // 3 riadok
    putpixel(2+w, 2+h, 0x000000); // 3 riadok
    putpixel(0+w, 3+h, 0x000000); // 4 riadok
    putpixel(1+w, 3+h, 0xFFFFFF); // 4 riadok
    putpixel(2+w, 3+h, 0xFFFFFF); // 4 riadok
    putpixel(3+w, 3+h, 0x000000); // 4 riadok
    putpixel(0+w, 4+h, 0x000000); // 5 riadok
    putpixel(1+w, 4+h, 0xFFFFFF); // 5 riadok
    putpixel(2+w, 4+h, 0xFFFFFF); // 5 riadok
    putpixel(3+w, 4+h, 0xFFFFFF); // 5 riadok
    putpixel(4+w, 4+h, 0x000000); // 5 riadok
    putpixel(0+w, 5+h, 0x000000); // 6 riadok
    putpixel(1+w, 5+h, 0xFFFFFF); // 6 riadok
    putpixel(2+w, 5+h, 0xFFFFFF); // 6 riadok
    putpixel(3+w, 5+h, 0xFFFFFF); // 6 riadok
    putpixel(4+w, 5+h, 0xFFFFFF); // 6 riadok
    putpixel(5+w, 5+h, 0x000000); // 6 riadok
    putpixel(0+w, 6+h, 0x000000); // 7 riadok
    putpixel(1+w, 6+h, 0xFFFFFF); // 7 riadok
    putpixel(2+w, 6+h, 0xFFFFFF); // 7 riadok
    putpixel(3+w, 6+h, 0xFFFFFF); // 7 riadok
    putpixel(4+w, 6+h, 0xFFFFFF); // 7 riadok
    putpixel(5+w, 6+h, 0xFFFFFF); // 7 riadok
    putpixel(6+w, 6+h, 0x000000); // 7 riadok
    putpixel(0+w, 7+h, 0x000000); // 8 riadok
    putpixel(1+w, 7+h, 0xFFFFFF); // 8 riadok
    putpixel(2+w, 7+h, 0xFFFFFF); // 8 riadok
    putpixel(3+w, 7+h, 0xFFFFFF); // 8 riadok
    putpixel(4+w, 7+h, 0xFFFFFF); // 8 riadok
    putpixel(5+w, 7+h, 0xFFFFFF); // 8 riadok
    putpixel(6+w, 7+h, 0xFFFFFF); // 8 riadok
    putpixel(7+w, 7+h, 0x000000); // 8 riadok
    putpixel(0+w, 8+h, 0x000000); // 9 riadok
    putpixel(1+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(2+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(3+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(4+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(5+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(6+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(7+w, 8+h, 0xFFFFFF); // 9 riadok
    putpixel(8+w, 8+h, 0x000000); // 9 riadok
    putpixel(0+w, 9+h, 0x000000); // 10 riadok
    putpixel(1+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(2+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(3+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(4+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(5+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(6+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(7+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(8+w, 9+h, 0xFFFFFF); // 10 riadok
    putpixel(9+w, 9+h, 0x000000); // 10 riadok
    putpixel(0+w, 10+h, 0x000000); // 11 riadok
    putpixel(1+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(2+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(3+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(4+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(5+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(6+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(7+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(8+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(9+w, 10+h, 0xFFFFFF); // 11 riadok
    putpixel(10+w, 10+h, 0x000000); // 11 riadok
    putpixel(0+w, 11+h, 0x000000); // 12 riadok
    putpixel(1+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(2+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(3+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(4+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(5+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(6+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(7+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(8+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(9+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(10+w, 11+h, 0xFFFFFF); // 12 riadok
    putpixel(11+w, 11+h, 0x000000); // 12 riadok
    putpixel(0+w, 12+h, 0x000000); // 13 riadok
    putpixel(1+w, 12+h, 0xFFFFFF); // 13 riadok
    putpixel(2+w, 12+h, 0xFFFFFF); // 13 riadok
    putpixel(3+w, 12+h, 0xFFFFFF); // 13 riadok
    putpixel(4+w, 12+h, 0xFFFFFF); // 13 riadok
    putpixel(5+w, 12+h, 0xFFFFFF); // 13 riadok
    putpixel(6+w, 12+h, 0xFFFFFF); // 13 riadok
    putpixel(7+w, 12+h, 0x000000); // 13 riadok
    putpixel(8+w, 12+h, 0x000000); // 13 riadok
    putpixel(9+w, 12+h, 0x000000); // 13 riadok
    putpixel(10+w, 12+h, 0x000000); // 13 riadok
    putpixel(11+w, 12+h, 0x000000); // 13 riadok
    putpixel(0+w, 13+h, 0x000000); // 14 riadok
    putpixel(1+w, 13+h, 0xFFFFFF); // 14 riadok
    putpixel(2+w, 13+h, 0xFFFFFF); // 14 riadok
    putpixel(3+w, 13+h, 0xFFFFFF); // 14 riadok
    putpixel(4+w, 13+h, 0x000000); // 14 riadok
    putpixel(5+w, 13+h, 0xFFFFFF); // 14 riadok
    putpixel(6+w, 13+h, 0xFFFFFF); // 14 riadok
    putpixel(7+w, 13+h, 0x000000); // 14 riadok
    putpixel(0+w, 14+h, 0x000000); // 15 riadok
    putpixel(1+w, 14+h, 0xFFFFFF); // 15 riadok
    putpixel(2+w, 14+h, 0xFFFFFF); // 15 riadok
    putpixel(3+w, 14+h, 0x000000); // 15 riadok
    putpixel(5+w, 14+h, 0x000000); // 15 riadok
    putpixel(6+w, 14+h, 0xFFFFFF); // 15 riadok
    putpixel(7+w, 14+h, 0xFFFFFF); // 15 riadok
    putpixel(8+w, 14+h, 0x000000); // 15 riadok
    putpixel(0+w, 15+h, 0x000000); // 16 riadok
    putpixel(1+w, 15+h, 0xFFFFFF); // 16 riadok
    putpixel(2+w, 15+h, 0x000000); // 16 riadok
    putpixel(5+w, 15+h, 0x000000); // 16 riadok
    putpixel(6+w, 15+h, 0xFFFFFF); // 16 riadok
    putpixel(7+w, 15+h, 0xFFFFFF); // 16 riadok
    putpixel(8+w, 15+h, 0x000000); // 16 riadok
    putpixel(0+w, 16+h, 0x000000); // 17 riadok
    putpixel(1+w, 16+h, 0x000000); // 17 riadok
    putpixel(6+w, 16+h, 0x000000); // 17 riadok
    putpixel(7+w, 16+h, 0xFFFFFF); // 17 riadok
    putpixel(8+w, 16+h, 0xFFFFFF); // 17 riadok
    putpixel(9+w, 16+h, 0x000000); // 17 riadok
    putpixel(6+w, 17+h, 0x000000); // 18 riadok
    putpixel(7+w, 17+h, 0xFFFFFF); // 18 riadok
    putpixel(8+w, 17+h, 0xFFFFFF); // 18 riadok
    putpixel(9+w, 17+h, 0x000000); // 18 riadok
    putpixel(7+w, 18+h, 0x000000); // 19 riadok
    putpixel(8+w, 18+h, 0x000000); // 19 riadok

    return 0;
}


void cmain(unsigned long magic, unsigned long addr) {
    // Initialize serial communication
    init_serial();

    // Clear the screen
    cls();

    // Set MBI to the address of the Multiboot information structure
    mbi = (multiboot_info_t *)addr;

    // // Is boot_device valid?
//     if (CHECK_FLAG(mbi->flags, 1))
//         printf("boot_device = 0x%x\n", (unsigned)mbi->boot_device);
//
        
    init_mb(magic, addr);
        
    print_mem_regions();
        
    printf("Boot complete, exiting kernel\n");

    // TU MAM NEJAKE STVORCEKY POMOCOU PUTPIXEL
    putpixel(511, 383, 0xFF0000);
    putpixel(512, 383, 0xFF0000);
    putpixel(513, 383, 0xFF0000);
    putpixel(511, 384, 0xFF0000);
    putpixel(512, 384, 0xFF0000);
    putpixel(513, 384, 0xFF0000);
    putpixel(511, 385, 0xFF0000);
    putpixel(512, 385, 0xFF0000);
    putpixel(513, 385, 0xFF0000);

    putpixel(383, 383, 0x00FF00);
    putpixel(384, 383, 0x00FF00);
    putpixel(385, 383, 0x00FF00);
    putpixel(383, 384, 0x00FF00);
    putpixel(384, 384, 0x00FF00);
    putpixel(385, 384, 0x00FF00);
    putpixel(383, 385, 0x00FF00);
    putpixel(384, 385, 0x00FF00);
    putpixel(385, 385, 0x00FF00);


    // Toto sa vlasne zobrazi to osdev logo
    splash();

    // A toto je ten kurzor a to su suradnice na ktorych sa zobrazi
    kurzor2(12, 12);

    printf("Nas nezastavia ziadne hradne muri\n");

}
