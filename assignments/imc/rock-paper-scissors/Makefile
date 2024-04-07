CC:=clang++
CFLAGS:=-Wall -Wextra -Werror -Wpedantic -Wno-newline-eof

.PHONY: game
game:
	$(CC) $(CFLAGS) -std=c++17 -o game.o game.cpp
	./game.o

# LLVM, GNU, Google, Chromium, Microsoft, Mozilla, WebKit.
.PHONE: fmt
fmt:
	clang-format -i *.cpp

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.dSYM
