Snorlax Standard Lib
====================

```sh
$ cmake -DCMAKE_BUILD_TYPE=Debug -B build
```


```sh
cmake --build build --target all
```

```sh
valgrind --leak-check=full ./build/snorlax-std-check
```