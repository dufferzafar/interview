/**
Curiously Recurring Template Pattern (CRTP) 
A class X derives from a class template instantiation using X itself as template argument. 

This pattern is used to achieve static polymorphism in C++.
*/

#include <iostream>

template <typename T>
class Base {
    T* getDerived() {
        return static_cast<T*>(this);
    }

    void print() {
        static_cast<T*>(this)->print();
    }
};

class Derived : Base<Derived> {
public:
    void print() {
        std::cout << "Derived" << std::endl;
    }
};

int main() {
    Derived d;
    d.print();


    Base b = d;
    b->print();

    return 0;
}
