#include <stdint.h>
#include "hexprint.h"
#include "libk.h"
#include "memory.h"


void run_hexprint(int num_addresses) {
  


printf("\n0TEST0: 1111 1111 1111 1111 1111 1111 1111 1111  ....  ....  ....  ....");
  //printf_addr("%c", q->byte.b2);
  
  mem_ptr_t *h;
   // int num_addresses;
    //int mem_address = 4; 
    int i, j, k;


for (i = 0; i < num_addresses; i++) {    
        // Increment address by 4 bytes each iteration
        h = (mem_ptr_t *)(0x100000 + i * 0x10);



    for (j = 0; j < 4; j++) {
        // Increment address by 4 bytes each iteration
        //h = (mem_ptr_t *)((char *)h + 0x4);
        
        // Print the address when starting or every 5th iteration
        if (j % 4 == 0) {
            printf("\n%p:", h);
            }
        
        
        // Print the nibbles in hex format
        printf(" %x%x%x%x %x%x%x%x", 
            h->nibble.n4, h->nibble.n3, h->nibble.n2, h->nibble.n1,
            h->nibble.n8, h->nibble.n7, h->nibble.n6, h->nibble.n5);
            
            h = (mem_ptr_t *)((char *)h + 0x4);
            
        //printf(" %c %c %c %c", h->byte.b1, h->byte.b2, h->byte.b3, h->byte.b4)
    }
    
    
    h = (mem_ptr_t *)((char *)h - 0x10);
    //printf("\n");
    
    for (k = 0; k < 4; k++){
    	
    printf("  %c%c%c%c", h->byte.b1, h->byte.b2, h->byte.b3, h->byte.b4);
    	h = (mem_ptr_t *)((char *)h + 0x4);
    
    }
    
    h = (mem_ptr_t *)((char *)h - 0x10);
    
}
}
