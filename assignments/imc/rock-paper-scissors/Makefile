CC:=clang++
CFLAGS:=-Wall -Wextra -Werror -Wpedantic -Wno-newline-eof

.PHONY: test
test:
	$(CC) $(CFLAGS) -std=c++17 -o test.o test.cpp
	./test.o

.PHONY: game
game:
	$(CC) $(CFLAGS) -std=c++17 -o game.o main.cpp
	./game.o

.PHONE: fmt
fmt:
	clang-format -i *.cpp

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.dSYM
