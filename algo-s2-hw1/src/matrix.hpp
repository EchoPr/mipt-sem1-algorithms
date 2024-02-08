#include <algorithm>
#include "matrix.h"

// Constructors
template <class T>
Matrix<T>::Matrix()
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            data[i][j] = 0;
}

template <class T>
Matrix<T>::Matrix(T value)
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            data[i][j] = value;
}

// Operators
template <class T>
T& Matrix<T>::operator()(unsigned r, unsigned c)
{
    if (r >= ROWS || c >= COLS)
        throw std::runtime_error("Index out of range!");

    return  data[r][c];
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T& other)
{
    Matrix<T> tmp;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            tmp(i, j) = data[i][j] * other;

    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator/(const T& other)
{
    if (other == 0)
        throw std::runtime_error("Deviding by zero!");

    Matrix<T> tmp;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            tmp(i, j) = data[i][j] / other;

    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> other)
{
    Matrix<T> tmp;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++){
            tmp(i, j) = data[i][j] * other(i, j);
        }

    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> other)
{
    Matrix<T> tmp;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            tmp(i, j) = data[i][j] + other(i, j);

    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> other)
{
    Matrix<T> tmp;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            tmp(i, j) = data[i][j] - other(i, j);

    return tmp;
}

// Functions
template <class T>
Matrix<T> Matrix<T>::dot(Matrix<T> other)
{
    Matrix<T> tmp;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++){
            for(int r = 0; r < 4; r++)
                tmp(i, j) += data[i][r] * other(r, j);
        }

    return tmp;
}

int inversions_perms(int (&comb)[], int n)
{
    int ans = 0;

    for (int i = 0; i < n; ++i) 
        for (int j = i + 1; j < n; ++j) 
            if (comb[i] > comb[j]) 
                ans++;

    return ans;
}

template <class T>
float Matrix<T>::det()
{
    float res = 0;

    int per[] = {0, 1, 2, 3};
    do{
        int N = inversions_perms(per, 4);
        int mult = 1;
        for (int i = 0; i < 4; i++)
            mult *= data[i][per[i]];
        
        res += (N % 2 == 0 ? 1 : -1) * mult;
    } while(std::next_permutation(per, per + 4));

    return res;
}

template <class T>
Matrix<T>& Matrix<T>::transpose()
{
    for (int i = 0; i < ROWS; i++)
        for (int j = i; j < COLS - i; j++)
            std::swap(data[i][j], data[j][i]);
        
    return *this;
}

template <class T>
Matrix<float> Matrix<T>::inverse()
{
    Matrix<float> tmp(*this);
    tmp.transpose();

    float det = tmp.det();
    
    if (det == 0)
        throw std::runtime_error("Determinant is zero!");

    return tmp / det;
}

// Other functions
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& op)
{
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++)
            os << op.data[i][j] << ' ';
        os << std::endl;
    }

    return os;
}
