# Some C++ 17 features

## if condition with initializer :

- Consider the following code :

    ...
    const auto it = myString.find("Hello");
    if (it != std::string::npos)
    {
        std::cout << it << " Hello\n"
    }
    ...

If we want to limit the scope of it only to the above block we can do

    ...
    {
        const auto it = myString.find("Hello");
        if (it != std::string::npos)
        {
            std::cout << it << " Hello\n"
        }
    }
    ...


- A better solution with C++17 is the following :

    if (const auto it = myString.find("Hello"); it != std::string::npos)
    {
        std::cout << it << " Hello\n";
    }


- Syntax :

    if (T0 x = /* ... */; condition(x))
    {
        // x is in scope here.
    }
    else if (T1 y = /* ... */; condition(y))
    {
        // x and y are in scope here.
    }
    else
    {
        // x and y are in scope here.
    }


- General syntax : if ( init-statement(optional) condition ) statement-true

Rules :
    The init-statement can be either :
    - An expression statement : A non block statement comprising of an expression and a semicolon. This can be empty statement as well.
    - A simple declaration, typically a declaration of a variable with initializer, but it may declare arbitrary many variables.


- Interesting use cases can be lock guards.

    if (std::lock_guard<std::mutex> guard(mtx); !queue.empty())
    {
        queue.pop();
    }

The idea is that the lock will be released immediately after the if block

- This can also be used with Switch case.


## if constexpr

- These are used for compile-time conditional statements.


    template <class T>
    enable_if_t<std::is_same<T, ClassA>::value, bool> someFunction(T a)
    {
        return a.methodA();
    }

    template <class T>
    enable_if_t<is_same<T, ClassB>::value, bool> someFunction(T b)
    {
        return b.methodB();
    }

    template <class T>
    enable_if_t<!std::is_same<T, ClassA>::value &&
                !is_same<T, ClassB>::value, bool>, bool> someFunction(T a)
    {
        return false;
    }


This can be written as :

    template <class T>
    bool someFunction(T a)
    {
        if constexpr (std::is_same<T, ClassA>::value)
        {
            return a.methodA();
        }
        else if constexpr (is_same<T, ClassB>::value)
        {
            return a.methodB();
        }
        else
        {
            return false;
        }
    }

Q Will this function compile if we had used simple "if" instead of "if constexpr"

- Rules : The condition must be a constexpr expression.
- Statements are not instantiated if their branch is not taken.
- There is a variant of "if constexpr" in tde, can check it out...


## Class template parameters type deduction:

- Before C++14, type deduction was only possible with functions :

    template <class T>
    bool someFunction(T b)
    {
        ...
    }

    int x;
    someFunction(x);        // No need for someFunction<int>(x)

The same could not be done for class template parameters. Now it is allowed :

    Before C++17 :

        std::vector<int> v{1, 2};

    After C++17 :

        std::vector v1{1, 2};


- But use carefully :
    std::vector v1{1, 2};
    std::vector v2{v1};     // std::vector<int>
    std::vector v3{v1, v2}; // std::vector<std::vector<int>>

Quote from cppreference : When initializing from a single argument of a type that
is a specialization of the class template at issue, copying deduction is generally
preferred over wrapping by default


- This is only performed if no template arguments are provided. It is not allowed
to do something similar to partial specialization :

        std::tuple<int> t(0, 1)


## Inline Variables

- Variables can now be declared inline just like functions.

Before C++17 :
    // In header (.h):
    extern bool ready;

    // In source file (.cpp):
    bool ready = false;

After C++17 :
    // In header
    inline bool ready = false;

- Similarly for static variables :

Before C++17 :
    // In header (.h):
    struct system
    {
        static bool ready;
    };

    // In source file (.cpp):
    bool system::ready = false;

After C++17 :

    // In header
    struct system
    {
        inline static bool ready = false;
    };


- Some rules for inline variables:
    - They may be defined in more than one translation unit as long as the
    definitions are identical.
    - The definition must be present in a translation unit that accesses an
    inline variable.
    - A static constexpr member variable is implicitly inline.

## Return Value Optimization

- With C++17, return value optimization (RVO) is mandatory.

- For example, before C++17, the following function f() might fail from compiling :

    struct Foo {
      Foo() { std::cout << "Constructed" << std::endl; }
      Foo(const Foo &) = delete;
      Foo(const Foo &&) = delete;
      ~Foo() { std::cout << "Destructed" << std::endl; }
    };

    Foo f() {
      return Foo();
    }

    int main() {
      Foo foo = f();
    }

After C++17, it will not.

- Named Return Value Optimization (NRVO) is still not mandatory:

    Foo f()
    {
        Foo x;
        return x;
    }


Nested Namespaces
-------------------------------------------------
if condition with initializer :
-------------------------------

- Consider the following code :

    ...
    const auto it = myString.find("Hello");
    if (it != std::string::npos)
    {
        std::cout << it << " Hello\n"
    }
    ...

If we want to limit the scope of it only to the above block we can do

    ...
    {
        const auto it = myString.find("Hello");
        if (it != std::string::npos)
        {
            std::cout << it << " Hello\n"
        }
    }
    ...


- A better solution with C++17 is the following :

    if (const auto it = myString.find("Hello"); it != std::string::npos)
    {
        std::cout << it << " Hello\n";
    }


- Syntax :

    if (T0 x = /* ... */; condition(x))
    {
        // x is in scope here.
    }
    else if (T1 y = /* ... */; condition(y))
    {
        // x and y are in scope here.
    }
    else
    {
        // x and y are in scope here.
    }


- General syntax : if ( init-statement(optional) condition ) statement-true

Rules :
    The init-statement can be either :
    - An expression statement : A non block statement comprising of an expression and a semicolon. This can be empty statement as well.
    - A simple declaration, typically a declaration of a variable with initializer, but it may declare arbitrary many variables.


- Interesting use cases can be lock guards.

    if (std::lock_guard<std::mutex> guard(mtx); !queue.empty())
    {
        queue.pop();
    }

The idea is that the lock will be released immediately after the if block

- This can also be used with Switch case.


------------
if constexpr
------------

- These are used for compile-time conditional statements.


    template <class T>
    enable_if_t<std::is_same<T, ClassA>::value, bool> someFunction(T a)
    {
        return a.methodA();
    }

    template <class T>
    enable_if_t<is_same<T, ClassB>::value, bool> someFunction(T b)
    {
        return b.methodB();
    }

    template <class T>
    enable_if_t<!std::is_same<T, ClassA>::value &&
                !is_same<T, ClassB>::value, bool>, bool> someFunction(T a)
    {
        return false;
    }


This can be written as :

    template <class T>
    bool someFunction(T a)
    {
        if constexpr (std::is_same<T, ClassA>::value)
        {
            return a.methodA();
        }
        else if constexpr (is_same<T, ClassB>::value)
        {
            return a.methodB();
        }
        else
        {
            return false;
        }
    }

Q Will this function compile if we had used simple "if" instead of "if constexpr"

- Rules : The condition must be a constexpr expression.
- Statements are not instantiated if their branch is not taken.
- There is a variant of "if constexpr" in tde, can check it out...


----------------------------------------
Class template parameters type deduction:
----------------------------------------

- Before C++14, type deduction was only possible with functions :

    template <class T>
    bool someFunction(T b)
    {
        ...
    }

    int x;
    someFunction(x);        // No need for someFunction<int>(x)

The same could not be done for class template parameters. Now it is allowed :

    Before C++17 :

        std::vector<int> v{1, 2};

    After C++17 :

        std::vector v1{1, 2};


- But use carefully :
    std::vector v1{1, 2};
    std::vector v2{v1};     // std::vector<int>
    std::vector v3{v1, v2}; // std::vector<std::vector<int>>

Quote from cppreference : When initializing from a single argument of a type that
is a specialization of the class template at issue, copying deduction is generally
preferred over wrapping by default


- This is only performed if no template arguments are provided. It is not allowed
to do something similar to partial specialization :

        std::tuple<int> t(0, 1)


----------------
Inline Variables
----------------

- Variables can now be declared inline just like functions.

Before C++17 :
    // In header (.h):
    extern bool ready;

    // In source file (.cpp):
    bool ready = false;

After C++17 :
    // In header
    inline bool ready = false;

- Similarly for static variables :

Before C++17 :
    // In header (.h):
    struct system
    {
        static bool ready;
    };

    // In source file (.cpp):
    bool system::ready = false;

After C++17 :

    // In header
    struct system
    {
        inline static bool ready = false;
    };


- Some rules for inline variables:
    - They may be defined in more than one translation unit as long as the
    definitions are identical.
    - The definition must be present in a translation unit that accesses an
    inline variable.
    - A static constexpr member variable is implicitly inline.

--------------------------
Return Value Optimization
--------------------------

- With C++17, return value optimization (RVO) is mandatory.

- For example, before C++17, the following function f() might fail from compiling :

    struct Foo {
      Foo() { std::cout << "Constructed" << std::endl; }
      Foo(const Foo &) = delete;
      Foo(const Foo &&) = delete;
      ~Foo() { std::cout << "Destructed" << std::endl; }
    };

    Foo f() {
      return Foo();
    }

    int main() {
      Foo foo = f();
    }

After C++17, it will not.

- Named Return Value Optimization (NRVO) is still not mandatory:

    Foo f()
    {
        Foo x;
        return x;
    }

------------------
Nested Namespaces
------------------

- Before C++17

    namespace A
    {

    namespace B
    {

    namespace C
    {

    // ...

    }
    }
    }

- After C++17

    namespace A::B::C
    {

    // ...

    }


------------
String Views
------------

- A light weight non-owning view of a string.

- Example :

Before C++17 :

    std::string first_3(std::string const& s)
    {
        if (s.size() < 3)
            return s;

        return s.substr(0, 2);
        // Expensive copy, may not allocate because of small string optimization
    }

    if (first_3("ABCDEFG") == "ABC")
        // ...

After C++17 :

    std::string_view first_3(std::string_view s)
    {
        if (s.size() < 3)
            return s;
        return s.substr(0, 3); // Cheap copy, interface similar to std::string
    }

    if (first_3("ABCDEFG") == "ABC")
        // ...


- The interface is similar to std::string.
- Overall string_view consists of a pointer to a char array and a length, and a
lot of member functions
- Since string_view does not own the string, cannot change the string.
- It is a pointer and a length, so if the underlying string is deallocated, then
we have dangling pointers. For example, if the underlying string is moved to a
new location, string view would not see that.
- If the string size increases, then string view would not see that and length
would not change.
- So I think this is just a good replacement for "const char*"

- Allowed implicit conversions

    const char* -> std::string_view : OK
    std::string -> std::string_view : OK
    std::string_view -> std::string : NOPE

The problem is that std::string_view -> std::string would makes a copy of the
underlying memory, complete with heap allocation, whereas the implicit
std::string -> std::string_view  need not. Hence, the conversion is not implicit
in the standards.

So given the above rules, string_view can be helpful in following cases :

Before C++17 :

    void to_int(const std::string& x)
    {
        // ..
    }

    void to_int(const char* x)
    {
        // ..
    }

We need to declare two overloads for such functions.

After C++17 :

    void to_int(std::string_view x)
    {
        ..

        // When calling this function with const char*, would lead to an additional call of ::strlen()
    }


--------
Optional
--------

- Consider the case where you have to return a value in case of success and false
in case  of failure. One way is to return std::pair<T,bool>.
Optional is more readable, easier to construct alternative where the intent would be
expressed explicitly.

    std::optional<std::long> tolong(std::string_view s)
    {
        std::optional<long> oi;
        char* p;
        long converted = strtol(s, &p, 10);
        if (*p == nullptr)
        {
            oi = converted
        }
        else
        {
            // conversion failed because the input wasn't a number
        }
        return oi;
    }


Reference : long int strtol (const char* str, char** endptr, int base);
    endptr : Reference to an object of type char*, whose value is set by
             the function to the next character in str after the numerical value.


- Checking an optional value is very easy :

    std::optional<std::long> x = tolong("1234");
    if (x)
    {
        std::cout << x.value();
        x.reset();
    }


- std::optional acts like a pointer (it also has operator-> and operator*) but
it owns its contents.
- Also, there is no heap allocation, the memory is allocated on stack and just
constructed when required.Advantage is that : If we had something other than
long such that it was not default constructible, the above example would still
be correct. This would not have been possible with std::pair<T, bool>.


-------
Variant
-------

- The class template std::variant represents a type-safe union.
For example, you might have done something like this earlier

    struct Order { int price; int qty; };
    struct Heartbeat { int nonce; };

    enum MsgType { ORDER, HB};
    struct MsgStruct
    {
        union Msg{ Order o; Heartbeat h; };
        Msg m;
        MsgType type;
    };

Variant provides alternative to that.
    std::variant<Order, Heartbeat> msg;


- An instance of std::variant at any given time either holds a value of one of
its alternative types.

    std::variant<int, std::string> v = "abc";
    if (std::holds_alternative<std::string>(v))
    {
        std::cout << "Contains : " << std::get<std::string>(v) << std::endl;
    }

    // std::get throws exception if not the same type, alternative : std::get_if

    v = 12;
    if(int* ptr = std::get_if<int>(&v); ptr)
    {
        std::cout << "Contains: " << *ptr << std::endl;

    }
    else
      std::cout << "failed to get value!" << '\n';

 - Consistent with the behavior of unions, a default-constructed variant holds a
value of its first alternative, unless that alternative is not
default-constructible (in which case the variant is not default-constructible
either).

- Similar to unions, variants owns the contents and have no heap allocations.

- An interesting application can be type safe heterogenous containers.

   std::vector<ExchangeMsg>     vs      std::vector<std::variant<Order, Heartbeat>>



---------------------
Structured Bindings :
---------------------

Structured bindings binds the specified names to subobjects or elements of the initializer :
For example, it gives you the freedom to do the following :

    double myArray[3] = { 1.0, 2.0, 3.0 };
    auto [a, b, c] = myArray;

So a, b and c will be copies of the elements. Hence, type deduction rules with
auto are same.

    std::tuple<double, double, int> t = // ...
    auto [x, y, z] = t;

Simplified Rules for a class to allow structured bindings :
- Either all non-static data members:
    Must be public.
    Must be direct members of the type or members of the same public base class.
- Or the type has an obj.get<N> method, like tuple or pair, etc.

Hence we can also use structured bindings with structs :

    struct Point
    {
        int x;
        int y;
    };

    Point p = { 1,2 };
    auto [ x_coord, y_coord ] = p;


Best use case :

    template <typename Key, typename Value>
    void update(std::map<Key, Value>& m)
    {
        for (const auto& [key, value] : m)
        {
            // .. //
        }
    }

- There cannot be a partial match with structured bindings, which was possible with std::tie. Example

    std::tuple<int, int, float, int> g();
    std::tie(a, b, std::ignore, c) = g();

From what I could understand, no strong reason but convention is not fixed for now. Following answer
discusses the same : https://stackoverflow.com/questions/40673080/stdignore-with-structured-bindings

-------------------
Interesting reads :
-------------------
- Constexpr lambdas
- Filesystem support
- std::in_place

Reference for C++ features : https://github.com/AnthonyCalandra/modern-cpp-features

- Before C++17

    namespace A
    {

    namespace B
    {

    namespace C
    {

    // ...

    }
    }
    }

- After C++17

    namespace A::B::C
    {

    // ...

    }


------------
String Views
------------

- A light weight non-owning view of a string.

- Example :

Before C++17 :

    std::string first_3(std::string const& s)
    {
        if (s.size() < 3)
            return s;

        return s.substr(0, 2);
        // Expensive copy, may not allocate because of small string optimization
    }

    if (first_3("ABCDEFG") == "ABC")
        // ...

After C++17 :

    std::string_view first_3(std::string_view s)
    {
        if (s.size() < 3)
            return s;
        return s.substr(0, 3); // Cheap copy, interface similar to std::string
    }

    if (first_3("ABCDEFG") == "ABC")
        // ...


- The interface is similar to std::string.
- Overall string_view consists of a pointer to a char array and a length, and a
lot of member functions
- Since string_view does not own the string, cannot change the string.
- It is a pointer and a length, so if the underlying string is deallocated, then
we have dangling pointers. For example, if the underlying string is moved to a
new location, string view would not see that.
- If the string size increases, then string view would not see that and length
would not change.
- So I think this is just a good replacement for "const char*"

- Allowed implicit conversions

    const char* -> std::string_view : OK
    std::string -> std::string_view : OK
    std::string_view -> std::string : NOPE

The problem is that std::string_view -> std::string would makes a copy of the
underlying memory, complete with heap allocation, whereas the implicit
std::string -> std::string_view  need not. Hence, the conversion is not implicit
in the standards.

So given the above rules, string_view can be helpful in following cases :

Before C++17 :

    void to_int(const std::string& x)
    {
        // ..
    }

    void to_int(const char* x)
    {
        // ..
    }

We need to declare two overloads for such functions.

After C++17 :

    void to_int(std::string_view x)
    {
        ..

        // When calling this function with const char*, would lead to an additional call of ::strlen()
    }


--------
Optional
--------

- Consider the case where you have to return a value in case of success and false
in case  of failure. One way is to return std::pair<T,bool>.
Optional is more readable, easier to construct alternative where the intent would be
expressed explicitly.

    std::optional<std::long> tolong(std::string_view s)
    {
        std::optional<long> oi;
        char* p;
        long converted = strtol(s, &p, 10);
        if (*p == nullptr)
        {
            oi = converted
        }
        else
        {
            // conversion failed because the input wasn't a number
        }
        return oi;
    }


Reference : long int strtol (const char* str, char** endptr, int base);
    endptr : Reference to an object of type char*, whose value is set by
             the function to the next character in str after the numerical value.


- Checking an optional value is very easy :

    std::optional<std::long> x = tolong("1234");
    if (x)
    {
        std::cout << x.value();
        x.reset();
    }


- std::optional acts like a pointer (it also has operator-> and operator*) but
it owns its contents.
- Also, there is no heap allocation, the memory is allocated on stack and just
constructed when required.Advantage is that : If we had something other than
long such that it was not default constructible, the above example would still
be correct. This would not have been possible with std::pair<T, bool>.


-------
Variant
-------

- The class template std::variant represents a type-safe union.
For example, you might have done something like this earlier

    struct Order { int price; int qty; };
    struct Heartbeat { int nonce; };

    enum MsgType { ORDER, HB};
    struct MsgStruct
    {
        union Msg{ Order o; Heartbeat h; };
        Msg m;
        MsgType type;
    };

Variant provides alternative to that.
    std::variant<Order, Heartbeat> msg;


- An instance of std::variant at any given time either holds a value of one of
its alternative types.

    std::variant<int, std::string> v = "abc";
    if (std::holds_alternative<std::string>(v))
    {
        std::cout << "Contains : " << std::get<std::string>(v) << std::endl;
    }

    // std::get throws exception if not the same type, alternative : std::get_if

    v = 12;
    if(int* ptr = std::get_if<int>(&v); ptr)
    {
        std::cout << "Contains: " << *ptr << std::endl;

    }
    else
      std::cout << "failed to get value!" << '\n';

 - Consistent with the behavior of unions, a default-constructed variant holds a
value of its first alternative, unless that alternative is not
default-constructible (in which case the variant is not default-constructible
either).

- Similar to unions, variants owns the contents and have no heap allocations.

- An interesting application can be type safe heterogenous containers.

   std::vector<ExchangeMsg>     vs      std::vector<std::variant<Order, Heartbeat>>



---------------------
Structured Bindings :
---------------------

Structured bindings binds the specified names to subobjects or elements of the initializer :
For example, it gives you the freedom to do the following :

    double myArray[3] = { 1.0, 2.0, 3.0 };
    auto [a, b, c] = myArray;

So a, b and c will be copies of the elements. Hence, type deduction rules with
auto are same.

    std::tuple<double, double, int> t = // ...
    auto [x, y, z] = t;

Simplified Rules for a class to allow structured bindings :
- Either all non-static data members:
    Must be public.
    Must be direct members of the type or members of the same public base class.
- Or the type has an obj.get<N> method, like tuple or pair, etc.

Hence we can also use structured bindings with structs :

    struct Point
    {
        int x;
        int y;
    };

    Point p = { 1,2 };
    auto [ x_coord, y_coord ] = p;


Best use case :

    template <typename Key, typename Value>
    void update(std::map<Key, Value>& m)
    {
        for (const auto& [key, value] : m)
        {
            // .. //
        }
    }

- There cannot be a partial match with structured bindings, which was possible with std::tie. Example

    std::tuple<int, int, float, int> g();
    std::tie(a, b, std::ignore, c) = g();

From what I could understand, no strong reason but convention is not fixed for now. Following answer
discusses the same : https://stackoverflow.com/questions/40673080/stdignore-with-structured-bindings

-------------------
Interesting reads :
-------------------
- Constexpr lambdas
- Filesystem support
- std::in_place

Reference for C++ features : https://github.com/AnthonyCalandra/modern-cpp-features
