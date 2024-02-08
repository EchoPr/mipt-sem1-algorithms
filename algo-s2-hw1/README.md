# Matrix 4x4
## To build
Folder src contains a [source files](https://github.com/EchoPr/mipt-sem1-algorithms/tree/main/algo-s2-hw1/src) of library
To build a project use [CMake build system](https://cmake.org/)

---
## Using example

Simple using of term-by-term multiplication and matrix product

```c++
Matrix<int> m2(3);
/*
    3 3 3
    3 3 3
    3 3 3
*/

Matrix<int> m3(1);
/*
    1 1 1
    1 1 1
    1 1 1
*/

std::cout << m2 * m3 << std::endl;
/*
    3 3 3
    3 3 3
    3 3 3
*/

std::cout << m2.dot(m3) << std::endl;
/*
    12 12 12
    12 12 12
    12 12 12
*/
```