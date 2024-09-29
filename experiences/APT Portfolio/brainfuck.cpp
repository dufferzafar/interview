#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Brainfuck {
public:
  Brainfuck(const std::string &code, const std::string &inputFile)
      : code(code), input(inputFile), memory(30000, 0) {
    loadInput();
  }

  void interpret() {
    while (ip < code.size()) {
      char command = code[ip];
      switch (command) {
      case '>':
        ++dp;
        break;
      case '<':
        --dp;
        break;
      case '+':
        ++memory[dp];
        break;
      case '-':
        --memory[dp];
        break;
      case '.':
        std::cout << memory[dp];
        break;
      case ',':
        if (inputStream) {
          char inputChar;
          inputStream.get(inputChar);
          memory[dp] = static_cast<unsigned char>(inputChar);
        }
        break;
      case '[':
        if (memory[dp] == 0) {
          jumpForward();
        } else {
          loopStack.push(ip);
        }
        break;
      case ']':
        if (memory[dp] != 0) {
          ip = loopStack.top();
        } else {
          loopStack.pop();
        }
        break;
      default:
        break;
      }
      ++ip;
    }
  }

private:
  void loadInput() {
    inputStream.open(input);
    if (!inputStream) {
      std::cerr << "Error opening input file: " << input << std::endl;
    }
  }

  void jumpForward() {
    int nestedLoops = 1;
    while (nestedLoops > 0 && ++ip < code.size()) {
      if (code[ip] == '[')
        ++nestedLoops;
      if (code[ip] == ']')
        --nestedLoops;
    }
  }

  std::string code;
  std::string input;
  std::vector<unsigned char> memory;
  
  std::size_t ip{0}; // instruction pointer
  std::size_t dp{0}; // data pointer
  
  std::stack<std::size_t> loopStack;
  std::ifstream inputStream;
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
    return 1;
  }

  std::string code;
  while (std::cin) {
    std::string line;
    std::getline(std::cin, line);
    code += line;
  }

  Brainfuck BF(code, argv[1]);
  BF.interpret();

  return 0;
}
