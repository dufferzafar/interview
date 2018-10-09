

vow = {"a", "e", "i", "o", "u"}


def difference_array(strArr, query):

    diff = [0] * (len(strArr) + 1)

    # Build difference array
    for i, s in enumerate(strArr):
        if s[0] in vow and s[-1] in vow:
            diff[i + 1] = diff[i] + 1
        else:
            diff[i + 1] = diff[i]

    res = []
    for q in query:
        l = int(q[0]) - 1
        r = int(q[-1])

        res.append(diff[r] - diff[l])

    return res


def bruteforce(strArr, query):

    res = []

    for q in query:
        l = int(q[0]) - 1
        r = int(q[-1])

        cnt = 0
        for s in strArr[l:r]:
            if s[0] in vow and s[-1] in vow:
                cnt += 1

        res.append(cnt)

    return res


if __name__ == '__main__':

    S = ['aab', 'a', 'bcd', 'awe', 'bbbbbu']
    Q = ['1-1', '1-4', '1-3', '2-5', '1-5']

    print(S)
    print(bruteforce(S, Q))
    print(difference_array(S, Q))

    print()

    S = ['yy', 'u', 'oe']
    Q = ['1-3', '2-3', '3-3']
    print(S)
    print(bruteforce(S, Q))
    print(difference_array(S, Q))

    print()

    S = ['aba', 'bcb', 'ece', 'aa', 'e']
    Q = ['1-5', '2-5', '2-2']
    print(S)
    print(bruteforce(S, Q))
    print(difference_array(S, Q))

