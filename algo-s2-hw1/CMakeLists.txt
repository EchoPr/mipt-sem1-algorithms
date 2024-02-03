cmake_minimum_required(VERSION 3.0.0)
project(algo-s2-hw1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(algo-s2-hw1 main.cpp
    src/matrix.hpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
