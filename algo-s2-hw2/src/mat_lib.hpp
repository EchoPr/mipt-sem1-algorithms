#ifndef UTILS_H
#define UTILS_H

#include "Mat4x4.hpp"
#include "Vec4.hpp"


template<class T>
Vec4<T> dot(Vec4<T> vec, Matrix<T> mat){
    Vec4<T> tmp;
    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < DIM; j++){
            tmp[i] += vec[j] * mat(j, i);
        }
    }
    return tmp;
}

template<class T>
Vec4<T> dot(Matrix<T> mat, Vec4<T> vec){
    Vec4<T> tmp;
    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < DIM; j++){
            tmp[i] += vec[j] * mat(j, i);
        }

    return tmp;
}


#endif