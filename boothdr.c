/**
 * Tu spisem veci ktore zmenim od originalu
 * 
 * 
 *
*/
#include <stdint.h>
#include "boothdr.h"
#include "memory.h"
#include "libk.h"
//#include "kernel.h"

/*
*  toto ja asi nevyuzijem kedze nemam ziaden command line
*/
// static char boot_cmdline[BOOT_CMDLINE_MAX];


// TOTO TU TERAZ NEPOTREBUJEM, on ma ten struct v KERNEL.H:

// extern struct acpi_descriptor_v1 *acpi_v1;
// extern struct acpi_descriptor_v2 *acpi_v2;
// extern struct boot_device        *boot_dev;
// extern struct framebuffer        *framebuffer;

/*
 * Extract multiboot provided information
 */
void init_mb(size_t magic, size_t addr) {
  int counter;
  multiboot_memory_map_t *mmap;
  multiboot_info_t *mbi;
  struct multiboot_tag *tag;
  struct multiboot_tag_basic_meminfo *meminfo;
  struct multiboot_tag_bootdev *bootdev_tag;

  /* Am I booted by a Multiboot-compliant boot loader? */
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      printf ("Invalid magic number: 0x%x\n", (unsigned) magic);
      return;
    }

  /* Set MBI to the address of the Multiboot information structure. */
  mbi = (multiboot_info_t *) addr;
  
  // /* Print out the flags. */
//   printf ("flags = 0x%x\n", (unsigned) mbi->flags);

	printf("Multiboot information structure: start=0x%x %dB\n", addr, *(size_t *) addr);

  /* Is the command line passed? */
  if (CHECK_FLAG (mbi->flags, 2))
    printf ("Command line:  %s\n", (char *) mbi->cmdline);
  
  if (CHECK_FLAG (mbi->flags, 9))
      printf ("Boot loader:  %s\n", (char *) mbi->boot_loader_name);
  
  /* Are mods_* valid? */
  if (CHECK_FLAG (mbi->flags, 3))
    {
      multiboot_module_t *mod;
      int i;
      
      printf ("mods_count = %d, mods_addr = 0x%x\n",
              (int) mbi->mods_count, (int) mbi->mods_addr);
      for (i = 0, mod = (multiboot_module_t *) mbi->mods_addr;
           i < mbi->mods_count;
           i++, mod++)
        printf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
                (unsigned) mod->mod_start,
                (unsigned) mod->mod_end,
                (char *) mod->cmdline);
    }

  /* Are mem_* valid? */
  if (CHECK_FLAG (mbi->flags, 0))
    printf ("Basic memory info: mem_lower = %uKB, mem_upper = %uKB\n",
            (unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);

  /* Is boot_device valid? */
  if (CHECK_FLAG (mbi->flags, 1))
    printf ("boot_device = 0x%x\n", (unsigned) mbi->boot_device);
  
  /* Are mmap_* valid? */
  if (CHECK_FLAG (mbi->flags, 6))
    {
      multiboot_memory_map_t *mmap;
      
      printf("MMAP, size = 0x%x\n", mmap->size);
      printf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
              (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
      printf ("INFO O PAMATI Z MULTIBOOT EXAMPLE\n");
	   int counter = 0;
    //  for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr; (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length; mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size)))
      for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
           (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
           mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                    + mmap->size + sizeof (mmap->size))) {
        printf ("   size = 0x%x, base_addr = 0x%x%08x,"
                " length = 0x%x%08x, type = 0x%x\n",
                (unsigned) mmap->size,
                (unsigned) (mmap->addr >> 32),
                (unsigned) (mmap->addr & 0xffffffff),
                (unsigned) (mmap->len >> 32),
                (unsigned) (mmap->len & 0xffffffff),
                (unsigned) mmap->type);
        add_mem_region(counter,
                      (uint32_t) mmap->addr,
                      (uint32_t) mmap->len,
                      (uint32_t) mmap->type);
        set_num_mem_regions(counter++);
			}
		//print_mem_regions();
    }
	//////////////////////////////////////////////////////////////////////
	//POTIALTO SOM TO PREROBIL, DALEJ MUSIM DAT FRAMEBUFFER INFO
	//////////////////////////////////////////////////////////////////////

  /* Bits 4 and 5 are mutually exclusive! */
  /*if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5))
  *  {
  *    printf ("Both bits 4 and 5 are set.\n");
  *    return;
  *  }
  *
  *   // Is the symbol table of a.out valid? 
  *if (CHECK_FLAG (mbi->flags, 4))
  *  {
  *    multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);
  *    
  *    printf ("multiboot_aout_symbol_table: tabsize = 0x%0x, "
  *            "strsize = 0x%x, addr = 0x%x\n",
  *            (unsigned) multiboot_aout_sym->tabsize,
  *            (unsigned) multiboot_aout_sym->strsize,
  *            (unsigned) multiboot_aout_sym->addr);
  *  }
  *
  *   // Is the section header table of ELF valid? 
  *if (CHECK_FLAG (mbi->flags, 5))
  *  {
  *    multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);
  *
  *    printf ("multiboot_elf_sec: num = %u, size = 0x%x,"
  *            " addr = 0x%x, shndx = 0x%x\n",
  *            (unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,
  *            (unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
  *  }
  */
  
    /* TOTO DORABAM JA - bude to FRAMEBUFFER info */
    if (CHECK_FLAG (mbi->flags, 12))
      printf ("framebuffer: addr=%x pitch=%d width=%d height=%d bpp=%d type=%d\n", (unsigned) mbi->framebuffer_addr, (unsigned) mbi->framebuffer_pitch, (unsigned) mbi->framebuffer_width, (unsigned) mbi->framebuffer_height, (unsigned) mbi->framebuffer_bpp, (unsigned) mbi->framebuffer_type);

}

