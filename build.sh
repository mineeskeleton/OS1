nasm -f elf32 boot.asm -o boot.o
gcc -m32 -c -fno-stack-protector kernel.c -o kernel.o
gcc -m32 -c -fno-stack-protector ./src/print.c -o ./src/print.o
gcc -m32 -c -fno-stack-protector ./src/input.c -o ./src/input.o
gcc -m32 -c -fno-stack-protector ./src/string.c -o ./src/string.o
ld -m elf_i386 -T link.ld -o ./bin/kernel.bin boot.o kernel.o ./src/print.o ./src/input.o ./src/string.o
qemu-system-x86_64 -kernel ./bin/kernel.bin