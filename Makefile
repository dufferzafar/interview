ifndef p
$(error Specify a program to build)
endif

EXE = $(patsubst %.cpp,%.out,$(patsubst %.c,%.out,$(p)))

default: clean compile run

clean:
	@rm -f *.out

lint:
	@cpplint --filter=-build/namespaces,-whitespace/blank_line,-legal/copyright,-whitespace/line_length $(p)
	@cppcheck -v --enable=style --std=c99 --error-exitcode=1 $(p)

# -fdiagnostics-color=always
compile:
	@g++ -Wall $(p) -o $(EXE)

run:
	@./$(EXE)
