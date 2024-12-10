#ifndef BOOTHDR_H
#define BOOTHDR_H

#include <stdint.h>
#include "multiboot.h"
#include "tty.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void init_mb(uint32_t magic, uint32_t addr);

#endif

