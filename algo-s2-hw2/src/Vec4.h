#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include "Mat4x4.h"

#define DIM 4


template <class T>
class Vec4
{
public:
    Vec4()
    {
        for (int i = 0; i < DIM; i++)
            data[i] = 0;
    }

    Vec4(T value)
    {
        for (int i = 0; i < DIM; i++)
            data[i] = value;
    }

    template <class K>
    Vec4(Vec4<K> other)
    {
        for (int i = 0; i < DIM; i++)
            data[i] = other[i];
    }

    ~Vec4(){};

    T &operator[](unsigned index)
    {
        if (index >= DIM)
            throw std::runtime_error("Index out of range!");

        return data[index];
    }
    Vec4 operator+(Vec4<T> other)
    {
        Vec4<T> tmp;
        for (int i = 0; i < DIM; i++)
            tmp[i] = data[i] + other;

        return tmp;
    }
    Vec4 operator-(Vec4<T> other)
    {
        Vec4<T> tmp;
        for (int i = 0; i < DIM; i++)
            tmp[i] = data[i] - other[i];

        return tmp;
    }

    Vec4 operator*(const T &other)
    {
        Vec4<T> tmp;
        for (int i = 0; i < DIM; i++)
            tmp[i] = data[i] * other;

        return tmp;
    }
    Vec4 operator/(const T &other)
    {
        if (other == 0)
            throw std::runtime_error("Deviding by zero!");

        Vec4<T> tmp;
        for (int i = 0; i < DIM; i++)
            tmp[i] = data[i] / other;

        return tmp;
    }
    Vec4 operator*(Vec4<T> other)
    {
        Vec4<T> tmp;
        for (int i = 0; i < DIM; i++)
            tmp[i] = data[i] * other[i];

        return tmp;
    }

    Vec4<T> dot(Matrix<T> mat){
        Vec4<T> tmp;
        for(int i = 0; i < COLS; i++){
            for(int j = 0; j < DIM; j++){
                tmp[i] += data[j] * mat(j, i);
            }
        }
        return tmp;
    }

    template <class Type>
    friend std::ostream &operator<<(std::ostream &os, const Vec4<Type> &op);

private:
    T data[ROWS];
};

template<class T>
std::ostream &operator<<(std::ostream &os, const Vec4<T> &op)
    {
        for (int i = 0; i < DIM; i++)
            os << op.data[i] << ' ';
        os << std::endl;

        return os;
    }

#endif