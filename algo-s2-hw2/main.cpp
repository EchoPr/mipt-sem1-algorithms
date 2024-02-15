#include <iostream>
#include "src/mat_lib.hpp"


int main(){
    Vec4<float> a;
    std::cout << a << std::endl;

    for(int i = 0; i < 4; i++) a[i] = i;
    std::cout << a << std::endl;

    Matrix<float> m(1);
    std::cout << m << std::endl;

    std::cout << dot(a, m) << std::endl;
    std::cout << dot(m, a) << std::endl;
}
