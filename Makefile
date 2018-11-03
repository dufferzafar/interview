EXE = $(patsubst %.cpp,%.out,$(patsubst %.c,%.out,$(p)))

ifeq ($(suffix $(p)),.c)
	CLANG = 'clang'
	GCC = 'gcc'
else
	CLANG = 'clang++'
	CLANG = 'g++'
endif

default: clean compile run

clean:
	@rm -f *.out

lint:
	@cpplint --filter=-build/namespaces,-whitespace/blank_line,-legal/copyright,-whitespace/line_length $(p)
	@cppcheck -v --enable=style --std=c99 --error-exitcode=1 $(p)

compile:
	@$(CLANG) -g -Wall $(p) -o $(EXE)

gcc:
	@$(GCC) -g -Wall $(p) -o $(EXE)

run: compile
	@./$(EXE)

# TODO: Bash function
# cpp <*.cpp> <input_file>
