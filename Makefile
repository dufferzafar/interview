default: clean compile run

clean:
	@rm -f *.out

lint:
	@cpplint --filter=-build/namespaces,-whitespace/blank_line,-legal/copyright,-whitespace/line_length $(p).cpp
	@cppcheck -v --enable=style --std=c99 --error-exitcode=1 $(p).cpp

compile:
	@g++ $(p).cpp -o $(p).out

run:
	@./$(p).out
