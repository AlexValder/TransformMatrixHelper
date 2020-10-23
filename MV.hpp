#pragma once
#include "Matrix.hpp"
#include "Vector.hpp"

namespace Module1 {

    template <int N>
    Matrix<N> operator*(const Vector<N>& v1, const Vector<N>& v2) {
        Matrix<N> result;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                result[i][j] += v1[i] * v2[j];
        return result;
    }

    template <int N>
    Vector<N> operator*(const Vector<N>& v, const Matrix<N>& m) {
        Vector<N> result;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                result[i] += v[j] * m[j][i];
        return result;
    }

    template <int N>
    Vector<N> operator*(const Matrix<N>& m, const Vector<N>& v) {
        Vector<N> result;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                result[i] += v[i] * m[j][i];
        return result;
    }

    template <int N>
    Point<N> operator*(const Point<N>& v, const Matrix<N>& m) {
        Point<N> result;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                result[i] += v[j] * m[j][i];
        return result;
    }

    template <int N>
    Point<N> operator*(const Matrix<N>& m, const Point<N>& v) {
        Point<N> result;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                result[i] += v[j] * m[i][j];
        return result;
    }

    Matrix<3> FindTransformMatrix(Point<2> before[3], Point<2> after[3])
    {
        auto ret = Matrix<3>
        {
            {before[0][0], before[0][1], 1},
            {before[1][0], before[1][1], 1},
            {before[2][0], before[2][0], 1}
        }.inverse() * Matrix<3>
        {
            {after[0][0], after[0][1], 1},
            {after[1][0], after[1][1], 1},
            {after[2][0], after[2][0], 1}
        };
        return ret;
    }
}
