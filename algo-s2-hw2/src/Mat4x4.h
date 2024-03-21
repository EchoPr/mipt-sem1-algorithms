#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <algorithm>
#include "Vec4.h"

#define ROWS 4
#define COLS 4
#define DIM 4


template <class T>
class Matrix
{
public:
    Matrix()
    {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                data[i][j] = 0;
    }
    Matrix(T value)
    {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                data[i][j] = value;
    }

    template <class K>
    Matrix(Matrix<K> other)
    {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                data[i][j] = static_cast<T>(other(i, j));
    }

    ~Matrix(){};

    T &operator()(unsigned r, unsigned c)
    {
        if (r >= ROWS || c >= COLS)
            throw std::runtime_error("Index out of range!");

        return data[r][c];
    }
    Matrix operator+(Matrix<T> other)
    {
        Matrix<T> tmp;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                tmp(i, j) = data[i][j] + other(i, j);

        return tmp;
    }
    Matrix operator-(Matrix<T> other)
    {
        Matrix<T> tmp;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                tmp(i, j) = data[i][j] - other(i, j);

        return tmp;
    }
    Matrix operator*(const T &other)
    {
        Matrix<T> tmp;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                tmp(i, j) = data[i][j] * other;

        return tmp;
    }
    Matrix operator/(const T &other)
    {
        if (other == 0)
            throw std::runtime_error("Deviding by zero!");

        Matrix<T> tmp;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                tmp(i, j) = data[i][j] / other;

        return tmp;
    }
    Matrix operator*(Matrix<T> other)
    {
        Matrix<T> tmp;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
            {
                tmp(i, j) = data[i][j] * other(i, j);
            }

        return tmp;
    }

    float det()
    {
        float res = 0;

        int per[] = {0, 1, 2, 3};
        do
        {
            int N = inversions_perms(per, 4);
            int mult = 1;
            for (int i = 0; i < 4; i++)
                mult *= data[i][per[i]];

            res += (N % 2 == 0 ? 1 : -1) * mult;
        } while (std::next_permutation(per, per + 4));

        return res;
    }
    Matrix<float> inverse()
    {
        Matrix<float> tmp(*this);
        tmp.transpose();

        float det = tmp.det();

        if (det == 0)
            throw std::runtime_error("Determinant is zero!");

        return tmp / det;
    }

    Matrix &transpose()
    {
        for (int i = 0; i < ROWS; i++)
            for (int j = i; j < COLS - i; j++)
                std::swap(data[i][j], data[j][i]);

        return *this;
    }
    Matrix dot(Matrix<T> other)
    {
        Matrix<T> tmp;
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
            {
                for (int r = 0; r < 4; r++)
                    tmp(i, j) += data[i][r] * other(r, j);
            }

        return tmp;
    }

    Vec4<T> dot(Vec4<T> vec)
    {
        Vec4<T> tmp;
        for (int i = 0; i < COLS; i++)
            for (int j = 0; j < DIM; j++)
            {
                tmp[i] += vec[j] * data[j][i];
            }

        return tmp;
    }

    template <class Type>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<Type> &op);

private:
    T data[ROWS][COLS];

    int inversions_perms(int (&comb)[], int n)
    {
        int ans = 0;

        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (comb[i] > comb[j])
                    ans++;

        return ans;
    }
};

template <class T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &op)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            os << op.data[i][j] << ' ';
        os << std::endl;
    }

    return os;
}

#endif