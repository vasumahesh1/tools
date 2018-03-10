## Tools in C++

[![Build Status](https://travis-ci.org/vasumahesh1/tools.svg?branch=master)](https://travis-ci.org/vasumahesh1/tools)

An array of tools that I am making as a part of learning various game engine architectures.

### Includes

- **StackAllocator**
  A Stack based memory allocator.

- **PoolAllocator<T>**
  A Pool based memory allocator for any datatype T.

For now you can see the `tests/` to see how they are implemented.

### Running the Code

I use [GoogleTest](https://github.com/google/googletest) to test the code and C++14 to compile them. To run this on your system, you need CMake.

Execute these to run tests:
```bash
cd build
cmake .. && make
ctest
```


