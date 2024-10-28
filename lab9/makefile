CC := g++
CFLAGS := -Wall

app.exe : main.o my_matrix.o
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

