#include <iostream>
#include "src/Mat4x4.h"


int main(){
    Vec4<float> a;
    std::cout << a << std::endl;

    for(int i = 0; i < 4; i++) a[i] = i;
    std::cout << a << std::endl;

    Matrix<float> m(1);
    std::cout << m << std::endl;

    std::cout << a.dot(m) << std::endl;
    std::cout << m.dot(a) << std::endl;
}
