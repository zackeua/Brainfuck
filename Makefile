CC1 = clang
CC2 = gcc
HASKELLC = ghc
RUSTCC = rustc
CCP = clang++

CFLAGS = -Ofast -g -Wall -Werror
HASKELLFLAGS = -O2


C_EXEC1 = brainlang
C_EXEC2 = gbrain
HASKELL_EXEC = haskellfuck
RUST_EXEC = rustybrain
CPP_EXEC = cppbrain

C_CODE = brainfuck.c
HASKELL_CODE = brainfuck.hs
CPP_CODE = brainfuck.cpp

all: c haskell rust 

c:$(C_EXEC1)

haskell:$(HASKELL_EXEC)

cpp:$(CPP_EXEC)

$(C_EXEC1): $(C_CODE)
	$(CC1) $(CFLAGS) -o $(C_EXEC1) $(C_CODE)

$(C_EXEC2): $(C_CODE)
	$(CC2) $(CFLAGS) -o $(C_EXEC2) $(C_CODE)

$(HASKELL_EXEC): $(HASKELL_CODE)
	$(HASKELLC) $(HASKELLFLAGS) -o $(HASKELL_EXEC) $(HASKELL_CODE)

$(CPP_EXEC): $(CPP_CODE)
	$(CCP) $(CFLAGS) -o $(CPP_EXEC) $(CPP_CODE)

clean:
	rm -r $(C_EXEC1) $(C_EXEC2) $(HASKELL_EXEC) *.hi *.o 
