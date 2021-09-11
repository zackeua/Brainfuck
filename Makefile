CC1 = clang
CC2 = gcc
CFLAGS = -Ofast -g -Wall -Werror
EXECUTABLE1 = brainlang
EXECUTABLE2 = gbrain
CODE = brainfuck.c
all:$(EXECUTABLE1)

$(EXECUTABLE1): $(CODE)
	$(CC1) $(CFLAGS) -o $(EXECUTABLE1) $(CODE)

$(EXECUTABLE2): $(CODE)
	$(CC2) $(CFLAGS) -o $(EXECUTABLE1) $(CODE)

clean:
	rm $(EXECUTABLE1)
	rm $(EXECUTABLE2)
