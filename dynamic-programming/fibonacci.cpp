int fibonacci(int n) {
    int a = 0, b = 1, c;
    while (--n > 0) {
        c = a+b; a = b; b = c;
    }

    return c;
}
