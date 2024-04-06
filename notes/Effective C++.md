This page contains notes for the book Effective C++: 55 Specific Ways to Improve Your Programs and Designs by Scott Meyers.

## Describe the use cases of static in C++.

    Static keyword is used in the following scenarios:

    - Static variables when declared in functions to retain the value during multiple invocations.
    - A static member variable of a class has the same value in any instance of the class and doesn't even require an instance of the class to exist. It can simply be referred using the class name  (`class_name::x;` rather than `instance_of_class.x;`).

            class user {
              private:
                static int next_id;
              ..
            };

            int user::next_id = 0;

        This is how you initialize a static data memeber.

    -  Static member functions are functions that do not require an instance of the class, and can be  called the same way you access static member variables - with the class name. For example , `a_class::static_function();` rather than `an_instance.function();`. Static member functions can only operate on static members, as they do not belong to specific instances of a class.


## When is memory allotted to `static` variables in C++?

    Memory is allocated to both static and global variables at program startup, and they live until the program ends. They cannot be "freed" or "reallocated".


## What is the difference between `global` and `static global` variables?

    The global variable has global scope. Global variables can be accessed using the `extern` keyword., whereas static variable has file scope, it is not possible to access the variable from any other file.

## Consider the following code :

        class Test {
            const int size = 100;
            int arr[size];          // Gives an error
        };

    <Qu> How will you correct the above error?

     The error is in the second statement and not the first statement. The first statement compiles well with C++11.

    - Using the **enum hack** : an enumeration must have all its values established at compile time, it’s local to the class, and its values can be used wherever an int is expected.

            class Bunch {
                enum { size = 1000 };
                int arr[size];
            };

    - Inside the class, you can initialize like this

            static const int size = 100; //at declaration

        Only the modern compilers allow this, and that too for static constant integers.


## Why should constants be preferred over `#define`?

    - When you do something like this,

            #define ASPECT_RATIO 1.653

        the symbolic name ASPECT_RATIO may never be seen by compilers; it may be removed by the preprocessor before the source code ever gets to a compiler.  This can be confusing if you get an error during compilation involving the use of the constant, because the error message may refer to 1.653, not ASPECT_RATIO.

        The solution is to replace the macro with a constant:

            const double AspectRatio = 1.653;

    - \#defines don’t respect scope. Once a macro is defined, it’s in force for the rest of the compilation (unless it's #undefed somewhere along the line). Which means that not only can’t #defines be used for class-specific constants, they also can’t be used to provide any kind of encapsulation, i.e., there is no such thing as a “private” #define, whereas const data members can be encapsulated (as done in the previous problem).

## What are the  problems with the following code?

        #define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

    <Qu> And how will you solve them?

    Whenever we write this kind of macro, we have to parenthesize all the arguments in the macro body (as done above), otherwise we can run into trouble when somebody calls the macro with an expression.
But even if we get that right, weird things can happen:

        int a = 5, b = 0;
        CALL_WITH_MAX(++a, b); // a is incremented twice

    We can solve these problems using inline templates :

        template<typename T>
        inline void callWithMax(const T& a, const T& b) {
            f(a > b ? a : b);
        }

    Since we don’t know what T is, we prefer passing by reference.


## What is the difference between `const type * ptr` and `type const * ptr`?

    They are the same, no difference.

## What is the difference between `const std::vector<int>::iterator` and `std::vector<int>::const_iterator`?

    STL iterators are modeled on pointers, so an iterator acts much like a T* pointer. The difference is similar to constant pointer vs pointer to a constant.

        std::vector<int> vec;

        const std::vector<int>::iterator iter = vec.begin();
        *iter = 10;     // Fine
        ++iter;         // Error

        std::vector<int>::const_iterator cIter = vec.begin();
        *cIter = 10;    // Error
        ++cIter;        // Fine


## What is the difference between *bitwise constness* (also known as physical constness) and *logical constness*? What does mutable keyword do in C++?

    Bitwise constness is C++’s definition of constness, where a const member function isn’t allowed to modify any of the non-static data members of the object on which it is invoked.
    Unfortunately, many member functions that don’t act very const pass the bitwise test. In particular, a member function that modifies what a pointer points to (without actually modifying the pointer) frequently doesn’t act const.

     For example, suppose we have a TextBlock-like class that stores its data as a *char** instead of a string

        class TextBlock {
            char m_data10];

          public:
            TextBlock(const char* data) {
                strcpy(m_data, data);
            }

            char& operator[](std::size_t position) const { return m_data[position]; }   // Bitwise const
        };

        const TextBlock x("Hello"); // declare constant object
        char *ptr = &x[0];          // call the const operator[]
        *ptr = ’J’;                         // cctb now has the value “Jello”

    Thus there is something incomplete with bitwise constness.
    This leads to the notion of logical constness. Adherents to this philosophy argue that a const member function might modify some of the bits in the object on which it’s invoked, but only in ways that clients cannot detect.

    Thus we have the feature of  of C++’s mutable which allows certain data members to be modified even in const member functions. Thus you can keep some **private** mutable data members to provide more constraints on the const functions, say keep a binary bit to check if the sting has been modified. And since they are private, the clients will never know.

## Why is the return type of `operator[] ` a reference, like `char&`?

    If operator[] did return a simple char , statements like this wouldn’t compile:

        tb[0] = ’x’;


    **Note:** A member function can be overloaded simply based on whether it is a const member function or not (not the return type const but const member function).

        char& operator[](std::size_t position) const {..}
        char& operator[](std::size_t position) { .. }


## How will you avoid code duplication when overloaded const and non-const member functions have essentially identical implementations?

    One way is to  move all common code into a separate member function (private, naturally) that both versions of operator[] call, but you’ve still got the duplicated calls to that function and you’ve still got the duplicated return statement code.

    Other way is to implement a non- const member function in terms of its const twin.

        char& operator[](std::size_t position)
        {
            return
                const_cast<char&>(
                    static_cast<const TextBlock&>(*this)[position]
                );
        }

    If you were to call a non-const function from a const one, you’d run the risk that the object you’d promised not to modify would be changed. That’s why having a const member function call a non-const one is wrong.


## Are all variables initialized by default in C++  at the point of declaration? How do you initialize the data members of a class?

    In some contexts, the variables are  guaranteed to be initialized (to zero), but in others, it’s not. For example, **an array isn’t necessarily guaranteed to have its contents initialized, but a vector is (only for built-in types like int, char, etc.)**. Thus always initialize your objects before you use them.

    Consider the example of a class :

        class ABEntry {  // ABEntry = “Address Book Entry”
            std::string theName;
          public  :
            ABEntry(const std::string& name) {
                theName = name;
            }
        }

    Inside the ABEntry constructor, theName isn’t being initialized, it is being assigned. Initialization took place earlier — when the default constructors were automatically called prior to entering the body of the ABEntry constructor.
    Thus a better way to write the ABEntry constructor is to use the member initialization list instead of assignments:

        ABEntry::ABEntry(const std::string& name) : theName(name) {}

    The assignment-based version first called default constructor to initialize theName then promptly assigned new values on top of the default-constructed one. All the work performed in those default construction was therefore wasted. The member initialization list approach avoids that problem, because the arguments in the initialization list are used as constructor arguments for the the data members.

    **Tip :** Always list every data member on the initialization list because it avoids having to remember which data members may go uninitialized if they are omitted. Also, sometimes the initialization list must be used, even for built-in types. For example, data members that are const or are references must be initialized; they can’t be assigned.

## What is the order of initialization of data members of a class when we use an initialization list?

    The data members are initialized in the order in which they are declared, even if they are listed in a different order on the member initialization list. Thus to avoid confusion, always list members in the initialization list in the same order as they’re declared in the class.

## Consider the following code

        class Transaction {
          public:
            virtual void logTransaction() const;
            Transaction() { logTransaction(); }
        };


        class BuyTransaction: public Transaction {
          public:
            virtual void logTransaction() const;
            ...
        };

        BuyTransaction obj;

    <Qu> What would happen if we execute the above code?

    BuyTransaction constructor will be called, but first, a Transaction constructor must be called (since base class parts of derived class objects are constructed before derived class parts are), which will further call logTransaction() which is virtual. Note that the version of logTransaction that’s called is the one in Transaction, not the one in BuyTransaction.
This    is so because the vptr points to the vtable of the base class at that point. The logic behind this is that derived class data members have not been initialized when base class constructors run. If virtual functions called during base class construction went down to derived classes, the derived class functions would almost certainly refer to local data members, but those data members would not yet have been initialized.

    Similar is the case if you call a virtual function inside a destructor.  Once a derived class destructor has run, the object’s derived class data members assume undefined values, so C++ treats them as if they no longer exist. Upon entry to the base class destructor, the object becomes a base class object, and all parts of C++ — virtual functions, dynamic_casts, etc., — treat it that way.

    Overall,** never call virtual functions during construction or destruction**, because such calls will never go to a more derived class than that of the currently executing constructor or destructor.

## What does the `explicit` specifier in front of constructors mean?

    The compiler is allowed to make one implicit conversion to resolve the parameters to a function. What this means is that the compiler can use constructors callable with a single parameter to convert from one type to another in order to get the right type for a parameter. Consider the following code :

        class Foo {
            int m_foo;
          public:
            Foo (int foo) : m_foo (foo) {}
        };

        void Bar(Foo f);

        int main () {
            Bar (42);
        }

    The argument is not a Foo object, but an int. However, there exists a constructor for Foo that takes an int so this constructor can be used to convert the parameter to the correct type.
The compiler is allowed to do this once for each parameter.
Prefixing the explicit keyword to the constructor prevents the compiler from using that constructor for implicit conversions. Adding it to the above class will create a compiler error at the function call `Bar (42)`. It is now necessary to call for conversion explicitly with `Bar (Foo (42))`. The reason you might want to do this is to avoid accidental construction that can hide bugs.

## Say you want to implement the `operator=` for some class `Student`,  what do you think is the return type of the function, and how will you implement it?

    Assignment returns a reference to its left-hand argument, so that expressions like `a=b=c;`are successfully evaluated without calling the constructors/destructors for creating temporaries (in case we passed by value). Thus for our class, we will return a reference to *this.

        Student& operator=(const Student& rhs) {
            ...
            return *this;
        }

    Similar is the case with `+=`, etc.

    **Note : ** When implementing such operators, make sure that they are well behaved when an object is assigned to itself.

## Consider the following code:

        class Customer {
            std::string name;
          public:
            Customer(const Customer& rhs) : name(rhs.name) {}
        };

        class PriorityCustomer: public Customer {
            int priority;
          public:
            PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority) {}
        };

    <Qu> What are the issues with the above code?

    Since PriorityCustomer’s copy constructor specifies no arguments to be passed to its base class constructor (i.e., it makes no mention of Customer on its member initialization list), so the Customer part of the PriorityCustomer object will try to be initialized by the default constructor. But since there is no default constructor, it will give an error.
    Thus whenever copying a derived class object (like the copy constructor or `operator=`), you must take care to also copy the base class parts.

        PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) :
                Customer(rhs), priority(rhs.priority) {}

## Consider the following code:

        std::string *stringArray = new std::string[100];
        ...
        delete stringArray;

    <Qu> What are the issues with the above code?

    If you use [] in a new expression, you must use [] in the corresponding delete expression. Using [] assumes that the pointer points to an array. Thus in the above code - at the very least - 99 of the 100 string objects pointed to by stringArray are unlikely to be properly destroyed, because their destructors will probably never be called.

## Some questions to consider when designing a new class:

    -  How should objects of your new type be created and destroyed?

    -  What are the restrictions on legal values for your new type?

    - What kind of type conversions are allowed for your new type?

    - What operators and functions make sense for the new type?

    - Who should have access to the members of your new type?


## When should we prefer pass-by-reference-to-const over pass-by-value and vice versa?

    When passing an argument by value, it leads to a call to the copy constructor and destructor. Thus when dealing with user defined types, it further leads to calls to constructors and destructor for the data members, whereas when passing by reference, we are simply passing a pointer. Thus is more efficient for user defined types, even if they are very small in size.
    But for built-in types, passing directly by value is more optimized than passing pointers, thus call by value is preferred.
Also, remember that STL iterators and function objects are designed such that pass by value is more efficient.

## What is the importance of data hiding, or keeping  data members private with respect to encapsulation?

    If we hide our data members properly, we can ensure that class invariants are always maintained, because only member functions can affect them. Furthermore, we reserve the right to change our implementation decisions later, without breaking any client code.
    Also note that private is much better than protected. This is so because the encapsulatedness of a data member is inversely proportional to the amount of code that might be broken if that data member changes, e.g., if it’s removed from the class. Thus removing a protected member can lead to breaking down of all the derived classes that use it, which is, again, typically an unknowably large amount of code.

## Consider the following code :

        baseClass* factoryFunction();   // Returns raw pointer to allocated object

    <Qu> Explain the idea behind RAII (Resource Acquisition is Initialization) using the above code as example.

    The common problem with such a code is that the callee can forget to delete the object. Thus the simple solution to initialize a shared_ptr with the object immediately after it is returned.

        void f() {
            shared_ptr<baseClass> sPtr(factoryFunction());
            ..
        }       // Delete called automatically

    This is the idea behind RAII where we acquire a resource and initialize a resource managing object in the same statement, which helps in preventing resource leaks.

    But again the client can forget to do that, thus better to write such functions as :

        shared_ptr<baseClass> factoryFunction();

    This will force the client to store the returned value in a shared_ptr. Note that this is how a factory method is implemented.

    **Note :**  Remember that there is a get() method with shared_ptr to get the raw underlying pointer. But that appears contrary to encapsulation for a RAII class. The idea is that RAII classes don’t exist to encapsulate something; they exist to ensure that a particular action — resource release — takes place.

## Consider the following code :

        void someMethod(shared_ptr<someClass> sptr);

        main() {
            someMethod(new someClass);
        }

    <Qu> Will the above code work?


    Remember that this is allowed:

        shared_ptr<int> sptr2(new int);

    So basically we have a constructor for shared pointer which takes the object pointer, but the problem is that the constructor is explicit, hence it will not compile. Basically for explicit constructors, copy initialization is not allowed :

        std::shared_ptr<int> p = new int(5);

    According to the reference, copy initialization occurs when passing an argument to a function by value, when returning from a function that returns by value, and so on.

    A better way would be to replace the method call by :

        someMethod(shared_ptr<int> sptr2(new int));


## Consider the code below:

        f(shared_ptr<someClass>(new someClass), someMethod())
    <Qu> What can be the possible problems with this code?

    Note that the arguments are evaluated before the function call but the compilers have the freedom to choose the order of evaluating the arguments. The `new someClass` expression must be executed before the shared_ptr constructor can be called, because the result of the expression is passed as an argument to the shared_ptr constructor, but the call to `someMethod()` can be performed first, second, or third. If compilers choose to perform it second, the order of operations would be:

    1. Execute “new someClass ”.
    2. Call someMethod().
    3. Call the shared_ptr constructor.

    But consider what will happen if the call to someMethod() yields an exception. In that case, the pointer returned from “new someClass” will be lost, because it won’t have been stored in the shared_ptr and thus would lead to a resource leak. Therefore it would be better to use separate statements for both :

        shared_ptr<someClass> sptr(new someClass);
        f(sptr, someMethod());


## What is a DLL (Dynamically Linked Library)? What is the advantage of using DLL?

    Dynamic linking is a mechanism that links applications to libraries at run time. The libraries remain in their own files and are not copied into the executable files of the applications. DLLs link to an application when the application is run, rather than when it is created. Many times, DLLs are placed in files with different extensions such as .exe, .drv or .dll.
    One advantage of using DLL is these files don't get loaded into the RAM together with the main program; they don't occupy space unless required. When a DLL file is needed, it is loaded and run. For example, as long as a user of Microsoft Word is editing a document, the printer DLL file is not required in RAM. If the user decides to print the document, then the Word application causes the printer DLL file to be loaded and run.

##  What is the cross-DLL problem and how does shared_ptr solve it?

     The cross-DLL problem crops up when an object is created using new in one dynamically linked library (DLL) but is deleted in a different DLL. On many platforms, such cross-DLL new/delete pairs lead to runtime errors.
    shared_ptr avoids the problem because its default deleter uses delete from the **same** DLL where the shared_ptr was created, by keeping track of its deleter method.

## Consider this class :

        class WebBrowser {
          public:
            ...
            void clearCache();
            void clearHistory();
            void removeCookies();
            ...
        };

    <Qu> We want to add a `clearEverything()` method to perform all these methods together. Should we add it as a member function or a non-member function?

    As mentioned earlier,  the greater something is encapsulated,the greater our ability to change it without affecting other things. Thus given a choice between a member function (which can access not only the private data of a class, but also private functions, enums, typedefs, etc.) and a non-member non-friend function (which can access none of these things) providing the same functionality, the choice yielding greater encapsulation is the non-member non-friend function, because it doesn’t increase the number of functions that can access the private parts of the class.
    Note that this reasoning applies only to non-member non-friend functions. Friends have the same access to a class’s private members that member functions have, hence the same impact on encapsulation.

    Now we can imagine that a class like WebBrowser might have a large number of convenience functions (like `clearEverything()`), some related to bookmarks, others related to printing, still others related to cookie management, etc.  The straightforward way to separate them is to declare bookmark-related convenience functions in one header file, cookie-related convenience functions in a different header file, and so on but all under the same namespace.

        // header “webbrowser.h”
        namespace WebBrowserStuff {
            class WebBrowser {
                // “core” related functionality
            };
        }

        // header “webbrowserbookmarks.h”
        namespace WebBrowserStuff {
            // bookmark-related convenience functions
        }

        // header “webbrowsercookies.h”
        namespace WebBrowserStuff {
            // cookie-related convenience functions
        }

    This is similar to how STL is organized with everything (vector, algorithm, memory, etc.) in the std namespace. The advantages of doing this is:

    - This allows user to be compilation dependent only on the parts of the system they actually use.   Partitioning functionality in this way is not possible when it comes from a class’s member functions, because a class must be defined in its entirety; it can’t be split into pieces.

    - Putting all convenience functions in multiple header files — but one namespace — also means that clients can easily extend the set of convenience functions. All they have to do is add more non-member non-friend functions to the namespace.

## Consider the following code:

        class Rational {
          public:
            Rational(int num = 0, int den = 1);
            int numerator() const;
            int denominator() const;
            const Rational operator*(const Rational& rhs) const;
        };

        Rational oneHalf(1, 2);
        result = oneHalf * 2;   // Statement 1
        result = 2 * oneHalf;   // Statement 2

    <Qu> Will the above statements compile?

    Statement1 will compile because compilers know that you’re passing an int and that the function requires a Rational, thus they do an implicit conversion by calling the Rational constructor. If Rational’s constructor were explicit, it  would not compile.

    Note that  in Statement 2, you are calling `operator*` method of int class. Thus it will not compile because parameters are eligible for implicit type conversion only if they are listed in the parameter list. The implicit parameter corresponding to the object on which the member function is invoked — the one `this` points to — is never eligible for implicit conversions.

    To support both methods, make `operator*` a non-member function, thus allowing compilers to perform implicit type conversions on all arguments.

        const Rational operator*(const Rational& lhs, const Rational& rhs);

## Why should we postpone variable declarations and initializations as long as possible?

    - By doing so, you avoid constructing and destructing unneeded objects.

    - Default-constructing an object and then assigning to it is generally less efficient than initializing it with the value using copy constructor.

## Compare the following two approaches :

        // Approach A
        Widget w;
        for (int i = 0; i < n; ++i) {
            w = some value dependent on i;
            ...
        }

    <Qu> Or

        // Approach B
        for (int i = 0; i < n; ++i) {
            Widget w(some value dependent on
            ...
        }

    In terms of Widget operations, the costs of these two approaches are as follows:

    - Approach A: 1 constructor + 1 destructor + n assignments.
    - Approach B: n constructors + n destructors.

    For classes where an assignment costs less than a constructor-destructor pair, Approach A is generally more efficient. This is especially the case as n gets large. Otherwise, Approach B is probably better.
    Furthermore, Approach A makes the name w visible in a larger scope (the one containing the loop) than Approach B, something that’s contrary to program comprehensibility and maintainability.

## Consider the following code :

        class Base {
          public:
            virtual void method() { ... }
            ...
        };

        class Derived: public Base {
          public:
            virtual void method() {
                static_cast<Base>(*this).method();
                ...
            };
        ...
        };

    <Qu> What is the problem with this code, and how will you solve it?

    Note that we are casting *this and not this.
    The code casts `*this` to a Base object, thus the call to method invokes Base::method(). But, the cast creates a new, temporary copy of the base class part of `*this`, then invokes method() on the copy. The  Thus if Base::method modifies the current object, the current object won’t be modified but a copy of that object will be modified. However, If Derived::method modifies the current object, the current object will be modified, hence inconsistent behaviour.
    The solution is to eliminate the cast and simply call the required method :

        class Derived: public Base {
          public:
            virtual void method() {
                Window::method();
                ...
            }
        ...
        };

## Consider the following code :

        class Point {
            int x,y;
          public:
            void setX (int val);
            void setY (int val);
          };

        class Rectangle {
            Point upperLeftCorner;
            Point lowerRightCorner;

          public:
            Point & upperLeft() const  { return upperLeftCorner; }
            Point & lowerRight() const { return lowerRightCorner; };
        };

        const Rectangle obj (point1, point2);

    <Qu> What is the problem with this code and how can you solve it?

    One argument in favour of this code is that  since Point is a user-defined type, thus passing user-defined types by reference is typically more efficient than passing them by value. But the problem is code like this:

        obj.upperLeft().setX(50);

    Thus, you might be able to modify your point object from the reference, even though the object is constant. A solution can be to change the return type of the function to return a const object :

        const Point & upperLeft() const { return upperLeftCorner; }

    Thus only read access will be given if a const object is returned and not write access. But the problem with this approach can be understood from the following code :

        Point * ptr = &obj.upperLeft();

    So if the rectangle object goes out of scope, it would lead to a dangling pointer to non existent objects.

    Thus it is recommended that functions should never return handle to an internal part of the object, even if the function is const, or returns a const.

## Can we declare virtual functions inline?

     Virtual means “wait until runtime to figure out which function to call,” and inline means “at compile time, replace the call site with the called function.” Therefore since compilers don’t know which function to be called, they cannot inline the function’s body.
     Note that this is a disadvantage if your functions are small, because small functions are often automatically inlined and lead to optimized code.


## How do you make a member function of class inline?

    Always remember that inlining is a request to compilers, not a command, thus might not always succeed.
    There are two ways to request compiler for making a member function inline:

        class MyClass {
            int m_i;
          public:
            int f() const { return m_i; }   // Method 1
            int g() const;
        };

        inline int MyClass::g() const { return m_i; }   // Method 2

## Why should inline functions generally be in header files?

    Inline functions must typically be in header files, because most build environments do inlining during compilation. In order to replace a function call with the body of the called function, compilers must know what the function looks like.

## Why should templates be placed in header files?

    Templates are typically in header files, because compilers need to know what a template looks like in order to instantiate it when it’s used.


## Consider the following code:

        class Base {
            std::string bm1, bm2;
          public:
            Base() {}
        };

        class Derived: public Base {
            std::string dm1, dm2, dm3;
          public:
            Derived() {}
        };

    <Qu> Is the `Derived` constructor a good candidate for inlining?

    Even though the constructor seems empty, there is a lot of code which automatically ends up inside it.
    The Derived constructor would first call the Base constructor which itself might have a lot of code. This can be a problem if the Base constructor is itself inline (as in the above case).
    Also, Derived’s constructor would call constructors for each of its data members and base class, and those calls might themselves be inlined. For example, in above case, Derived’s constructor will have constructor calls for 5 string objects which themselves might be inlined.
    Further if an exception is thrown during construction of an object, any parts of the object that have already been fully constructed are automatically destroyed. There has to be some code in our program to make those things happen, and that code often ends up in constructors itself.
    So overall if the constructor is inline,  there can be a lot of repeated code, this can increase the object file size a lot, which is not required. Also there are other disadvantages of inline functions as discussed in the next question.

## What are the disadvantages of inlining?

    - Inlining is likely to increase the size of the object code.

    - It is impossible to provide binary upgrades to the client visible inline functions in a library. This is so because if `f` is an inline function in a library, clients of the library compile the body of `f` into their applications. If a library implementer later decides to change `f`, all clients who’ve used `f` must recompile.

    -  Most debuggers have trouble with inline functions. because we cannot set a breakpoint in a function that isn’t there.

## What is the pimpl (Pointer to implementation) idiom? Explain with the help of the following example of class:

        class Person {
            string theName;
            Date theBirthDate;

          public:
            Person(const std::string& name, const Date& birthday);
            string name() const;
            string birthDate() const;
        };

    The problem that the pimpl idiom deals with is that of compilation dependencies between libraries. In the above example, Person class has compilation dependencies on libraries for string and Date, and thus we need to `inlcude` these header files. If any of these header files is changed, or if any of the header files they depend on changes, the file containing the Person class must be recompiled, as must any files that use Person. Such cascading compilation dependencies is what pimpl idiom tries to solve.

    The possible alternative to that would have been to just forward declare the string and birthDate class and use them without including the header files. For example

        class string;
        class Date;

        class Person {
            string theName;
            string theBirthDate;
            ...
        };

        main() {
            Person p;
        }

    But this is not allowed in C++. Because compilers need to know the size of a Person object at compile time  so that it can reserve enough space for the objects (like p in above case). Thus it is important to add such implementation details even to a class declaration, and we cannot just work with the interface of the class at declaration.

    So the pimpl idion says that we can seperate the classs interface and its implementation into two classes, and the interface class will just have a pointer to the object of implementation class as its data member. So in above class the `Person` class will be modifed to:

        // Person.h

        #include  <string>  // Should not forward declare stl stuff

        class PersonImpl;
        class Date;

        class Person {
            shared_ptr <PersonImpl> pimpl;

          public:
            Person(const std::string& name, const Date& birthday);
            string name() const;
            string birthDate() const;
        };

    And `Person.cpp` would look like this:

        Person::Person(const std::string& name, const Date& birthday)
        : pImpl(new PersonImpl(name, birthday, addr)) {}

        std::string Person::name() const { return pImpl->name(); }

    So now we don't have a compilation dependency on PersonImpl and Date in our Person class, because we have separated the interface and the implementation, and the interface class just has a pointer.
    Class like `Person`which use the pimpl idiom are called Handle classes.


## What are the drawbacks of pimpl idiom?

    In the case of Handle classes, member functions have to go through the implementation pointer to get to the object’s data. That adds one level of indirection per access.
    And you must add the size of this implementation pointer to the amount of memory required to store each object.
    Finally, the implementation pointer has to be initialized (in the Handle class’s constructors) to point to a dynamically allocated implementation object, so you incur the overhead inherent in dynamic memory allocation (and subsequent deallocation) and the possibility of encountering bad_alloc (out-of-memory) exceptions.

## What are the alternatives to using pimpl idiom for solving the same problem?

    The alternative for pimpl idion for separating interface and implementation details for reducing compilation dependencies is to use interface classes (for the actual interface), and then derived classes for the implementation details. Because like clients of Handle classes, clients of Interface classes need not recompile unless the Interface
class’s interface is modified.


        class Person {
          public:
            virtual ~Person();
            virtual std::string name() const = 0;
            virtual std::string birthDate() const = 0;

            // The static factory method for instantiating
            static shared_ptr<Person> create(const std::string& name, const Date& birthday) {
                return shared_ptr<Person>(new PersonImpl(name, birthday));
            }
            ...
        };

        main() {
            ...
            shared_ptr<Person> ptr(Person::create(name, dateOfBirth, address));
            ...
        }

    Note that the class has a factory functions or virtual constructor. They return pointers  to dynamically allocated objects that support the Interface class’s interface.

    The drawback of using this method is that every function call is virtual, so we pay the cost of an indirect jump each time we make a function call.
Also, objects derived from the Interface class must contain a virtual table pointer. This pointer may increase the amount of memory needed to store an object.

## Consider the following code :

        class someClass {
            int mData;

          public:
            someClass(const int data) : mData(data) {};
            const int getData(const someClass& otherObj) const { return otherObj.mData; };
        };

        int main() {
          someClass a(1);
          someClass b(2);

          std::cout << "b via a = " << a.getData(b) << std::endl;
          return 0;
        }

    <Qu> Will it work?

    It is perfectly possible for object a to access private data from object b and return it. Hence this code works. Basically in C++ access control works on per-class basis, not on per-object basis.

## Is partial template specialization allowed for function templates?

    Only full template specialization allowed for function templates and not partial template specialization. The alternative to that is function overloading. For example, say you have the following function template:

        template <typename T, typename U>
        T fun(U pObj) {...}

    So partial specialization would have looked like:

        template <typename T>
        T fun <T, int> (int pObj) {...}

    But this is not allowed, and we can replace it with function overaload:

        template <typename T>
        T fun(int pObj){...}

    **Note** that full function specialization is allowed:

        template <>
        void fun<void, int>(int pObj) { ... }

## What is std::swap() ?

    The method looks like:

        template< class T >
        void swap( T& a, T& b ) noexcept(/* see below */);

    It is used to exchange two values.

        int a = 5, b = 3;
        std::swap(a,b);

    **Note :** A very interesting item (Item 25) on how to implement swap for your class is given in book. Do read if required.

## What is the difference between explicit interface and implicit interface? Explain with the help of following code:

        template<typename T>
        void doProcessing(T& w)
        {
            if (w.size() > 10 && w != someNastyWidget) {
                ...
            }
        }

    The explicit interface of typically consists of the function signatures, i.e., function names, parameter types, return types, etc. of the public methods of a class, which explain how we can use its objects.
    An implicit interface is different in the sense that it consists of valid expressions. For example, in the above code, the implicit interface for T (w’s type) appears to have these constraints:

    - It must offer a member function named size that returns an object of some type X such that there is an operator> that can be called with an object of type X and an int (because 10 is of type int). It would also be fine if the operator> could take a parameter of type Y, and there were an implicit conversion from objects of type X to objects of type Y. Basically the `w.size() > 10` should be valid for the object w of type T.

    - Similarly type T must support an operator!= function that compares objects of type T and someNastyWidget's type, even if by implicitly type casting both of the operands.

    Just as you can’t use an object in a way contradictory to the explicit interface its class offers (the code won’t compile), you can’t try to use an object in a template unless that object supports the implicit interface the template requires (again, the code won’t compile).

## Consider the following code:

        template<class T> class Widget;
        template<typename T> class Widget;

    <Qu> What is the difference between class and typename in the above code?

    There is no difference between the two.

## Consider the folowing code:

        template<typename C>
        void print2nd(const C& container)
        {
            C::const_iterator * x;
            ...
        }

    <Qu> What are the problems with the above code?

    This looks like we’re declaring x as a local variable that’s a pointer to a C::const_iterator.  For example, C can be `vector<int>` and then we will get a pointer to  ` vector<int>::const_iterator` .
    But in the above statement, we are assuming C::const_iterator as a type. What if C had a static data member that happened to be named const_iterator , and what if x happened to be the name of a global variable? In that case, the code above wouldn’t declare a local variable, it would be a multiplication of C::const_iterator by x.
    Thus until C is known, there’s no way to know whether C::const_iterator is a type or isn’t. C++ has a rule to resolve this ambiguity: it assumes all such cases as not a type unless you tell it otherwise.

    By such cases I mean nested dependent names. For example, here, const_iterator is *nested* inside C, and also is *dependent* on the template parameter. So nested dependent names would not be considered as a type unless specifically mentioned. To do that, we need to add `typename` in front of it.

        typename C::const_iterator * x;

## Consider the following code:

        template<typename IterT>
        void workWithIterator(IterT iter) {
            typename std::iterator_traits<IterT>::value_type temp(*iter);
            ...
        }

    <QU> What does it do?

     Here we are using the standard traits class, the C++ way of saying “the type of thing pointed to by objects of type IterT.” The statement declares a local variable (temp) of the same type as what IterT objects point to, and it initializes temp with the object that iter points to. If IterT is `vector<int>::iterator` , temp is of type int. If IterT is `list<string>::iterator`, temp is of type string.
    Because std::iterator_traits<IterT>::value_type is a nested dependent type name (value_type is nested inside iterator_traits<IterT>, and IterT is a template parameter), we must precede it by typename.

## Consider the following code:

        template <typename someType>
        class Base {
          public:
            baseClassMethod();
            ..
        }

        template <typename someType>
        class Derived : public Base <someType> {
          public:
            derivedClassMethod() {
                ..;
                baseClassMethod();
            }
            ..
        }

    <Qu> What is the problem with the above code?

    The problem is that when compilers encounter the definition for the class template Derived , they don’t know what class it inherits from because without knowing what `someType` is, there’s no way to know what the class `Base<someType>` looks like.     For example, say there is a specialization of Base class `Base<int>` which does not even have the `baseClassMethod()` inside it.
    That is why C++ generally refuses to look in templatized base classes for inherited names and gives an error for such function calls.

## How will you solve the above problem?

    -  We can preface calls to base class functions with “this->”

            this->baseClassMethod();    // Assumes that method will be inherited

    - We can use a `using` declaration (generally preferred)


            template <typename someType>
            class Derived : public Base <someType> {
              public:
                // Assume that Base will have this method
                using Base <someType>::baseClassMethod;

                derivedClassMethod() {
                    ..;
                    baseClassMethod();
                }
                ..
            }

    - Explicitly specify the function being called. But this is  least desirable way to solve the problem, because if the function being called is virtual, explicit qualification turns off the virtual binding behavior.

            Base <someType>::baseClassMethod();

## Why should we factor parameter-independent code out of templates? Explain using the following class as example.

        template<typename T, std::size_t n>
        class SquareMatrix {
          public:
            ...
            void invert();

          private:
            T data[n*n];        // Note that this is allowed
        };

    The simple reason is that templates can lead to code bloat with large binaries because of replicated instantiations of code. So if we have the following code:

        SquareMatrix<double, 5> sm1;
        ...
        sm1.invert();

        SquareMatrix<double, 10> sm2;
        ...
        sm2.invert();

    Two copies of `invert()` will be instantiated which would be quiet similiar. The solution is to create a new function that took the size value as a parameter, then call this  function with 5 or 10 instead of replicating the code.

        template<typename T>
        class SquareMatrixBase {    // Size independent base class
          protected:
            ...
            void invert(std::size_t matrixSize);
        };

        template<typename T, std::size_t n>
        class SquareMatrix: private SquareMatrixBase<T> {   // Private inheritance
            using SquareMatrixBase<T>::invert;

          public:
            ...
            void invert() { invert(n); }        // Inline call to base class method
        };

    Note that the base class is also a templatized class but independent of matrix size. Thus all matrix objects of a given type T will inherit from the same base class, and therefore will share a single copy of base's invert(). Note that we should not declare SquareMatrixBase::invert inline because otherwise each instantiation of SquareMatrix::invert will get a copy of SquareMatrixBase::invert’s code, and would again lead to code bloat.

    As with non-size paramemters (like size), type parameters can lead to bloat, too. For example, on most platforms,  all pointer types have the same binary representation, so templates holding pointer types (e.g., `list<int*>`, `list<const int*> `, `list<SquareMatrix<long, 3>*>`, etc.) should often be able to use a single underlying implementation for each member function. Typically, this means implementing member functions that work with strongly typed pointers (i.e., T* pointers) by having them call functions that work with untyped pointers (i.e., void* pointers).

## What are generalized copy constructors?

    Consider the following example:

        template<typename T>
        class someClass {
          public:
            template<typename U>
            someClass(const someClass<U>& other);
            ...
        };

    This says that for every type T and every type U, a `someClass<T>` can be created from a `someClass<U>`, because `someClass<T>` has a constructor that takes a `someClass<U>` parameter. Constructors like this — ones that create one object from another object whose type is a different instantiation of the same template (e.g., create a `someClass<T>` from a `someClass<U>`) — are  known as generalized copy constructors.

## What are friend functions? What is the common use case for friend functions? Are friend functions inherited?

    A friend function of a class is defined outside that class' scope but it has the right to access all private and protected members of the class. Even though the prototypes for friend functions appear in the class definition, friends are not member functions. Similarly you can declare a class as friend to another class.

        class Node {
           int data;
           Node * next;
        public:
           friend void printData(Node node);
           friend class LinkedList;
        };

    Note that friend functions can be declared under any Access Specifier, the access specifier rules do not apply to friend functions.

    An interesting use case for friend functions is that you can declare a common friend function for two or more classes and thus it can access private members of both the classes. Therefore it can act like a bridge and implement unique functionalities.

    No, friend functions are not inherited.

## onsider the following code:

        template<typename T>
        class Rational {
          public:
            Rational(const T& numerator = 0, const T& denominator = 1);
            ..
        };

        template<typename T>
        const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {...}

        Rational<int> oneHalf(1, 2);
        Rational<int> result = oneHalf * 2;

    <Qu>Will the above code work?

    We might expect them to use `Rational<int>`’s non-explicit constructor to convert 2 into a `Rational<int>`, thus allowing them to deduce that T is int, but - unlike function calls - **implicit type conversion functions are never considered during template argument deduction**.  This is so because before we can call a function, we know which functions exist. But with templates , in order to know that, we have to deduce parameter types for the relevant function templates (so that we can instantiate the appropriate functions).

## Consider the following code:

        template<typename T>
        class Rational {
          public:
            ...
            friend const Rational operator*(const Rational& lhs, const Rational& rhs) {
                return Rational( lhs.numerator() * rhs.numerator(),
                                 lhs.denominator() * rhs.denominator());
            }
        };

        Rational<int> oneHalf(1, 2);
        Rational<int> result = oneHalf * 2;

    <Qu>Will this code solve the above problem? If yes, How?

    First, note that Inside a class template, the name of the template can be used as shorthand for the template and its parameters, so inside `Rational<T>`, we can just write `Rational` instead of `Rational<T>`.

    This code will solve our problem because now, when the object `oneHalf` is declared to be of type `Rational<int>`, the class `Rational<int>` is instantiated, and as part of that process, the friend function `operator*` that takes `Rational<int>` parameters is automatically instantiated too. Thus now, compilers can use implicit conversion functions (such as Rational’s non- explicit constructor) when calling the `operator*` method.

## Explain the different types of iterators in STL?

    There are 5 types of iterators :

    1. **Input Iterators** :
    Input iterators can move only forward, can move only one step at a time, can only read what they point to, and can read what they’re pointing to only once. They’re modeled on the read pointer into an input file.

    1. **Output Iterators** :
    Output iterators move only forward, move only one step at a time, can only write what they point to, and can write it only once. They’re modeled on the write pointer into an output file.

        Because input and output iterators can move only forward and can read or write what they point to at most once, they are suitable only for one-pass algorithms.

    1. **Forward Iterators** :
     Forward iterators can do everything input and output iterators can do, plus they can read or write what they point to more than once. This makes them viable for multi-pass algorithms. Iterators into containers like singly linked list are forward iterators.

    1. **Bidirectional Iterators** :
    Bidirectional iterators add to forward iterators the ability to move backward as well as forward. Iterators for the STL’s list are in this category, as are iterators for set, multiset, map, and multimap.

            template < ... >
            class list {
              public:
                class iterator {
                  public:
                    typedef bidirectional_iterator_tag iterator_category;
                    ...
                };
                ...
            };

        Hence when you write list<int>::iterator, you get a bidirectional iterator.

    1. **Random Access Iterators** :
    These kinds of iterators add to bidirectional iterators the ability to perform “iterator arithmetic,” i.e., to jump forward or backward an arbitrary distance in constant time. Such arithmetic is analogous to pointer arithmetic, which is not surprising, because random access iterators are modeled on built-in pointers, and built-in pointers can act as random access iterators. Iterators for vector , deque, and string are random access iterators.

        Similar as above, when you use an iterator for a vector, you get a random access iterator.

## What does the `advance()` method for iterators do and how is it implemented?

    The advance method looks like this:

        template<typename IterT, typename DistT>
        void advance(IterT& iter, DistT d);

    Conceptually, advance just does iter += d, but advance can’t be implemented that way, because only random access iterators support the += operation. Less powerful iterator types have to implement advance by iteratively applying ++ or -- d times.

    Thus we want to implement it as something like :

        template<typename IterT, typename DistT>
        void advance(IterT& iter, DistT d) {
            if (iter is a random access iterator) {
                iter += d;
            } else {
                if (d >= 0) { while (d--) ++iter; }
                else { while (d++) --iter; }
            }
        }

    So to check the type of the iterator, we can use the traits class **at compile time**.

## Consider the following code:

        template<typename IterT, typename DistT>
        void advance(IterT& iter, DistT d) {
            if ( typeid(typename std::iterator_traits<IterT>::iterator_category) ==
                 typeid(std::random_access_iterator_tag)) {
                iter += d;
            } else {
                if (d >= 0) { while (d--) ++iter; }
                else { while (d++) --iter; }
            }
        }

    <Qu>Will this code solve the above problem? Assume that the if condition is written correctly.

    As mentioned in the previous question, the iterator_traits class will help us find the type of iterator at compile time, because at compile time only, we will know iterT, hence will know its iterator category. But there are two problems with this code:

    1. Even though `iterator_traits<IterT>::iterator_category` can be determined during compilation, yet the if statement is evaluated at runtime. Thus we would like to do a conditional test on compile time.

    1. The bigger problem is that the code won't compile. Consider the following example for the above implementation :

            std::list<int>::iterator iter;
            ...
            advance(iter, 10);

        So on substituting iter’s and 10’s types for the template parameters IterT and DistT, compiler will generate a version of advance where  we would be trying to use += on a `list<int>::iterator`, but `list<int>::iterator` is a bidirectional iterator, so it doesn’t support +=. Only random access iterators support +=. Even though we’ll never try to execute the += line, because the typeid test will always fail for `list<int>::iterators`, but compilers are obliged to make sure that all source code is valid, even if it’s not executed, and “iter += d” isn’t valid when iter isn’t a random access iterator.


## How will you solve the above problems?

    The solution for doing a compile-time conditional test in this case is through function overaloading. When we overload some function f, we specify different parameter types for the different overloads. When we call f, compilers pick the best overload, based on the arguments you’re passing. So in our case, we can  create multiple versions of an overloaded function advance, declaring each to take a different type of iterator_category object.

        template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag) {
            iter += d;
        }

        template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag) {
            if (d >= 0) { while (d--) ++iter; }
            else { while (d++) --iter; }
        }

        template<typename IterT, typename DistT>
        void advance(IterT& iter, DistT d) {
            doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category);
        }

        std::list<int>::iterator iter;
        ...
        advance(iter, 10);


    So overall, given the various overloads for doAdvance(), all advance needs to do is call them, passing an extra object of the appropriate iterator category type so that the compiler will use overloading resolution to call the proper implementation.

## Explain in detail how iterator_traits work?

    First, understand that the `iterator_tag`s are simple structs:

        struct input_iterator_tag {};
        struct output_iterator_tag {};
        struct forward_iterator_tag: public input_iterator_tag {};
        struct bidirectional_iterator_tag: public forward_iterator_tag {};
        struct random_access_iterator_tag: public bidirectional_iterator_tag {};

    Next remember that each container has a predefined iterator tag (as shown above), which is `typedef`ed as its iterator_category:

        template < ... >
        class list {
          public:
            class iterator {
              public:
                typedef bidirectional_iterator_tag iterator_category;
                ...
            };
            ...
        };

    Next, understand that iterator_traits is itself a struct as shown :

        template<typename IterT>
        struct iterator_traits {
            typedef typename IterT::iterator_category iterator_category;
            ...
        };

    So now you can think how `std::iterator_traits<IterT>::iterator_category` works.

## What is Template Metaprogramming (TMP)? What are the advantages/disadvantages of using it?

    Template metaprogramming (TMP) is the process of writing template based C++ programs that execute during compilation.

    - Since template metaprograms execute during C++ compilation, they can shift work from runtime to compile-time.

    - One consequence is that some kinds of errors that are usually detected at runtime can be found during compilation.

    - However, a consequence of shifting work from runtime to compile-time is that compilation takes
longer. Programs using TMP may take much longer to compile than their non-TMP counterparts.

    TMP has been shown to be Turing-complete, which means that it is powerful enough to compute anything. Using TMP, you can declare variables, perform loops, write and call functions, etc. Note that  TMP was discovered, not invented. The features underlying TMP were introduced when templates were added to C++. All that was needed was for somebody to notice how they could be used in clever and unexpected ways.

## Explain how you can write loops in TMP by writing the program for a factorial which gets computed at compile time.

    TMP loops involve recursive template instantiations. The “hello world” program of TMP is computing a factorial during compilation.  It also demonstrates one way in which variables are created and used in TMP.

        template<unsigned n>
        struct Factorial {
            enum { value = n * Factorial<n-1>::value };
        };

        template<>
        struct Factorial<0> {
            enum { value = 1 };
        };

        main() {
            std::cout << Factorial<5>::value;
        }

    The looping part of the code occurs where the template instantiation `Factorial<n>` references the template instantiation `Factorial<n-1>`. Like all good recursion, there’s a special case that causes the recursion to terminate. Here, it’s the template specialization `Factorial<0>`.
    Each instantiation of the Factorial template is a struct, and each struct uses the enum hack to declare a TMP variable named `value`. `value` is what holds the current value of the factorial computation.

## How does public inheritance model an "is-a" relationship?

    This is amongst the most important rules of object oriented programming. If you write that class D (“Derived”) publicly inherits from class B (“Base”), you are telling C++ compilers (as well as human readers of your code) that every object of type D is also an object of type B, but not vice versa. You are asserting that anywhere an object of type B can be used, an object of type D can be used just as well, but not vice versa. Developing an intuition is very important, let us see an example for that :

        class Rectangle {
          public:
            virtual void setHeight(int newHeight);
            virtual int getHeight() const;
          ...
        };

        class Square : Rectange { .. }

    So our mathematical intuition tells us that every square is a rectangle, so we can write class hierarchy like above. But for a rectangle, resizing height without changing width like the following is a valid operation, which might not hold for a square :

        void makeBigger(Rectangle& r)
        {
            r.setHeight(r.getHeight() + 10);
            ...
        }

    Now the fundamental difficulty in this case is that something applicable to a rectangle (its width may be modified independently of its height) is not applicable to a square (its width and height must be the same). But public inheritance asserts that everything that applies to base class objects also applies to derived class objects. This is how the mathematical and object oriented intuition differ.

## Consider the following class hierarchy :

        class Base {
            int x;
          public:
            virtual void mf1() = 0;
            virtual void mf1(int);
            virtual void mf2();
            void mf3();
            void mf3(double);
            ...
        };

        class Derived: public Base {
          public:
            virtual void mf1();
            void mf3();
            ...
        };

    <Qu> Based on the above declaration, consider the following function calls :

        Derived d;
        int x;
        ...
        d.mf1();
        d.mf1(x);
        d.mf2();
        d.mf3();
        d.mf3(x);

    <Qu> Which of the above calls will succeed, and which function do they call? Also, how will you fix the function calls that did not succeed.

    The rule is that when you redefine a base class's method in the derived class, **all the methods** from the base classes with that name get hidden for the derived class.
For  example, when you define  `Derived::mf1()`, both `Base::mf1()` and `Base::mf1(int)`   get hidden in the derived class. So as we can see,  this applies even though the functions in the base and derived classes take different parameter types, and it also applies regardless of whether the functions are virtual or non-virtual.

    Thus `d.mf1()` will succeed and will call `Derived::mf1()`, but `d.mf1(x)` will fail because `Derived::mf1()` will hide `Base::mf1(int)`.
    Note that `d.mf2()` will succeed and call `Base::mf2()`.
    `d.mf3()` will also succeed and calls `Derived::mf3` but `d.mf3(x)` would fail because `Derived::mf3` hides `Base::mf3(double)`.

    The rationale behind this behavior is that it prevents you from accidentally inheriting overloads from distant base classes when you create a new derived class in a library or application framework.

    Now to fix this behaviour, we can make use of the `using` declarations:

        class Derived: public Base {
            using Base::mf1;  // make all things in Base named mf1 and mf3
            using Base::mf3;  // visible (and public) in Derived’s scope


          public:
            virtual void mf1();
            void mf3();
            void mf4();
            ...
        };

    So by `using` declaration, you make **all the methods** with that name visible for the derived class.

        d.mf1();   // still fine, still calls Derived::mf1
        d.mf1(x);  // now okay, calls Base::mf1
        d.mf2();   // still fine, still calls Base::mf2
        d.mf3();   // fine, calls Derived::mf3
        d.mf3(x);  // now okay, calls Base::mf3


## Among pure virtual function, simple virtual function, and a non-virtual function, which one would you prefer in the following situations :
    -  <Qu> When you want the derived method to inherit both a function's interface and a default implementation.
    -  <Qu> When you want the derived method to only inherit the function's interface.
    - <Qu> When you want to allow the derived class to inherit the function prototype as well as the implementation.

    The purpose of declaring a pure virtual function is to have derived classes inherit a function interface only.
    The purpose of declaring a simple virtual function is to have derived classes inherit a function interface as well as a default implementation.

    Note that even the pure virtual methods can have a default implementation, but when using pure virtual methods, it is necessary for the derived classes to redefine these methods whereas not compulsory in case of simple virtual function. Consider the following example :

        class Airplane {
          public:
            virtual void fly(const Airport& destination) = 0;
            ...
        };

        void Airplane::fly(const Airport& destination) {
            // default code for fly
        }

        class ModelA: public Airplane {
          public:
            virtual void fly(const Airport& destination) {
                Airplane::fly(destination); // Note that this is allowed
            }
            ...
        };

    So as can be seen, it is necessary for ModelA to redefine the `fly()` method, even if it simply calls the Base's method inside it.
    So note that this is how you call the `Airplane`'s default implementation inside, without the `using` clause as in the previous problem. This is called **function forwarding**, where we simply forward the function call to another method.

    The purpose of declaring a non-virtual function is to have derived classes inherit a function interface as well as a **mandatory** implementation. By mandatory, we mean that we should be careful in redefining it in derived class (we will see the reason in the next problem).

    So always keep these things in mind when choosing a function's declaration. The differences in declarations for pure virtual, simple virtual, and non-virtual functions allow you to specify with precision what you want derived classes to inherit: interface only, interface and a default implementation, or interface and a mandatory implementation, respectively.

## Consider the following class hierarchy :

        class B {
          public:
            void mf();
            ...
        };

        class D: public B {
          public:
            void mf();
            ...
        };

        D x;
        B *pB = &x;
        D *pD = &x;

        pB->mf();
        pD->mf();

    <Qu> Which mf() will be called in the above two function calls?

    Situation like these are the reason we declare destructors as virtual in polymorphic classes.
    `pB->mf();` will call `B::mf` and `pD->mf()` will call `D::mf`.
    The reason for this inconsistent behavior is that non-virtual functions like `B::mf` and `D::mf` are statically bound. That means that because pB is declared to be of type pointer-to-B, non-virtual functions invoked through pB will always be those defined for class B, even if pB points to an object of a class derived from B, as it does in this example.
    Virtual functions, on the other hand, are dynamically bound, so they don’t suffer from this problem. So to avoid this inconsistent behaviour, we should  carefully redefine an inherited non-virtual function.  If D really has to publicly inherit from B, and if D really needs to implement `mf()` differently from B, then it `mf()` should be virtual, as it happens in case of destructors of polymorphic classes.
    Note that static binding is also known as early binding, and dynamic binding is also known as late binding.

## What is the difference between static type and dynamic type of an object?

    An object’s static type is the type you declare it to have in the program text, whereas an object’s dynamic type is determined by the type of the object to which it currently refers.

        Shape *ps;                  // static type = Shape*
        Shape *pc = new Circle;     // static type = Shape* ,  dynamic type = Circle*

## Why should we never redefine a function’s inherited default parameter value?

    Consider the following code :

        class Shape {
          public:
            enum ShapeColor { Red, Green, Blue };
            virtual void draw(ShapeColor color = Red) const = 0;
            ...
        };

        class Rectangle: public Shape {
          public:
            virtual void draw(ShapeColor color = Green) const;
            ...
        };

        Shape *pr = new Rectangle;
        pr->draw();


    So at the last function call, `pr->draw()` will call Rectangle::draw(Shape::Red). This weird behaviour occurs because virtual functions are dynamically bound, but default parameters are statically bound. This is why we end up invoking a virtual function defined in a derived class but using a default parameter value from a base class.
    The reason for this behaviour in C++ is to shift the task of determining default values for parameters to compile time rather than run time for to make the mechanism faster and less complicated.
    Now this can be a disadvantage of providing default values for virtual functions, because each of the derived class will need to use the same default value to avoid confusion and this would lead to a lot of code repetitions. Also, a small change will have to be repeated at all places.

## Explain briefly how are standard library's sets implemented?

     Sets are implemented as balanced search trees, which allows them to guarantee logarithmic-time lookups, insertions, and erasures.

## What is composition between types and what type of relationship is reflected by composition?

    Composition is the relationship between types that arises when objects of one type contain objects of another type. For example,

        class Person {
            std::string name;   // Composed object
            Address address;    // ditto
            ...
        };

    In this example, `Person` objects are composed of `string`, `Address`, and so on.
    Like public inheritance means “is-a”, composition means either “has-a” or “is-implemented-in-terms-of.” So in the above example, a Person has a name, has an address and so on.
    For another example, consider that we want to implement a stack data structure. So we can do that using a list. Now it is clear that stack is not a list, but we can implement a stack in terms of a list. Thus we can have a list object in our stack class.

## Consider the following code:

        class Person { ... };
        class Student: private Person { ... };

        void eat(const Person& p);
        Student s;
        eat(s);

    <Qu> Will it work?

    This code will not work because in contrast to public inheritance, compilers will generally not convert a derived class object (such as Student) into a base class object (such as Person ) if the inheritance relationship between the classes is private. That is why, private inheritance represents a is-implemented-in-terms-of relationship.
    This is similar to composition. So to choose between them, private inheritance is a legitimate design strategy when you’re dealing with two classes not related by is-a and one either needs access to the protected members of another or needs to redefine one or more of its virtual functions. In all other cases, choose composition over private inheritance.

## What is Empty Base Optimization (EBO)?

    Consider the following class with no data members or functions :

        class Empty {};

        Empty obj;

    You will see that an object of Empty class requires non-zero memory, generally 1 byte. This is so because the standard does not allow objects (and classes thereof) of size 0, since that would make it possible for two distinct objects to have the same memory address. Thus a char is silenty inserted into “empty” objects. But this constraint doesn’t apply to base class parts of derived class objects :

        class HoldsAnInt: private Empty {
            int x;
        };

    For most compilers,  `sizeof(HoldsAnInt) == sizeof(int)`. This is known as the Empty Base Optimization (EBO).

## Consider the following code :

        class Base1 {
          public:               // Note the public
            void checkOut();
            ...
        };

        class Base2 {
          private:              // Note the private
            bool checkOut() const;
            ...
        };

        class Derived: public Base1, public Base2 {
            ...
        };

        Derived obj;
        obj.checkOut();

    <Qu> Which `checkOut()` method will be called?

    Note that in this example, the call to checkOut is ambiguous, even though only one of the two functions is accessible.  This is a disadvantage of multiple inheritance, hence we should use it judiciously. Also, to resolve the ambiguity, you must specify which base class’s function to call:

        obj.Base1::checkOut();

    Or we can also give a using clause in the derived class's definition to avoid ambiguity :

        class Derived: public Base1, public Base2 {
          public:
            using Base1::checkOut;
            ...
        };


## What is the diamond problem with multiple inheritance?

    Multiple inheritance can often lead to hierarchies like :

        class Stream { ... };

        class InputStream: public Stream { ... };

        class OutputStream: public Stream { ... };

        class IOStream: public InputStream, public OutputStream { ... };

    Now suppose the Stream class has a data member called File, so IOStream will inherit two copies of File in the above declaration, one from each of the base classes.
    If that is not what you want, we can make the class a *virtual base class*.

        class Stream { ... };

        class InputStream: virtual public Stream { ... };

        class OutputStream: virtual public Stream { ... };

        class IOStream: public InputStream, public OutputStream { ... };

##  Explain how do we implement virtual functions using the Non-Virtual Interface (NVI) idiom?

    NVI idiom is based on the principal that virtual functions should always be private, and is called through a public member function. For example, consider the following class :

        class Base {
          public:
            int publicMethod() const {
                ...                             // do “before” stuff
                int retVal = virtualMethod();   // do the real work
                ...                             // do “after” stuff
                return retVal;
            }

          private:
            virtual int virtualMethod() const {
                ...
            }
        };

        class Derived {
          private:
            virtual int virtualMethod() const {
                ...
            }
        };


    So the derived classes don't redefine the `publicMethod()` but only the private `virtualMethod()`. This design where clients call private virtual functions indirectly through public non-virtual member functions is known as the non-virtual interface (NVI) idiom.
    An advantage of the NVI idiom is suggested by the “do ‘before’ stuff” and “do ‘after’ stuff” comments in the code. This means that the wrapper ensures that before a virtual function is called, the proper context is set up, and after the call is over, the context is cleaned up. For example, the “before” stuff could include locking a mutex, etc, and similarly the “after” stuff.

    Note that the new idea here is having a private virtual method. This is allowed, and thus private virtual functions can be overridden in the derived classes. Methods of derived classes can't call virtual functions from the base class, but they can provide their own implementation for them.

## How can you replace virtual functions using function pointers?

    We can make a function pointer as a data member in our class, which can be initialized as an argument, say to the constructor. So at runtime, the call to function pointer will be resolved which will call the actual function.
    The disadvantage of this technique is that the actual function would be pushed outside of the class, and thus would not be able to access the internal parts of the object, and only access the public interface. So this technique is not always applicable.

    Even better than function pointer is to use `tr1::function`. The advantage is that it can hold any callable entity (function pointer, function object, or member function pointer). So more like a generalized function pointer. For example,

        std::tr1::function<int (const someClass&)> functionObject;

    This shows that `functionObject` will hold a function which takes a `const someClass&` and returns an `int`.
