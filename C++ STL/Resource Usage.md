
# C++ Resource Usage

HackerRank limits memory usage to 512 MB.

## Memory 

|        Container        |  1e6  |  1e7   |   1e8   |
|:-----------------------:|:-----:|:------:|:-------:|
|      `vector<int>`      | 4 MB  | 40 MB  | 400 MB  |
|     `vector<long>`      | 8 MB  | 80 MB  | 800 MB  |
|    `vector<string>`     | 32 MB | 320 MB | 3200 MB |

|         Container          |  1e5   |  1e6  | 1e7 |
|:--------------------------:|:------:|:-----:|:---:|
| `vector< vector<int> > []` | 2.5 MB | 25 MB |  -  |

<!-- | `map< int, pair<int, int> >` | 8 MB  | 80 MB  | 800 MB  | -->

---

* The results are consistent, and exactly what one would expect
    - An `int` takes 4 Bytes. So 10^6 ints take 4 * 10^6 Bytes ~= 4 MB.
    - Same for `long` as it takes 8 Bytes.

    - Going by same numbers, it seems an empty `string` takes 32 Bytes.
        + Need to confirm this somewhere

* Making the vector global or defining it in `main()` was same.
    - Need to test by storing in some other function?


## Time

TODO.
