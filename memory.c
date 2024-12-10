#include "memory.h"
#include "tty.h"
#include "libk.h"

static char *MEMORY_REGION_T[MAX_REGION_TYPES] = {
  "UNKNOWN",
  "AVAILABLE",
  "RESERVED",
  "ACPI",
  "ACPI NVS",
  "BAD"
};

static basic_meminfo_t mem_info;
static memory_region_t mem_regions[MAX_REGIONS];
static int num_regions = 0;

//toto som teraz dorobil
void set_basic_meminfo(size_t lower, size_t upper) {
  mem_info.lower = lower;
  mem_info.upper = upper;
}

void peek(size_t addr, int count) {
  mem_ptr_t *p = (mem_ptr_t *) addr;
#ifdef CONFIG_ARCH_X86_32
  for (int i = 0; i < count; i++) {
    printf("Peek addr=%x, %x%x%x%x %x%x%x%x\n", p, p->nibble.n4,
        p->nibble.n3, p->nibble.n2, p->nibble.n1, p->nibble.n8,
        p->nibble.n7, p->nibble.n6, p->nibble.n5);
    p += 1;
  }
#endif
}

/*
 * Extract the type of memory region
 */
static char *mem_reg_lookup(int type) {
  if (type >= MAX_REGION_TYPES) {
    return MEMORY_REGION_T[0];
  }

  return MEMORY_REGION_T[type];
}

void print_mem_regions() {
  printf("MEMORY MAP - z ODYSSEY\n");
  for (int idx = 0; idx <= num_regions; idx++) {
    memory_region_t mem_reg = get_mem_region(idx);
    printf("  %d: 0x%x - 0x%x %d [%s]\n",
        idx,
        mem_reg.start,
        mem_reg.end,
        mem_reg.len,
        mem_reg_lookup(mem_reg.type));
  }
}

void set_num_mem_regions(int num) {
  num_regions = num;
}

void add_mem_region(int idx, size_t start, size_t len, size_t type) {
  // TODO: deprecate this with dynamic memory allocation
  if (idx >= MAX_REGIONS) {
    printf("exceeded maximum number of memory regions");
  }

  mem_regions[idx].start = start;
  mem_regions[idx].end   = start+len-1;
  mem_regions[idx].len   = len-1;
  mem_regions[idx].type  = type;
}

memory_region_t get_mem_region(int idx) {
  return mem_regions[idx];
}

