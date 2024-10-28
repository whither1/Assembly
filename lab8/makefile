CC := gcc
CFLAGS := -Wall -m80387 -mno-80387

app.exe : main.o
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.i : %.c
	$(CC) $(CFLAGS) -S $< -o $@
