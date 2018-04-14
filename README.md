## Tools in C++

[![Build Status](https://travis-ci.org/vasumahesh1/tools.svg?branch=master)](https://travis-ci.org/vasumahesh1/tools)

An array of tools that I am making as a part of learning various game engine architectures.

### Includes

- **StackAllocator**

  A Stack based memory allocator.

- **PoolAllocator\<T\>**

  A Pool based memory allocator for any datatype T.

- **MonotonicAllocator\<alignment\>**

  A Sequential Memory Allocator.

- **Allocator**

  A Base class from which all custom allocators are derived.

- **MemoryBuffer**

  A Base class for creating and handling memory. MemoryBuffer's main role is to give the `Allocator`s a buffer to write data to. It is upto the allocator on how to use the memory buffer, but a segment of it is given to it. Think of this as a allocating a huge chunk of memory, and splitting it into parts for different allocators with different alignment needs to end up using it.

- **FNVHashOperator** or **FNVHash**

  A FNV1A Hashing Implementation. A `constexpr` implementation.

- **HashMap\<K, V\>**

  A HashMap that uses a FNV1A Hash (Can have a custom `HashOperator` if needed) chaining. Also, uses a `PoolAllocator` for allocating the LinkedList if needed for chaining.

- **Vector\<T\>**
  
  A Vector that uses a custom `Allocator` for allocating and deallocating objects. C++17 does offer a pmr allocator (polymorphic allocator) allowing us to create a std::vector with a custom allocator (while avoiding the templating issue at the same time). But this tool is meant to work with C++14/11, so I have a minimal implementation of a Vector. It also includes a `std::iterator` (random access iterator, available as `Vector<Type>::Iterator`), so it can be used with regular std algorithms like `std::sort`.

For now you can see the `tests/` to see how they are implemented.

### Running the Code

I use [GoogleTest](https://github.com/google/googletest) to test the code and C++14 to compile them. To run this on your system, you need CMake.

#### Linux / OSX

Execute these to build & run tests:
```bash
cd build
cmake .. && make
ctest
```

#### Windows

Make sure you launch using the Cross Tools for VS. I built it on VS2017.

```batch
cd scripts
BuildDebug_Win32.bat
```


