
# Fast I/O in C++

Two major optimizations on I/O:

The first one is enabled by placing this line in the beginning of the program, before any input/output:

`ios_base::sync_with_stdio(false);`

This command turns off iostreams and stdio synchronization (description). It is on by default, which means that calls to iostreams and stdio functions can be freely interleaved even for the same underlying stream. When synchronization is turned off, mixing calls is no longer allowed, but iostreams can potentially operate faster.

The second optimization is about untying cin from cout:

`cin.tie(NULL);`

By default, cin is tied to cout, which means that cout is flushed before any operation on cin (description). Turning this feature off allows iostreams, again, to operate faster. One should be careful with this optimization in interactive problems: it should either not be used, or an explicit flush should be issued each time.

Also note that frequent use of endl also negatively affects iostreams performance, because endl not only outputs a newline character, but also flushes the stream's buffer (decription). You can simply output '\n' or "\n" instead of endl.

## Links

* http://codeforces.com/blog/entry/5217

* https://bitbucket.org/andreyv/cppiotest/src/tip/iotest.cpp?fileviewer=file-view-default

* https://github.com/hthuwal/competitive-programming/tree/master/IO%20and%20speed%20comparaisons
