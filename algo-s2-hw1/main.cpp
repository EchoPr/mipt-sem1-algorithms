#include <iostream>
#include "src/matrix.hpp"

int main()
{
    Matrix<int> m1;
    Matrix<int> m2(3);
    Matrix<int> m3(1);
    Matrix<float> m4(m2);

    // m2(0, 0) = 4;
    // m2(0, 3) = 4;
    // std::cout << m2 + m3 - m1 << std::endl;
    // std::cout << m2 << std::endl;
    // std::cout << m2.transpose() << std::endl;

    // m2.transpose();
    // std::cout << m2.inverse() << std::endl;

    // for(int i = 0; i < ROWS; i++)
    //     m2(i, i) = i + 5;
    // std::cout << m2.inverse() << std::endl;

    // for(int i = 0; i < ROWS; i++)
    //     m1(i, i) = 2;
    // std::cout << m1.inverse() << std::endl;

    std::cout << m2 * m3 << std::endl;
    std::cout << m2.dot(m3) << std::endl;
    



    
}
