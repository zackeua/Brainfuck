CC1 = clang
CC2 = gcc
HASKELLC = ghc
CFLAGS = -Ofast -g -Wall -Werror
HASKELLFLAGS = -O
C_EXEC1 = brainlang
C_EXEC2 = gbrain
HASKELL_EXEC = haskellfuck
C_CODE = brainfuck.c
HASKELL_CODE = brainfuck.hs
all:$(C_EXEC1)

c:$(C_EXEC1)

haskell:$(HASKELL_EXEC)

$(C_EXEC1): $(C_CODE)
	$(CC1) $(CFLAGS) -o $(C_EXEC1) $(C_CODE)

$(C_EXEC2): $(C_CODE)
	$(CC2) $(CFLAGS) -o $(C_EXEC2) $(C_CODE)

$(HASKELL_EXEC): $(HASKELL_CODE)
	$(HASKELLC) $(HASKELLFLAGS) -o $(HASKELL_EXEC) $(HASKELL_CODE)

clean:
	rm -r $(C_EXEC1)
	rm -r $(C_EXEC2)
	rm -r $(HASKELL_EXEC)
	rm *.hi
	rm *.o
