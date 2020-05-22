#assemble boot.s file
as --32 boot.s -o boot.o

#compile kernel.c file
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

gcc -m32 -c utils.c -o utils.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

#linking the kernel with kernel.o and boot.o files
ld -m elf_i386 -T linker.ld kernel.o utils.o boot.o -o ourOS.bin -nostdlib

#check ourOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot ourOS.bin

#building the iso file
mkdir -p isodir/boot/grub
cp ourOS.bin isodir/boot/ourOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ourOS.iso isodir

#remove unused file
rm kernel.o
rm utils.o
rm boot.o
rm ourOS.bin

rm -rf isodir

#run it in qemu
qemu-system-x86_64 -cdrom ourOS.iso

#message
echo ">>> Our OS is compiled successfully, located in this folder - ourOS.iso <<<"
