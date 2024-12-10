#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MAX_REGION_TYPES  6
#define MAX_REGIONS       100

typedef struct memory_region_struct {
  uint32_t start;
  uint32_t end;
  uint32_t len;
  uint32_t type;
} memory_region_t;

union mem_ptr {
  // For x86, the order is n4, n3, n2, n1, n8, n7, n6, n5
  struct {
    uint8_t n1: 4;
    uint8_t n2: 4;
    uint8_t n3: 4;
    uint8_t n4: 4;
    uint8_t n5: 4;
    uint8_t n6: 4;
    uint8_t n7: 4;
    uint8_t n8: 4;
  } nibble;
  // For x86, the order is b2, b1, b4, b3
  struct {
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
  } byte;
  // For x86, the order is w2, w1
  struct {
    uint16_t w1;
    uint16_t w2;
  } word;
} __attribute__((packed));
typedef union mem_ptr mem_ptr_t;

void add_mem_region(int idx, uint32_t start, uint32_t len, uint32_t type);
memory_region_t get_mem_region(int idx);
void set_num_mem_regions(int num);
void print_mem_regions();
void peek(uint32_t addr, int count);

#endif

