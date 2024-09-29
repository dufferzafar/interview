#include <iostream>
#include <typeindex>

class Any
{
private:
    void* ptr;
    std::type_index idx;
    int sz;

public:
    ~Any()
    {
        for (int i = 0; i < sz; ++i)
        {
            delete (i + static_cast<char*>(ptr));
        }
    }

    template <typename T>
    Any(T val) : idx{std::type_index(typeid(T))}
    {
        sz = sizeof(T);
        ptr = new T(val);
    }

    template <typename X>
    X Get()
    {
      if (std::type_index(typeid(X)) == idx)
        return *(static_cast<X*>(ptr));
      else
      {
        std::cout << idx.name() << " != " << std::type_index(typeid(X)).name() << std::endl;
        throw std::runtime_error("Type mismatch");
      }
    }
};

int main()
{
    Any a(89);
    
    std::cout << a.Get<int>() << std::endl;
    std::cout << Any(std::string("Shadab Zafar")).Get<const char*>() << std::endl;

    return 0;
}
