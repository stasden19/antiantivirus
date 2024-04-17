all: elf.c main.c upx_start.asm upx_end.asm
		nasm -f elf64 upx_start.asm
		nasm -f elf64 upx_end.asm
		gcc -o main.exe upx_start.o main.c upx_end.o
		gcc -o elf.exe elf.c
		g++ code.cpp -o code

clean:
		rm -f *.exe *.o

