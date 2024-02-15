cmake_minimum_required(VERSION 3.0.0)
project(algo-s2-hw2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(algo-s2-hw2 main.cpp
    src/Mat4x4.hpp
    src/Vec4.hpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
