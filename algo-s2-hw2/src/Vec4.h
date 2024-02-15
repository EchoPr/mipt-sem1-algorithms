#ifndef VEC4_H
#define VEC4_H

#include <iostream>

#define DIM 4

template <class T>
class Vec4{
public:
    
    Vec4();
    Vec4(T);
    
    template <class K>
    Vec4(Vec4<K> other)
    {
        for (int i = 0; i < DIM; i++)
            data[i] = other[i];
    }

    ~Vec4(){};    

    T& operator[](unsigned);
    Vec4 operator+(Vec4);
    Vec4 operator-(Vec4);
    Vec4 operator*(const T &);
    Vec4 operator/(const T&);
    Vec4 operator*(Vec4);

    template <class Type>
    friend std::ostream& operator<<(std::ostream& os, const Vec4<Type>& op);
    

private:
    T data[ROWS];
};

#endif