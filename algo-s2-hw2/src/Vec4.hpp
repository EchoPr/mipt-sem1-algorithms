#include <algorithm>
#include "Vec4.h" 

// Constructors
template <class T>
Vec4<T>::Vec4()
{
    for (int i = 0; i < DIM; i++)
        data[i] = 0;
}

template <class T>
Vec4<T>::Vec4(T value)
{
    for (int i = 0; i < DIM; i++)
        data[i] = value;
}

// Operators
template <class T>
T& Vec4<T>::operator[](unsigned index)
{
    if (index >= DIM)
        throw std::runtime_error("Index out of range!");

    return  data[index];
}

template <class T>
Vec4<T> Vec4<T>::operator*(const T& other)
{
    Vec4<T> tmp;
    for (int i = 0; i < DIM; i++)
        tmp[i] = data[i] * other;

    return tmp;
}

template <class T>
Vec4<T> Vec4<T>::operator/(const T& other)
{
    if (other == 0)
        throw std::runtime_error("Deviding by zero!");

    Vec4<T> tmp;
    for (int i = 0; i < DIM; i++)
        tmp[i] = data[i] / other;

    return tmp;
}

template <class T>
Vec4<T> Vec4<T>::operator*(Vec4<T> other)
{
    Vec4<T> tmp;
    for (int i = 0; i < DIM; i++)
        tmp[i] = data[i] * other[i];

    return tmp;
}

template <class T>
Vec4<T> Vec4<T>::operator+(Vec4<T> other)
{
    Vec4<T> tmp;
    for (int i = 0; i < DIM; i++)
        tmp[i] = data[i] + other;

    return tmp;
}

template <class T>
Vec4<T> Vec4<T>::operator-(Vec4<T> other)
{
    Vec4<T> tmp;
    for (int i = 0; i < DIM; i++)
        tmp[i] = data[i] - other[i];

    return tmp;
}


// Other functions
template <class T>
std::ostream& operator<<(std::ostream& os, const Vec4<T>& op)
{
    for (int i = 0; i < DIM; i++)
        os << op.data[i] << ' ';
    os << std::endl;

    return os;
}
