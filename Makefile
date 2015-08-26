default: clean compile run

clean:
	@rm -f *.out

compile:
	@g++ $(program).cpp -o $(program).out

run:
	@./$(program).out
