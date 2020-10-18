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
                result[i] += v[i] * m[j][i];
        return result;
    }
}
