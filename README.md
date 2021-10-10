# DS (Data Structure)
`DS` is a C library that contains a [`HashTable`](https://www.youtube.com/watch?v=2Ti5yvumFTU) and a [`LinkedList`](https://www.youtube.com/watch?v=VOpjAHCee7c). Currently in progress.

## Dependency
- [GCC](https://gcc.gnu.org/)
- make

## Development environment
This project is developed in Linux environment (Gentoo). 

## DOCUMENTATION
All naming convention are specified in [`Style.md`](Style.md). The documentation of each function are written in header files. 

## Trying out
Make sure the [dependency](#dependency) is fulfilled. Git clone this repo (`git clone https://github.com/RechieKho/ds.git`). Run `make`. The binary will be output in the `bin/` directory. Edit the `src/main.c` and try out the `HashTable` and `LinkedList`. Most of the time, you do not need to worry about the header dependency as the `Makefile` will calculate the depencency for you (with the help of `gcc` compiler). 