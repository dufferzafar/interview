"""Print all permutations."""

# There's a better algorithm that only stores indices on stack


def __permutations(string, perm):
    if not string:
        if perm:
            print(perm)
        return

    for i, ch in enumerate(string):
        __permutations(string[:i] + string[i + 1:], perm + ch)


def permutations(string):
    __permutations(string, "")


if __name__ == '__main__':
    permutations("ABCD")
