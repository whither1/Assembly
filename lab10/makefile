CC := g++
CFLAGS := -Wall

app.exe : main.o
	gcc main.o -L/usr/lib/x86_64-linux-gnu $(pkg-config --libs gtk+-3.0) -o app.exe -no-pie

main.o : main.asm2
	nasm -f elf64 -o main.o main.asm
