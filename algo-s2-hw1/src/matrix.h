#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

#define USHORT unsigned short

#define ROWS 4
#define COLS 4

template <class T>
class Matrix
{
public:

    Matrix();
    Matrix(T);
    
    template <class K>
    Matrix(Matrix<K> other)
    {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                data[i][j] = static_cast<T>(other(i, j));
    }

    ~Matrix(){};

    T& operator()(unsigned, unsigned);
    Matrix operator+(Matrix&);
    Matrix operator-(Matrix);
    Matrix operator*(const T &);
    Matrix operator/(const T&);
    Matrix operator*(Matrix);

    float det();    
    Matrix<float> inverse();
    Matrix& transpose();

    template <class Type>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<Type>& op);
    

private:
    T data[ROWS][COLS];
};

#endif