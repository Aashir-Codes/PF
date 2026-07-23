# Programming Fundamentals in C++

A collection of C++ programs written during my **Programming Fundamentals** course.
The repository is organised topic-by-topic, following the order in which the
concepts were taught — from basic console output all the way to dynamic memory,
pointers, and small end-to-end projects.

Each folder is self-contained and focuses on a single concept, usually built as a
menu-driven program so every exercise can be run and explored interactively.

---

## Topics

| #  | Folder | What's inside |
|----|--------|---------------|
| 01 | [Basic Printing](01-Basic-Printing) | First programs — formatted output, patterns, and simple tasks. |
| 02 | [Problem Solving](02-Problem-Solving) | Logic-building exercises: primes, min/max/middle, Rock–Paper–Scissors. |
| 03 | [Loops](03-Loops) | `for` / `while` / `do-while`, menu-driven programs and a mini-programs collection. |
| 04 | [Arrays](04-Arrays) | 1-D array operations, searching, frequency counting, bubble sort. |
| 05 | [2D Arrays](05-2D-Arrays) | Two-dimensional arrays, traversal, and neighbour lookups. |
| 06 | [Searching and Sorting](06-Searching-and-Sorting) | Classic searching and sorting algorithms. |
| 07 | [Char Arrays and Files](07-Char-Arrays-and-Files) | Character arrays, file I/O, a mini word editor and a grade calculator. |
| 08 | [Pointers](08-Pointers) | Pointer basics, pointer arithmetic, and references. |
| 09 | [Dynamic Memory](09-Dynamic-Memory) | `new`/`delete`, resizable arrays, 2-D and 3-D dynamic allocation. |
| 10 | [Console Animations](10-Console-Animations) | Fun terminal animations (paint brush, Newton & the apple, and more). |
| —  | [Projects](Projects) | Larger programs: a **Chess** game and a **Course Grading System**. |

---

## Building & running

All programs are standard C++ and can be compiled with `g++`:

```bash
g++ path/to/program.cpp -o program
./program
```

> **Note:** A few programs — most of the animations and the Chess project — use
> Windows-specific headers (`<windows.h>`, `<conio.h>`) for console graphics and
> keyboard input, so they are best compiled on Windows (e.g. with MinGW). The
> rest of the code is portable and runs on Linux, macOS, and Windows alike.

---

## About

These are learning exercises, so the emphasis is on understanding the
fundamentals — clean logic, modular functions, and building things from scratch
rather than using standard-library shortcuts.

## License

Released under the [MIT License](LICENSE).
