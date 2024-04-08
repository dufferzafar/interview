CC:=/usr/bin/clang++
FILE:=ConcurrentQueue.cpp

.PHONY: queue
queue:
	$(CC) -g -std=c++11 $(FILE) -o queue.o -pthread
	./queue.o

.PHONY: tsan
tsan:
	$(CC) -g -std=c++11 $(FILE) -fsanitize=thread -fPIE -o queue.o -pthread
	./queue.o

.PHONY: asan
asan:
	$(CC) -g -std=c++11 $(FILE) -fsanitize=address -fno-omit-frame-pointer  -o queue.o -pthread
	./queue.o

.PHONY: ubsan
ubsan:
	$(CC) -g -std=c++11 $(FILE) -fsanitize=undefined -fno-omit-frame-pointer  -o queue.o -pthread
	./queue.o
