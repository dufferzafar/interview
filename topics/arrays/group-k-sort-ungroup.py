"""
Given an array of n elements and an integer k.

Group the elements in k. And then sort the array.

Ex: [1, 23, 4, 3, 8, 9] and k = 2.
    So number formed are 123, 43, 89.

    Now after sorting, it will be 43, 89, 123.
    So return the array as [4,3,8,9,1,23]

n will always be multiple of k.
"""


def concat_num(lst):
    return (int("".join(map(str, lst))), lst)


def group(lst, k):
    return map(concat_num, [lst[i:i + k] for i in range(0, len(lst), k)])


def ungroup(grps):
    return [n for (_, grp) in grps for n in grp]


def group_sort_ungroup(lst, k):
    return ungroup(sorted(group(lst, k)))


if __name__ == '__main__':
    lst = [1, 23, 4, 3, 8, 9]
    print(group_sort_ungroup(lst, 2))
