CC = gcc
CFLAGS = -O3 -Wall -Werror

all: test

test: test.o bloomflt.o hash.o
	$(CC) $+ -o test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o test

.PHONY: clean
.SILENT: clean
