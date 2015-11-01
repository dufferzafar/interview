default: clean lint compile run

clean:
	@rm -f *.out

lint:
	@cpplint --filter=-build/namespaces,-whitespace/blank_line,-legal/copyright,-whitespace/line_length $(program).cpp
	@cppcheck -v --enable=style --std=c99 --error-exitcode=1 $(program).cpp

compile:
	@g++ $(program).cpp -o $(program).out

run:
	@./$(program).out
