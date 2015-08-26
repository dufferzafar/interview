default: clean compile run

clean:
	@rm -f *.out

compile:
	@g++ -std=c++11 $(program).cpp -o $(program).out

run:
	@./$(program).out
