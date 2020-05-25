INCLUDE_DIR = include/
GCC_FLAGS = -Wall -fno-stack-protector -fno-builtin -m32 -I $(INCLUDE_DIR)
NASM_FLAGS = -f elf32 -I $(INCLUDE_DIR)

	# kstart to link with any module
MODULES = boot io kernel keyboard vga string utils time


OBJECTS = $(MODULES:%=obj/%.o)
ourOS: $(OBJECTS)
	#gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
	ld -m elf_i386 -T linker.ld $(OBJECTS) -o ourOS.bin -nostdlib

	#cc $(LDFLAGS) -nostdlib -m32 -Wl,-Ttext-segment,0x100000,-Map,ourOS.map -o ourOS.bin $(OBJECTS) 
	grub-file --is-x86-multiboot ourOS.bin
	mkdir -p isodir/boot/grub
	cp ourOS.bin isodir/boot/ourOS.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ourOS.iso isodir
	#mkdir -p iso/boot/grub
	
	#cp mtask iso/boot/
	#cp boot/stage2_eltorito boot/menu.lst iso/boot/grub/
	#mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o mtask.iso iso
	qemu-system-x86_64 -cdrom ourOS.iso

.PHONY: clean
clean:
	rm -f obj/* dep/* s/* ourOS ourOS.map ourOS.iso
	rm -rf iso

obj/%.o: src/%.asm
	nasm $(NASM_FLAGS) $< -o $@

obj/%.o: src/%.s
	as --32 $< -o $@


obj/%.o: src/%.c
	cc $(GCC_FLAGS) -c $< -o $@

s/%.s: src/%.c
	cc $(GCC_FLAGS) -S $< -o $@



# Generate dependencies

dep/%.d: src/%.c
	cc $(GCC_FLAGS) $< -MM -MT 'obj/$*.o $@' > $@

dep/%.d: src/%.asm
	nasm $(NASM_FLAGS) $< -M -o 'obj/$*.o $@' > $@

DEPS = $(MODULES:%=dep/%.d)
-include $(DEPS)
