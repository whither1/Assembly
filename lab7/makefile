CC := clang
CFLAGS := -Wall 

app.exe : main.o lab7.o
	$(CC) $^ -o $@

lab7.o: lab7.asm
	nasm -f elf64 $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
