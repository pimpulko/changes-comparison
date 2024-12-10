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
 */

#ifndef FLATMM_H
#define FLATMM_H

#include <stdint.h>
#include <stddef.h>

#define MEM_START_ADDR 0x200000 // initialize mm at the 2MB mark
#define MEM_FRAME_SIZE 5        // size of each frame of memory
#define MEM_END_ADDR   0x200100

#define FRAME_ROOT       1
#define FRAME_AVAILABLE  2

struct flat_mem_page {
  uint8_t flags;
  size_t  next;
  size_t  prev;
  uint8_t frame[MEM_FRAME_SIZE];
};

typedef struct flat_mem_page flat_mem_page_t;

void  init_flatmm();
void* get_free_frame(size_t size);

#endif
