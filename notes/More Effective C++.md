This page contains notes for the book More Effective C++: 35 New Ways to Improve Your Programs and Designs by Scott Meyers.

## What is static and dynamic type of pointer and reference?

The static type of a pointer or reference is its declared type. The dynamic type is determined by the type of object it actually refers to.

        Base* bPtr   = new Derived;    // Static type of ptr is Base*, dynamic type is Derived*
        Base& bRef = *(new Derived); // Static type of bRef is Base, dynamic type is Derived

## Point out some differences between pointers and references.

- There is no null reference.
The following is a corner case whose behaviour is undefined:

        char *pc = 0;
        char& rc = *pc;

- References must be initialized but pointers can be uninitialized, even though risky.

        int& intRef;    // Error, since uninitialized

- Pointers can be reassigned but references cannot.


## Will you use a reference or a pointer as return type for implementing operator[]?

This operator typically needs to return something that can be used as the target of an assignment.

    v[5]  = 10;        // If implemented through references
    *v[5] = 10;        // If implemented through pointers

Thus we prefer references as return type here.

## What are the modern C++ style casts?

The problem with the conventional C style casts is that they are hard to locate, and also difficult to point out the exact nature of case. Hence, we have the modern C++ style casts:

- static_cast :
It has basically the same power and meaning as the general-purpose C-style cast. It also has the same kind of restrictions. For example, you can’t cast a struct into an int or a double into a pointer using static_cast any more than you can with a C-style cast.

        double result = static_cast<double>(firstNumber)/secondNumber;

- const_cast :
By using a const_cast, you can remove the constness of an object. Note that adding constness is done using the static cast.

        Base * bPtr = new Derived;
        someFunction(const_cast<Dervied *>(bPtr));    // Error because const cast can only affect constness or volatileness


- dynamic_cast :
It is used to cast pointers or references to base class objects into pointers or references to derived or sibling base class objects in such a way that you can determine whether the casts succeeded. Failed casts are indicated by a null pointer (when casting pointers) or an exception (when casting references)

        int x = 5;
        double y = dynamic_cast<double> (x);    //  Error! int has no virtual functions

- reinterpret_cast :
The result of this cast is almost always implementation defined, and thus is rarely portable. One use case is when casting between function pointer types.



## What does the keyword *volatile* mean?

Volatile is a qualifier that when applied to a variable tells the compiler that the value of this variable may change at any time-without any action being taken by the code the compiler finds nearby. Thus, such objects are omitted from optimization. Also, the system always reads the current value of a volatile object from the memory location rather than keeping its value in temporary register at the point it is requested, even if a previous instruction asked for a value from the same object.

For a use case, consider the following code:

    quit = 0;
    while (!quit)
    {
            /* very small loop which is completely visible to the compiler */
    }

The compiler is allowed to notice the loop body does not touch the `quit` variable and convert the loop to a `while(true)` loop. Even if the quit variable is set on the signal handler for `SIGINT` and `SIGTERM` the compiler has no way to know that.

However, if the `quit` variable is declared volatile, the compiler is forced to load it every time, because it can be modified elsewhere. This is exactly what you want in this situation.


##  Consider the following code and find error:

    void printBaseArray(ostream& s, const Base array[], int numElements) {
        for (int i = 0; i < numElements; ++i) {
            s << array[i];         // Assumes operator<< is defined for Base
        }
    }

    Dervied derivedArray[10];
    printBaseArray(cout, derivedArray, 10);


So note that what we are doing is passing an array of derived class objects to a function which requires array of base class objects. Remember that `array[i]` is really just shorthand for an expression involving pointer arithmetic: it stands for `*(array+i)`. Thus difference between the addresses of `array[i]` and `array[0]` is `i*sizeof(an object of Base)` but each object in the array is actually of size of a Derived. Thus the results will be undefined.

**Tip: ** We are unlikely to make the mistake of treating an array polymorphically if we avoid having a concrete class inherit from another concrete class. We would see more benefits of following this tip later.

##  Point out some restrictions on classes which do not have a default constructor.

Default constructors initialize objects without any information from the place where the object is being created.  Therefore,  if a class lacks a default constructor, there are restrictions on how you can use that class. Consider the following class:

    class Student {
        public:
        Student(int ID);
        ...
    };

Because Student lacks a default constructor, its use may be problematic in the following contexts.

- There is, in general, no way to specify constructor arguments for objects in arrays, so it is not usually possible to create arrays of Student objects:

        Student studArray[10];                     // error! No way to call ctors
        Student *studList = new Student[10];  // error! Same problem

    The possible work arounds are:

        Student studArray[] = {0, 1, 2, ..., 9};

        Student ** studList = new (Student*)[10];
        for (int i = 0; i < 10; i++)
            studList[i] = new Student(i);

    The problems with the second method is that we need extra space for the pointers, and we need to deallocate all the objects ourselves otherwise will lead to memory leaks.

    Other workaround exists using *placement new*, can be read from book page 37.

- Virtual base classes lacking default constructors are a difficult to work with because all classes derived from that class — no matter how far removed — must know about, understand the meaning of, and provide for the virtual base class’s constructors’ arguments.

##  What is the difference between prefix and postfix increment operator? Why is prefix believed to be more efficient than postfix operator?

For an integer `i` with value 5, `i++` will increment `i` to 6 but will return 5 whereas `++i` will also increment i to 6 and return 6.

        int i = 5;
        cout << i++ << endl;        // Will print 5
        cout << ++i << endl;        // Will print 7

So as can be seen intuitively, the postfix operator has to create a temporary object (which stores the old value for returning. This temporary needs to be constructed and destructed, whereas the prefix increment operator would need no such temporaries. Therefore, when dealing with **user-defined types**, prefix increment should be used whenever possible, because it’s inherently more efficient.

To read more about actual implementation of prefix and postfix operators, read item 6 from page 47.

##  What do you mean by short circuiting of expression evaluation?

    It means that once the truth or falsehood of an expression has been determined, evaluation of the expression ceases, even if some parts of the expression haven’t yet been examined. Both C and C++ employ short-circuit evaluation property.

##  What is comma operator, explain with one use case?

Most common use case of comma operator is the for loop:

        for(int i = 0, j = 10; i < j; ++i, --j) { ... }

    An expression containing a comma is evaluated by first evaluating the part of the expression to the left of the comma, then evaluating the expression to the right of the comma; the result of the overall comma expression is the value of the expression on the right. So in the final part of the loop above, compilers first evaluate `++i` , then `--j`, and the result of the comma expression is the value returned from `--j`.

##  Based on the above two properties, why should we never overload `&&`, `||`, and `,` ?

Say if we overload the `&&` operator, the following line of code

        if (expression1 && expression2) ...

will get converted to

        if (operator&&(expression1, expression2)) ...

by the compiler. So now we need to deal with function call semantics. The two important semantics are that all the parameters are evaluated before calling the function, and the order of evaluation of these arguments is implementation dependent. So this means that we cannot force a strict left-to-right order of evaluation on  `expression1` and `expression2` for short circuiting.

Similar is the problem with comma operator, where we need to evaluate the left hand expression before the right hand expression.

##  Try to understand the following code. What are the problems associated with this technique?

    class Rational {
        public:
        ...
        Rational(int num, int den);
        operator double() const;
    };

Here we have declared an implicit type conversion operator, which will be called when we cast a *Rational* object to *double*.

    Rational r(1, 2);          // r has the value 1/2
    double d = 0.5 * r;        // converts r to a double and then does multiplication

The fundamental problem with these kind of functions is implicit casts when not required. For example, consider the following code

    Rational r(1, 2);
    cout << r;

So if we have not defined `operator<<` for *Rational*, rather than giving an error the compiler would implicitly convert the object to a double, which might not be required.

##  How will you solve the above problem?

The solution is to replace the operators with equivalent functions that don’t have the syntactically magic names.

    class Rational {
        public:
        ...
        Rational(int num, int den);
        double asDouble() const;
    };

    Rational r(1, 2);
    cout << r;                         // Error!

    cout << r.asDouble();        // No error

Thus the implicit function calls are not possible now. So that is why the std::string type  contains no implicit conversion from a string object to a C-style char* . Instead, there is an explicit member function, `c_str` , that performs that conversion.

##  Mention some problems faced by single argument constructors in classes with regard to implicit type conversions. Also mentioned the solution provided by C++ for these problems.

Consider the following code

    class Array {
        public:
        Array(int size);
        ...
    };


    Array a(5);
    a = 10;

So here the last instruction is equivalent to

    a = static_cast<Array>(10);

Such a cast is hard to locate, and also inefficient at times because we are creating and destroying temporary `Array` objects. So implicitly casting the parameters to class objects is creating problem for us.

The solution provided by C++ is the `explicit` keyword.  Constructors can be declared explicit, and if they are, compilers are prohibited from invoking them for purposes of implicit type conversion. Explicit conversions are still legal.

    class Array {
        public:
        explicit Array(int size);
        ...
    };

    Array a(5);
    a = 10;                            // Implicit conversion will give error
    a = static_cast<Array>(10);        // Explicit conversion gives no error

##  How will you solve the above problem using a Proxy Class?

Consider the following solution and try to understand it.

    class Array {
        public:

        class ArraySize {
            public:
            ArraySize(int numElements): theSize(numElements) {}
            int size() const { return theSize; }

            private:
            int theSize;
        };

        Array(ArraySize size);
        ...
    };

    Array a(5);        // No error, implicit conversion of 10 into a temporary ArraySize object

    a = 10;            // Error, think reason?

In the last command, we get an error because compilers cannot consider converting the int into a temporary ArraySize object and then creating the necessary Array object from this temporary, because that would call for two user-defined conversions, one from int to ArraySize and one from ArraySize to Array. Such a conversion sequence is forbidden because no sequence of conversions is allowed to contain more than one user-defined conversion. Thus will give an error.

So such tricks are at the heart of proxy classes(here ArraySize), whose objects stand as a proxy for some other objects.Proxy objects can give you control over aspects of your software’s behavior — in this case implicit type conversions — that is otherwise beyond your grasp. We will learn more about them later.

##  What is the 80-20 rule?

The 80-20 rule states that 80 percent of a program’s resources are used by about 20 percent of the code: 80 percent of the runtime is spent in approximately 20 percent of the code, 80 percent of the memory is used by some 20 percent of the code, and so on. The fundamental point is that the overall performance of your software is almost always determined by a small part of its constituent code.

The 80-20 rule also means that improving random parts of the program is unlikely to help very much. Rather than intuitively guessing the bottleneck, we should  empirically identify the relevant 20 percent of your program using a program profiler.
Remember that a profiler can only tell you how a program behaved on a particular run (or set of runs), so make sure your input data set is representative of how the software is used by its clients.

##  What is the difference between `new operator`, `operator new` and `operator new[]`?

When we write code like this,

    string *ps = new string("Memory Management");

the new we are using is the `new operator`. It does two tasks. First, it allocates enough memory to hold an object of the type requested. In the example above, it allocates enough memory to hold a string object. Second, it calls a constructor to initialize an object in the memory that was allocated. So this is how it is different from `malloc` which only allocates the memory.
Note that we cannot overload the `new operator`.

The `new operator` calls a function to perform the requisite memory allocation called as operator new.

    void *rawMemory = operator new(sizeof(string));

Thus `operator new` is like `malloc`, and can be overloaded.

Some times we use `new operator` to allocate an array.

    string *ps = new string[10];         // allocate an array of objects

The `new` being used is still the `new operator`, but because an array is being created, it is allocated by the array-allocation equivalent, a function called `operator new[]`. Also  like `operator new` , `operator new[]` can be overloaded.

##  What is `placement new` operator?

In some scenarios it becomes necessary to place objects at specified locations in memory. For example, we have already allocated some memory buffer and we need the object to be constructed exactly in that buffer, then we use placement new. Placement new is achieved by overloading the *operator new* which takes the memory location apart from the default size_t argument.

        void * operator new(size_t, void *location) {
        return location;
    }

So remember that the  purpose of *operator new* is to find memory for an object and return a pointer to that memory. But since here the user already knows the memory location where the object needs to be placed, all placement new has to do, then, is return the pointer that is passed into it.

The way to call this *placement new* is shown in the following example:

        void someCode()  {
            char memory[sizeof(Fred)];
            void* p = memory;
            Fred* f = new(p) Fred();        // Calling the placement new operator

            // ...

            f->~Fred();                       // Explicitly call the destructor for the placed object
    }

Note that the user is taking sole responsibility that the pointer you pass to the “placement new” operator points to a region of memory that is big enough and is properly aligned for the object type that you’re creating. Neither the compiler nor the run-time system make any attempt to check whether the user did this right. Thus don’t use this “placement new” syntax unless you have to.

If you use *placement new* to create an object in some memory, you should avoid using the *delete operator* on that memory. That’s because the *delete operator* calls *operator delete* to deallocate the memory, but the memory containing the object was not allocated by *operator new* in the first place. Instead, you should undo the effect of the constructor by explicitly calling the object’s destructor, and the person who allocated the memory would himself look after deallocating it.

##  What is the difference between `delete operator`, `operator delete` and `operator delete[]`?

The meanings are very synonymous. So when you call

    delete obj;            // The delete operator

It automatically gets broken down to two steps:

    ps->~string();                 // call the object’s dtor
    operator delete(ps);        // deallocate the memory

Again the `operator delete[]` is used to deallocate memory when we use `delete operator` on an array in the following manner:

    delete [] objectArray;

So the `delete operator` would call destructor for each array element, and  then calls `operator delete[]` to deallocate the memory.

##  What are the C++ equivalent of `malloc` and `free`?

`operator new` and `operator delete` are the C++ equivalent of malloc and free respectively. Thus always remember that calling free on a `new`ed pointer yields undefined behavior, as does deleteing a `malloc`ed pointer.

##  Say we have defined `operator+` for a class, does that mean we can use the `operator+=` too?

We cannot do that. Both these operators need to be defined separately. A good practice would be to defined one in terms of the the other so that we only need to maintain and update the latter and the former automatically gets updated.

##  Who do you think would be generally faster, `operator+=` or `operator+`?

In general, the assignment versions of operators (like `+=`) are more efficient than stand-alone (like `+`) versions, because stand-alone versions must typically return a new object, and that costs us the construction and destruction of a temporary. Assignment versions of operators write to their left-hand argument, so there is no need to generate a temporary to hold the operator’s return value.

Thus there is a trade-off between

    result = a + b + c + d;        // Probably uses 3 temporary objects

and

    result  = a;
    result += b;                // No temporary needed
    result += c;
    result += d;

The former is easier to write, debug, and maintain, and it offers acceptable performance whereas the latter is more efficient.

##  How would you write `printf("%10.5f", d);` using `cout`?

We can use `setw()` and `setprecision()` for that

    cout << setw(10)                            // Set field width
            << setprecision(5)                        // Set decimal places
            << setiosflags(ios::showpoint)        // Keep trailing 0s
            << setiosflags(ios::fixed)                // Use these settings
            << d;

##  Is such a function definition allowed in C++?

    const SomeClass operator+(int lhs, int rhs);

One of the rules of C++ is that every overloaded operator must take at least one argument of a user-defined type. `int` is not a user-defined type, so we can’t overload an operator taking only arguments of that type. If this rule did not exist, programmers would be able to change the meaning of predefined operations, and that can lead to chaos.

##  Consider the following 3 function candidates :
    - `void someFunction(string str);`
- `void someFunction(string & str);`
- `void someFunction(const string & str);`

<Qu>Which of the above functions will give an error if we call it using

    char someCharArray[] = "I am Kiera";
    someFunction(someCharArray);

    This call can succeed only if the type mismatch can be eliminated by the compilers by creating a temporary object of type string and initializing it with the passed charArray. This will lead to construction and destruction of a temporary but is worth it. These conversions occur only when passing objects by value (case 1) or a reference-to-const parameter (case 3) and not when when passing using reference-to-non-const parameter (case 2).

The reason is simple, if the temporary was created in case 2, then the changes in the temporary will not be reflected back to the original array. Thus case 2 will give an error.

**Comment** : Such temporaries usually arise in two cases:  when implicit type conversions are applied to make function calls succeed and when functions return objects.

##  What is return value optimization?

Consider the following function:

    Widget MakeWidget()
    {
        Widget w;

        ...

        return w;
    }

It can be seen that we can avoid the need to copy the local variable w by constructing it in the memory alloted for the function’s return value. This is known as the return value optimization (RVO), and it’s been explicitly mentioned by the C++ Standard.
The compilers may perform RVO if (1) the type of the local object is the same as that returned by the function and (2) the local object is what’s being returned.

##  What is lazy evaluation? Explain using the example of string and matrix class.

Employing lazy evaluation means writing your code in such a way that it defers computations until the results of those computations are required. If the results are never required, the computations are never performed. Consider the following examples:

- Consider the string copy constructor which gets invoked in such a case:

        String s1 = "Hello";
        String s2 = s1;

    A common implementation for the String copy constructor would result in s1 and s2 each having its own copy of “Hello” by allocating heap memory via the new operator and calling `strcpy` to copy the data in s1 into the memory allocated by s2 . This is *eager evaluation*: making a copy of s1 and putting it into s2 just because the String copy constructor was called.
    Note that since we do not need s2 right now, we could have simply did a little book keeping right now so we know who’s sharing what, and in return we save the cost of a call to new and the expense of copying anything. Also by doing this we can also perform all read operations easily as long as none of the two strings need to be modified.

        s1.convertToUpperCase();

    So for such modify operations,  we have to implement them so that it makes a copy of s2 ’s value and
privately modify s1.

- Consider a program that uses large objects containing many constituent fields, which need to be repeatedly read and written to files in databases. Thus rather than performing large read operations every time this object is accessed by bringing in the entire object, just read the relevant fields when required and delay the complete object read till it is actually required. Details regarding this example can be read from book.

- Consider the example of matrix class.

        Matrix<int> m1(1000, 1000),  m2(1000, 1000);
        ...
        Matrix<int> m3 = m1 + m2;

    So rather than performing the addition right away (1,000,000 additions), it would be faster to sets up a data structure inside m3 that indicates that m3 ’s value is the sum of m1 and m2, say by storing a pointer to each of m1 and m2 , plus an enum indicating that the operation on them is addition. This way, when we need to access particular part of m3 (say the second row m3[1]), we only need to compute that part. So doing this way can make the user feel that all the operations are occurring at run time with no delay.

So note that we need to  maintain data structures that can store values, dependencies, or a combination of the two and to overload operators like assignment, copying, and addition. Thus lazy evaluation is a lot of work, but practically, it often ends up saving significant amounts of time and space during program runs without any change for the user.

A simple trick that uses lazy evaluation is to **declare and define immediately prior to use**.

Mainstream programming languages like C++ employ eager evaluation internally,  but several languages — notably APL, some dialects of Lisp, and virtually all dataflow languages — embrace the idea as a fundamental part of the language.

##  What is mutable keyword? Can you solve the problem handled by mutable without using mutable?

Sometimes there is requirement to modify one or more data members of class / struct through const function even though you don’t want the function to update other members of class / struct. This task can be easily performed by using mutable keyword.

    class Customer {
        name[25];
        mutable char placedorder[50];

        public:
        void changePlacedOrder(char* p) const {
                strcpy(placedorder, p);
        }
    }

    The idea of const functions is not allow them to modify the object on which they are called. It is recommended practice to make as many functions const as possible so that accidental changes to objects are avoided.  When we declare a function as const, the `this` pointer passed to function becomes pointer to constant. Adding mutable to a variable allows even such a pointer to change members. So another way to do the same would be

    void Customer::changePlacedOrder(char* p) const {
        Customer * const fakeThis = const_cast<Customer* const>(this);
        strcpy(fakeThis->placedorder, p);
    }

So if we use this `fakeThis` approach, we don't need to declare the variables as mutable because we have cast away the constness of the *this.

**Note : ** `const` class objects can only explicitly call `const` member functions.

##  What is the difference between

        int * const ptr;

<Qu>    and

        const int * ptr;

<Qu>    in C++?

The first one is a constant pointer i.e. a pointer that cannot change the address its holding and the second is a pointer to a constant i.e. a pointer through which one cannot change the value of variable it points to.

##  What is the type of a `this` pointer?

The type of this in a member function of a `class X` is `X*`, and if the member function is declared `const`, the type of this is `const X*`.

##  Does caching help amortize the cost of expected computations?

Caching can help reduce the average cost of computations that need to be performed repeatedly. But since it requires the overhead of maintaining a data structure(say a map), it should be preferred for calculations that are performed multiple times.
For     example, say we need to repeatedly look up names of students by their roll numbers. So we can maintain a map `int->string ` which helps us in these lookups and in the average case, the cost of reading and modifications would be constant.

##  What is locality of reference?

    Experience has shown that if data in one place is requested, it’s quite common to want nearby data, too. This is the infamous locality of reference phenomenon, and systems designers rely on it to justify disk caches, memory caches for both instructions and data, and instruction pre-fetches.

##  Can we directly link and run object files compiled from C code and C++ code together?

We cannot combine such files unless the different compilers agree on implementation-dependent features like the size of ints and doubles, the mechanism by which parameters are passed from caller to callee, and whether the caller or the callee arrange the parameter passing. These details can only be confirmed by the vendors. For more on how to combine C and C++ code, refer to item 34 from book.

##  What is name mangling and how can we suppress it in C++? Does C have name mangling?

Name mangling is the process through which your C++ compilers give each function in your program a unique name, which is useful for function overloading. This is not done in C because you can not overload function names in C. Note that different compilers mangle function names in different ways.
To suppress name mangling, use C++’s extern "C" directive:

    extern "C"
    void drawLine(int x1, int y1, int x2, int y2);

It means that the function should be called as if it were written in C, thus name mangling is automatically suppressed.

**Comment : **  The preprocessor symbol `__cplusplus` is defined only for C++ compilations. Thus you can write code like `#ifdef __cplusplus` to check if we are compiling for C++.

##  What is static initialization and static destruction? Can you suggest some way to implement this?

The constructors of static class objects and objects at global, namespace, and file scope are usually called before the body of main is executed. This process is known as static initialization. Similarly, objects that are created through static initialization must have their destructors called after main has finished executing. This process is called static destruction.

Since program execution is supposed to begin with main, many compilers insert a call to a special compiler-written function at the beginning and ending of main for static initialization and destruction as illustrated below.

    int main(int argc, char *argv[]) {
        performStaticInitialization();
        ...
        performStaticDestruction();
    }

For exact details on how our compiler implements it, compiler documentation can be referred.

##  What is the use of `this` pointer in classes?

When a member function for a class is called,  C++ utilizes a hidden `this` pointer to keep track of which object it was called on.

    class Simple {
        int m_id;

        public:
        void setID(int id) { m_id = id; }
    };


    Simple simpleObj;
    simpleObj.setID(2);

The above code would automatically gets converted to something like the following by the compiler transparent to the programmer.

    class Simple {
        int m_id;

        public:
        void setID(Simple* const this, int id) { this->m_id = id; }        // Modified
    };


    Simple simpleObj;
    setID(&simpleObj, 2);    // Note that simpleObj has been changed from an object prefix to a function argument!

Thus when the compiler compiles a normal member function, it implicitly adds a new parameter to the function named `this`. The this pointer is a hidden const pointer that holds the address of the object the member function was called on.

##  What is a virtual table, explain with diagram using the following class:

    class C1 {
        public:
        C1();
        virtual ~C1();
        virtual void f1();
        virtual int f2(char c) const;
        virtual void f3(const string& s);
        void f4() const;
        ...
    };

Every class that uses virtual functions (or is derived from a class that uses virtual functions) is given its own virtual table. This table is simply a static array that the compiler sets up at compile time. A virtual table contains one entry for each virtual function that can be called by objects of the class. Each entry in this table is simply a function pointer that points to the most-derived function accessible by that class.

    <img style='width: 400px' src="https://image.ibb.co/e5zbFR/Vtable.png"></img>

Note that the nonvirtual function f4 is not in the table, nor is C1 ’s constructor.

##  What is virtual pointers or *vptr*?Show how the vtbl and vptr will look like for the following classes:

    class Base {
        public:
        virtual void function1() {};
        virtual void function2() {};
    };

    class D1: public Base {
        public:
        virtual void function1() {};
    };

    class D2: public Base {
        public:
        virtual void function2() {};
    };

Each object whose class declares virtual functions carries with it a hidden data member that points to the virtual table for that class. Thus in the above case, the compiler will add a vptr to the  most base class  that uses virtual functions which is Base and this will automatically be inherited by the derived classes. Thus the base class will look something like

    class Base {
        public:
        FunctionPointer *__vptr;
        virtual void function1() {};
        virtual void function2() {};
    };

The following diagram shows how the virtual table will look like for the above classes. Because there are only two virtual functions here, each virtual table will have two entries (one for function1(), and one for function2()) pointing to the most-derived function implementation which an object of that class type can call.

<img style='width: 500px' src="https://image.ibb.co/gjRCpm/VTable.gif"></img>

##  For the above classes, can you briefly explain how the following code will work?

    int main() {
        D1 d1;
        Base *dPtr = &d1;
        dPtr->function1();
    }

We create an object d1 of class D1, thus d1 has it’s __vptr set to the D1's virtual table. Next note that because dPtr is a base pointer, it only points to the Base portion of d1. However, also note that __vptr is in the Base portion of the class, so dPtr has access to this pointer.
When we make a call to function1(), first, the program recognizes that function1() is a virtual function. Second, the program uses dPtr->__vptr to get to D1’s virtual table. Third, it looks up which version of function1() to call in D1’s virtual table. This has been set to D1::function1(). Therefore, dPtr->function1() resolves to D1::function1().

##  What are the costs of using virtual functions?

- We have to set aside space for a virtual table for each class that contains virtual functions.
- We have to pay for an extra pointer inside each object that is of a class containing virtual functions.
- Calling a virtual function is slower than calling a non-virtual function for a couple of reasons: First, we have to use the *__vptr to get to the appropriate virtual table. Second, we have to index the virtual table to find the correct function to call. Only then can we call the function. As a result, we have to do 3 operations to find the function to call, as opposed to 2 operations for a normal indirect function call, or one operation for a direct function call.
- Virtual functions cannot be inlined.

##  Why can virtual functions not be inlined?

That is because “inline” means “during compilation, replace the call site with the body of the called function,” but “virtual” means “wait until runtime to see which function is called.” If the compilers don’t know which function will be called at a particular call site, it cannot inline the function call. This also leads to a hit to performance for the virtual functions.

##  Do abstract classes need virtual tables?

Since vtables are only accessed by class objects and abstract classes have no objects, thus vtables are unecessary for abstract classes and are generally removed.

##  What is RTTI and what is its use?

RTTI (stands for runtime type identification) lets us discover type information about objects and classes at runtime. That information is stored in an object of type type_info, and we can access the type_info object for a class by using the
typeid operator.

    const type_info& t_someVar = typeid(someVar);
    printf("Type Info of someVar = %s", t_someVar.name());

The purpose and implementations in similar to the virtual function implementation, thus can be implemented using the vtabl of class by adding an extra entry for the `type_info` object.

<img style='width: 400px' src="https://image.ibb.co/ka9nN6/Vtable2.png"></img>

##  What does an object of any class look like?

Static class members are treated almost exactly like global variables / functions. Because they are not tied to an instance, there is nothing to discuss regarding memory layout. Class member variables are duplicated for each instance as you can imagine, as each instance can have its own unique values for every member variable. Class member functions only exist once in a code segment in memory, and rather than each object knowing the function, the function knows the object by passing the this pointer.

When a class inherits from another, then the object layout will start with its base class, which in turn may start with a base class of its own. Following the base's area (its members) will be the derived class's members in turn, with an undefined amount of padding between them. When a class inherits from more than one base then things become a little different. The base areas are laid out in memory sequentially. Base1 followed by Base2, etc. after which the derived class's members are laid out in turn with an undefined amount of padding between them.

If the class (or one of its base classes) contain any virtual methods, the layout generally starts with vptr, i.e a pointer to a virtual table (or vtable) which is a table of pointers to function implementations related to that class.

##  How does an object of a class look like when we virtually inherit from base classes? For example, consider the object of class D in the following example:

    class A { ... };
    class B: virtual public A { ... };
    class C: virtual public A { ... };
    class D: public B, public C { ... };

When storing the data members of an object of class D, we need to store additional pointers to virtual base class as shown in the following diagram.

<img style='width: 300px' src="https://image.ibb.co/d41Cpm/Diamond.png"></img>

The pointers are required so that when we do `B* ptr = new D()`, we can access the object using `ptr` as if it is an object of class B. Thus we need a way to reach class A's data members. If we would have not used virtual inheritance, then both B and C would have had their own copies of A, ie. B::A and C::A. Thus in earlier cases, such extra pointers were not needed.

##  Say you have a `Matrix` class and you want to overload the `operator<<` for this class, how will you do it?

The canonical way to implement operator<< for any type is this:

    std::ostream& operator<<(std::ostream& out, const Matrix& obj) {
            out<< obj.Mat[i][j];  // stream obj's data into os
        return out;
    }

Binary operators like `operator<<` can either be members of their left-hand argument's class or free functions. (Some operators, like assignment, must be members.) Since the stream operators' left-hand argument is a stream, stream operators either have to be members of the stream class or free functions.
Sometimes you want to stream objects whose internals are not accessible through their class' public interface, so the operator can't get at them. Then you have two choices: Either put a public member into the class which does the streaming

    class Matrix {
        public:
        void stream_to(std::ostream&) const {os << Mat[i][j];}
        private:
            int Mat[100][100];
    };

and call that from your implementation of `operator<<`. The other way is to make the operator a friend so that it can access the class' private parts.

    class T {
        public:
        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        private:
            int Mat[100][100];
    };

##  What do you understand by virtual constructor? How will you implement a virtual copy constructor?

    A virtual constructor is a function that creates different types of objects depending on the input it is given.
A virtual copy constructor returns a pointer to a new copy of the object invoking the function. The following is one possible implementation:

    class Base {
        public:
        virtual Base * clone() const = 0;    // declaration of virtual copy constructor
    };

    class Derived: public Base {
        public:
        virtual Derived * clone() const {            // virtual copy constructor
            return new Derived(*this);
        }
    };

    Base * objPtr1 = new Dervied;
    Base * objPtr2 = objPtr1->clone();

A class’s virtual copy constructor just calls its real copy constructor, thus both will be consistent. Notice that the above implementation uses a recent feature that no longer must a derived class’s redefinition of a base class’s virtual function declare the same return type. Instead, if the function’s return type is a pointer (or a reference) to a base class, the derived class’s function may return a pointer (or reference) to a class derived from that base class.

##  How can you limit the object count of a class to one?

The first idea to do this is to keep a static count of objects instantiated in the constructor, and when the count becomes more than 1, throw an exception.

    class Printer {
        public:
        Printer() {
            if (numObjects >= 1) throw Exception();
            // Normal construction here
            numObjects++;
        }
        ~Printer() {
            // Normal destruction
            numObjects--;
        }
            private:
            static unsigned int numObjects;
            Printer(const Printer& rhs); // there is a limit of 1 printer, so never allow copying
    };

The problem with such a technique is that other classes can derive from such a base class. Thus when we make instances of derived classes too, they will increment the count which might not be required.

    Base bObj;
    Dervied dObj;    // Throws exception

The easiest way to prevent objects of a particular class from being created is to declare the default constructor of that class private and delete the copy and move constructors. The following is the code that does that:

    class Printer {
        public:
        void reset();
        static Printer& thePrinter();

        Printer(const Printer&) = delete;
        Printer& operator=(const Printer&) = delete;
        Printer(Printer&&) = delete;
        Printer& operator=(Printer&&) = delete;

        private:
        Printer();
    };

    Printer& Printer::thePrinter() {
        static Printer p;
        return p;
    }

    Printer::thePrinter().reset();        // Can directly use the static object

One constraint that comes with making constructors private is that such classes cannot acts as base classes(Think why?). The reason is that the constructor is not inherited, thus the derived classes cannot call the base constructor. Thus the above problem gets solved.

##  Can we declare the `thePrinter()` function inline?

Functions like `thePrinter()` which declare a static object should not be declared inline because if the definition gets replaced at the place of function call, multiple instances of these objects will appear. This is usually against the purpose of declaring objects static.

##  How will you model a class such that you can have any number of objects of that class but no class can derive from it?

The idea is very similar to what we have done above. Simply declare the constructor as private, and make a pseudo constructor which always declares `new` objects on the heap and returns the pointers.

    class FSA {
        public:
        // pseudo-constructors
        static FSA * makeFSA();
        static FSA * makeFSA(const FSA& rhs);
        ...

        private:
        FSA();
        ...
    };

    FSA * FSA::makeFSA() { return new FSA(); }
    FSA * FSA::makeFSA(const FSA& rhs) { return new FSA(rhs); }

One of the problems with doing this is that the objects since allocated on heap need to be `delete`d. So rather than manually calling `delete` every time, we can store the returned pointer in an unique_ptr object. Such objects are automatically deleted when the pointer goes out of scope. Thus keep destructor public because needs to be called from outside.

    std::unique_ptr<FSA> pfsa1(FSA::makeFSA());
    std::unique_ptr<FSA> pfsa2(FSA::makeFSA(*pfsa1));

##  Design a class such that there are at max n objects of the class.

Basically this question means that we can create and destroy objects and at each time, we just want n objects at max. So the solution will be very simple, simply keep a static count variable which keeps the current count of objects. Also make the constructors private to get rid of inheritance problem by making the constructor private. As for constructing new objects, make a pseudo constructor as done above. So we combine all the ideas in the following code:

    class Printer {
            public:
        // pseudo-constructors
        static Printer * makePrinter();
        static Printer * makePrinter(const Printer& rhs);
        ~Printer() {
            numObjects--;
        }
        ...
        private:
        static size_t numObjects;
        static const size_t maxObjects = 10;
        Printer();
        Printer(const Printer& rhs);
        void init();    // To avoid copying code
    };

    size_t Printer::numObjects = 0;
    const size_t Printer::maxObjects;

    void Printer::init() {
        if (numObjects >= maxObjects) throw Exception();
        numObjects++;
    }
    Printer::Printer() { init() }
    Printer::Printer(const Printer& rhs) { init(); }

    Printer * Printer::makePrinter() { return new Printer; }
    Printer * Printer::makePrinter(const Printer& rhs) { return new Printer(rhs); }

##  Using the above concepts, can you model a counting class such that a class which derives from it gets its own object counter with max n objects?

So the concepts should be clear by now. We need to inherit from this class, thus we cannot make the constructor and destuctor private. We cannot make it public as well so that this base class does not have objects of its own. Thus we make it protected. We don't even need the `makeCounted()` for constructing new objects because this is just a base class to derived from.
The other concept is that each class needs its separate counter, thus one static objects won't work. So what we can do is to have a counting class template which will give us a separate static counter variable each time a class derives from it.

    template<class BeingCounted>
    class Counted {
        protected:
        Counted();
        Counted(const Counted& rhs);
        ~Counted() { --numObjects; }
        private:
        static size_t numObjects;
        static const size_t maxObjects;
        void init();
    };

    template<class BeingCounted>
    Counted<BeingCounted>::Counted() { init(); }

    template<class BeingCounted>
    Counted<BeingCounted>::Counted(const Counted<BeingCounted>&) { init(); }

    template<class BeingCounted>
    void Counted<BeingCounted>::init() {
        if (numObjects >= maxObjects) throw TooManyObjects();
        ++numObjects;
    }

Note : Static variables are shared across same instantiations of template in the same translation unit.

##  Can you call `delete this` in a class method?

Doing this is possible but it requires that the object has been allocated using `new()` on heap, and there is no way to **check** this.

##  How will you model a class such that its objects can only be allocated on the heap?

Non-heap objects are automatically constructed at their point of definition and automatically destructed at the end of their lifetime, so it suffices to simply make these implicit construction and destruction illegal.
If make all constructors private, we can make a special function , say `create()` which will allocate a new object each time on heap and return it as done above. But the problem with this technique is that we need do declare all the constructors private, including default and copy constructor too.
The other idea is to declare the destructor private, which is easier because the class only has one destructor. But then how will we destroy the objects constructed on heap? We cannot simply call `delete` because `delete` would not be able to to call the private destructor.
The solution can be to have a pseudo destructor which simply calls `delete this`.

    class SomeClass {
        public:
        SomeClass();
        // pseudo-destructor (a const member function, because
        // even const objects may be destroyed)
        void destroy() const { delete this; }

        private:
        ~SomeClass();
    };

    SomeClass n;                        // Error!
    SomeClass *p = new SomeClass;        // Fine
    delete p;                            // Error!
        p->destroy();                        // Fine

##  How will you model a class such that objects cannot be allocated on heap?

Such objects are always created by calls to `new`, thus we can try to make it impossible for clients to call `new`. Now, we can not affect the availability of the `new operator` (that’s built into the language), but we can take advantage of the fact that the new operator always calls `operator new`. Thus we can declare it private. Unless there’s a compelling reason to split up the pair, it’s best to declare both `operator new` and `operator delete` private. We can declare `operator new[]` and `operator delete[]` private as well.

    class SomeClass {
        private:
        static void *operator new(size_t size);
        static void operator delete(void *ptr);
        ...
    };

    SomeClass n1;                        // Fine
    SomeClass *p = new SomeClass;        // Error!


##  What are containers, iterators and algorithms in STL?

    STL is based on these three fundamental concepts. Containers hold collections of objects, like bitset, vector , list , deque, queue, priority_queue , stack , set, and map. Iterators are pointer-like objects that let you walk through STL containers just as you’d use pointers to walk through built-in arrays. So basically iterators are like generalized templated pointers specialized for different containers. For example, for a linked list the prefix increment operator will move us to the next element in the list.
Algorithms are functions that work on STL containers and that use iterators to help them do their work. For example the following is the generalized algorithm for finding a value in the container.

    template<class Iterator, class T>
    Iterator find(Iterator begin, Iterator end, const T& value) {
        while (begin != end && *begin != value)
            ++begin;
        return begin;
    }
Furthermore, C++ pointers are STL iterators, so the find algorithm above will work with normal arrays too.

    int values[50];
    int *firstFive = find(values, values+50, 5);

**Note : ** STL is extensible, we can add our own collections, algorithms, and iterators to the STL family.

##  Why should we prefer pass by const reference over pass by value?

Each by-value parameter costs us a call to the parameter’s constructor and destructor every time the function is invoked, which can be avoided by using pass-by-reference, which involves no object construction or destruction. Thus when writing generalized templated code, we prefer pass by const reference.

##  How will you implement a 2D array class such that the elements of the array can be accessed using `arrObj[i][j]`?

The important thing to know is that there is no `operator[][]` which could be overloaded, thus we can only overoad `operator[]`to return a special object (say of class Array1D) anad again overload `operator[]` for this class to return the element in our original 2d array.

    template<class T>
    class Array2D {
        public:
        class Array1D {
            public:
            T& operator[](int index);
            const T& operator[](int index) const;
            ...
        };

        Array1D operator[](int index);
        const Array1D operator[](int index) const;
        ...
    };

Objects that stand for other objects are often called proxy objects, and the classes that give rise to proxy objects are often called proxy classes. In this example, Array1D is a proxy class. Its instances stand for one-dimensional arrays that, conceptually, do not exist.

##  How will you model a class for which copying the objects makes no sense?

We can declare the copy constructor and the assignment operator private. The general idea is that **handle assignment and copy construction in every class**, even if no body ever uses those things. Not handling them directy puts the compiler generated functions as effective which might not always be a good thing.

##  What do you mean by double dispatch and how would you implement it?

Double dispatch is the method to implement a function call that’s virtual on two parameters. So note that virtual on a single object type is automatically resolved by the compiler using virtual tables. But double resolution is not provided by default. To understand the problem consider the following example:
Say you have a game in which multiple objects of type `Spaceship`, `SpaceStation`, `Asteriod` exists which inherit from a common abstract class `GameObject`. Now we need to implement a collision method which should be different based on the dynamic type both the colliding objects.

    processCollision(GameObject & object1, GameObject & object2);

If the collision processing depended only on the dynamic type of object1 , you could make `processCollision()` virtual in GameObject and call `object1.processCollision(object2)`. But here collision effect depends on both their dynamic types. We discuss two methods to handle this problem:

- We begin by declaring a virtual function collide in GameObject overidding it in the derived classes. This function through the virtual function mechanism will help us get the correct type of the first object. Inside this method, we discover the real type of `otherObject` using type comparison tests with all possibilities:

        class GameObject {
            public:
            virtual void collide(GameObject& otherObject) = 0;
            ...
        };

        class SpaceShip: public GameObject {
            public:
            virtual void collide(GameObject& otherObject) {
                const type_info& objectType = typeid(otherObject);
                if (objectType == typeid(SpaceShip)) {
                    SpaceShip& ss = static_cast<SpaceShip&>(otherObject);
                    // process a SpaceShip-SpaceShip collision;
                }
                ...
            }
            ...
        };

This method has a problem that if a new type of object — a new class — is added to the game, we must update each RTTI-based if -then -else chain in the program that might encounter the new object type. If we forget even a single one, the program will have a bug. This is the primary reason why virtual functions were invented in the first place: to shift the burden of generating and maintaining type-based function calls from programmers to compilers

- The other method is to implement double-dispatching as two single dispatches, i.e., as two separate virtual function calls: the first determines the dynamic type of the first object, the second determines that of the second object.

        classSpaceShip;        // forward declarations
        class SpaceStation;
        class Asteroid;

        class GameObject {
            public:
            virtual void collide(GameObject& otherObject) = 0;
            virtual void collide(SpaceShip&  otherObject) = 0;
            virtual void collide(SpaceStation& otherObject) = 0;
            virtual void collide(Asteroid& otherobject) = 0;
            ...
        };

        class SpaceShip: public GameObject {
            public:
            virtual void collide(GameObject& otherObject);
            virtual void collide(SpaceShip& otherObject);
            virtual void collide(SpaceStation& otherObject);
            virtual void collide(Asteroid& otherobject);
            ...
        };

        void SpaceShip::collide(GameObject& otherObject) {
            otherObject.collide(*this);        // Think how this works?
        }

As before, the first virtual call is to the collide function taking a GameObject& parameter. In the second function call, compilers figure out that being inside the member function of `Spaceship`, the static type of `*this` must be `Spaceship`. Thus the call is therefore to the collide function taking a `SpaceShip&` , not the collide function taking a `GameObject&`.
Note that the above problem still exists: as new classes are added, the code must be updated and  each class definition must be amended to include a new virtual function. A better way to do this is explained in Item 31 of book where we try to implement the virtual table ourselves for double dispatch.

Note that other languages like CLOS (Common Lisp Object System) supports multiple dispatch, i.e. a method which supports virtual on as many parameters as required.

##  The following are some general tips for good design :

- Preserve consistency with the behavior of the built-in types by providing operators and functions with a natural syntax and intuitive semantics: when in doubt, do as the ints do.
-  Make your classes easy to use correctly and hard to use incorrectly. Accept that clients will make mistakes.
- Design your code so that when changes are necessary, the impact is localized.
- Encapsulate as much as you can; make implementation details private.
- Where applicable, use unnamed namespaces or file-static objects and functions.
- Try to avoid designs that lead to virtual base classes, because such classes must be initialized by every class derived from them even those derived indirectly.
    - Avoid         RTTI-based designs that make use of cascading if -then -else statements. Every time the class hierarchy changes, each set of statements must be updated, and if you forget one, you’ll receive no warning from your compilers.



