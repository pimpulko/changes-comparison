OBJECTS = boot.o tty.o serial.o io.o libk.o memory.o boothdr.o kernel.o

.PHONY: run run-cd grub copy clean
	
myos.bin: $(OBJECTS)
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

%.o: %.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

%.o: %.S
	i686-elf-gcc -c $< -o $@

run:
	qemu-system-i386 -kernel myos.bin -serial stdio
	
run-cd:
	qemu-system-i386 -cdrom myos.iso -vga std -serial stdio
	
grub:
	grub-mkrescue -o myos.iso isodir
	
copy:
	cp myos.bin isodir/boot

clean:
	rm *.o *.bin *.iso isodir/boot/myos.bin
