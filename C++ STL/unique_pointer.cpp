/*
https://lokiastari.com/posts/Smart-Pointer-UniquePointer


*/

#include <cstddef>
#include <memory>
#include <iostream>

namespace my
{
    template <typename T>
    class unique_ptr {
        T* ptr;

        public:

        unique_ptr() : ptr{nullptr} { }
        // unique_ptr(std::nullptr_t) : ptr{nullptr} { }
        unique_ptr(T *p) : ptr(p) { }
        ~unique_ptr() {
            delete ptr;
        }

        // Rule of Zero
        // Simple data types

        // Constructor
        // Destructor
        // Copy Constructor
        // Copy Assignment Operator
        // Move Constructor
        // Move Assignment Operator

        // Rule of Three

        // Rule of Five

        [[nodiscard]] T *get() { return ptr; }

        [[nodiscard]] T* release()
        {
            T* t = ptr;
            ptr = nullptr;
            return t;
        }

        void swap(unique_ptr<T>& rhs)
        {
            std::swap(ptr, rhs.ptr);
        }

        void reset(T* p = nullptr)
        {
            delete ptr;
            ptr = p;
        }

        // if (p) {}
        operator bool() const
        {
            return ptr != nullptr;
        }

        // Overload the arrow operator
        T* operator->() { return get(); }

        // Overload the dereference operator
        T& operator*() { return *get(); }

        // Move constructor
        unique_ptr(unique_ptr&& rhs)
        {
            reset(rhs.release());
        }

        // Move assignment
        unique_ptr& operator=(unique_ptr&& rhs)
        {
            reset(rhs.release());
            return *this;
        }

        // Why were these needed?
        unique_ptr& operator=(std::nullptr_t)
        {
            reset(nullptr);
            return *this;
        }

        // Copy constructor
        unique_ptr(const unique_ptr&) = delete;

        // Copy assignment
        unique_ptr& operator=(const unique_ptr&) = delete;
    };

    template <typename T, typename ...Args>
    unique_ptr<T> make_unique(Args ...args)
    {
        return unique_ptr<T>(new T(args...));
    }
}

int ours()
{
    using namespace my;

    int i = 0;

    unique_ptr<int> p(&i);

    // std::cout << "Value of int is: " << *p; 

    unique_ptr<int> x{&i};

    unique_ptr<int> y(new int(19));

    unique_ptr<int> z = &i;

    unique_ptr<int> q;
    // q = p;
    q = std::move(p);

    auto t = make_unique<int>(9);
    std::cout << *(p.get());
    std::cout << *p;
    
    static_cast<void>(p.release());

    p.reset();
    p.reset(&i);

    p = nullptr;

    return 0;
}

int theirs()
{
    using namespace std;

    // auto p = make_unique<int>(9);

    int i = 0;
    unique_ptr<int> p(&i);
    unique_ptr<int> x{&i};
    unique_ptr<int> y{nullptr};

    unique_ptr<int> q = std::move(p);

    std::cout << *(p.get());
    std::cout << *p;
    p.release();

    p = nullptr;

    p.reset();
    p.reset(&i);
}
