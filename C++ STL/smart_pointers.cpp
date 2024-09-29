/*
* What are smart pointers?
* Why do we need them?

* Types
    * unique_ptr
    * shared_ptr
    * weak_ptr

https://lokiastari.com/posts/Smart-Pointer-UniquePointer

Smart Pointers Make Bad APIs https://vector-of-bool.github.io/2018/12/02/smart-pointer-apis.html
An overview on smart pointers https://www.meetingcpp.com/blog/items/an-overview-on-smart-pointers.html
std::shared_ptr - cppreference.com https://en.cppreference.com/w/cpp/memory/shared_ptr

Circular dependency issues with std::shared_ptr, and std::weak_ptr
https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/

Inside STL: Smart pointers - The Old New Thing 
https://devblogs.microsoft.com/oldnewthing/20230814-00/?p=108597

Inside STL: The different types of shared pointer control blocks - The Old New
Thing https://devblogs.microsoft.com/oldnewthing/20230821-00/?p=108626 

Exploring std::shared_ptr | Shahar Mike's Web Spot 
https://shaharmike.com/cpp/shared-ptr/

c++ - To what degree does std::shared_ptr ensure thread-safety? - Stack Overflow
https://stackoverflow.com/questions/9127816/to-what-degree-does-stdshared-ptr-ensure-thread-safety
*/

#include <iostream>
#include <memory>

struct Widget {
  int id;
};

class App {
  Widget *w;
};

int main() {
  // C style
  {
    Widget *w;
    w = new Widget();
    delete w;

    // Forgot to delete
    // Memory Leak

    // Use after free
    delete w;
    w = nullptr;
    std::cout << w->id;

    // Double Delete is Undefined Behaviour
    delete w;
  }

  // C++ style unique
  {
    // Modern C++ Guidelines: never use new / delete in your code
    std::unique_ptr<Widget> w1(new Widget());

    // std::unique_ptr<Widget> w2 = w1;
    // std::unique_ptr<Widget> w5(w1);

    std::unique_ptr<Widget> w3 = std::move(w1);
    std::unique_ptr<Widget> w4(std::move(w1));
  }

  // C++ style shared
  {
    std::shared_ptr<Widget> w1(new Widget());
    std::shared_ptr<Widget> w2 = w1;

    std::shared_ptr<Widget> w3(new Widget());
  }

  {
    int i = 1;
    int j = 0;

    j = i;
    j = std::move(i);

    std::cout << i;
  }

  // RAII
  // Resource Acquisition is Initialization
  // Resource Release is Destruction

  return 0;
}
