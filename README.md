# XOR Linked List (C++)

Implementation of an **XOR Linked List** in modern C++ with full iterator support.  
This data structure is a memory-efficient variant of a doubly linked list, where each node stores the XOR of the previous and next node addresses instead of two separate pointers.

## Features
- Templated container (`XORLinkedList<T>`)
- Forward and reverse iterators (`Iterator`, `ReverseIterator`)
- Copy / Move constructors and assignments
- Standard modifiers:
  - `push_back`, `push_front`
  - `pop_back`, `pop_front`
  - `insert(pos, val)`
  - `erase(pos)`
  - `clear`
- Accessors:
  - `front`, `back`
  - `empty`, `getSize`
- `operator<<` for stream output
- Compatible with STL algorithms (`std::for_each`, range-based for loops)

## Build & Run
```bash
g++ -std=c++20 -Wall -Wextra -O2 main.cpp -o xorlist
./xorlist
```
## Notes

- The implementation uses raw pointers and manual memory management for educational purposes.  
- Iterators are bidirectional and can be used in STL algorithms.  
- This project is intended as a demonstration of pointer arithmetic and XOR tricks, not as a production container.
