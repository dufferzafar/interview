import sys

# Question is similar to LCS: O(n^2) DP
# and Edit Distance?


def cerr(*args):
    print(*args, file=sys.stderr)


def is_abbr(a, b):
    """Return true if a can be modified to be made equal to b."""

    m, n = len(a), len(b)

    # Size is m * n (+1 because of 0-length)
    # dp[i][j] is 1 iff a[:i] can be made equal to b[:j]
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # First row & First column form the base cases?

    # Empty strings are equal!
    dp[0][0] = 1
    for i in range(1, m + 1):
        dp[i][0] = int(dp[i - 1][0] and a[i - 1].islower())

    # The general case
    for i in range(1, m + 1):
        for j in range(1, n + 1):

            if a[i - 1].islower():

                if a[i - 1].upper() == b[j - 1]:
                    dp[i][j] = dp[i - 1][j] or dp[i - 1][j - 1]
                else:
                    dp[i][j] = dp[i - 1][j]

            elif a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]

    cerr("\n".join([" ".join(map(str, r)) for r in dp]))

    return dp[m][n]


if __name__ == "__main__":
    q = int(input().strip())
    for _ in range(q):
        a = input().strip()
        b = input().strip()

        if is_abbr(a, b):
            print("YES")
        else:
            print("NO")
