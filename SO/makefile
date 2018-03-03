edit: compile link clear

compile: start.asm main.c scrn.c
	nasm -f aout -o start.o start.asm
	gcc -m32 -Wall -O -fstrength-reduce -fno-pie -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o main.o main.c
	gcc -m32 -Wall -O -fstrength-reduce -fno-pie -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o scrn.o scrn.c

link: link.ld start.o main.o scrn.o
	ld -T link.ld -o kernel.bin start.o main.o scrn.o  -melf_i386

clear: start.o main.o scrn.o
	rm start.o
	rm main.o
	rm scrn.o

clean:
	rm start.o
	rm main.o
	rm scrn.o
	rm kernel.bin
