# Mark and Sweep Garbage Collector in C

A basic garbage collection program.

## Documentation

Visit [docs](https://github.com/briancain/garbage-collection/docs) for more information

## Running the tests

Most of the tests are located in main. Compiling with the make file will be the easiest way to run the tests.

## Using the GC

To use the GC, you simply have to add the garbageCollector.h header file to your C program. Instead of calling malloc, you will use the gcInit hooks. There are several other important garbage collection hooks that you will need to use, so make sure to read the documentation in the docs folder.

## Developers

- [Brian Cain](https://github.com/briancain)
- [Carlos Salazar](https://github.com/razalas)
