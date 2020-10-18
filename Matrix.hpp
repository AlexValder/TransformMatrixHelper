#pragma once
#include <iostream>
#include <cassert>
#include <cstring>

namespace Module1 {

    template  <int N>
    class Vector
    {
    public:
        using elem = float;
        using iter = float*;
        using citer = const float*;
        using ref = float&;
        using cref = const float&;

        Vector() {
            std::memset(&this->arr[0], 0, N*sizeof(float));
        };

        Vector(const Vector& v) {
            std::memcpy(&this->arr[0], &v.arr[0], N*sizeof(float));
        }

        Vector(Vector&& v) {
            std::memcpy(&this->arr[0], &v.arr[0], N*sizeof(float));
        }

        explicit Vector(float arr[N]) {
            std::memcpy(&this->arr[0], &arr[0], N*sizeof(float));
        }

        static int length() noexcept { return N; }

        ref operator[](size_t i) noexcept {
            assert(i < N);
            return arr[i];
        }

        cref operator[](size_t i) const noexcept {
            assert(i < N);
            return arr[i];
        }

        inline iter begin() noexcept { return &arr[0]; }
        inline iter end() noexcept { return &arr[0] + N; }
        inline citer begin() const noexcept { return &arr[0]; }
        inline citer end() const noexcept { return &arr[0] + N; }
        inline citer cbegin() const noexcept { return &arr[0]; }
        inline citer cend() const noexcept { return &arr[0] + N; }

        inline iter rbegin() noexcept { return &arr[0] + N - 1; }
        inline iter rend() noexcept { return &arr[0] - 1; }
        inline citer rcbegin() const noexcept { return &arr[0] + N - 1; }
        inline citer rcend() const noexcept { return &arr[0] - 1; }
    private:
        elem arr[N];
    };

    template<int N>
    class Matrix
    {
    public:
        using elem = float;
        using iter = float*;
        using citer = const float*;
        using ref = float&;
        using cref = const float&;

        Matrix() {
            std::memset(&this->arr[0][0], 0, N*N*sizeof(float));
        };

        explicit Matrix(float arr[N][N]) {
            std::memcpy(&this->arr[0][0], &arr[0][0], N*N*sizeof(float));
        }

        Matrix(const Matrix& m) {
            std::memcpy(&this->arr[0][0], &arr[0][0], N*N*sizeof(float));
        }

        Matrix(Matrix&& m) {
            std::memcpy(&this->arr[0][0], &arr[0][0], N*N*sizeof(float));
        }

        static int dim() noexcept { return N; }

        iter operator[](size_t i) noexcept {
            assert(i < N);
            return arr[i];
        }

        citer operator[](size_t i) const noexcept {
            assert(i < N);
            return arr[i];
        }

        inline iter begin() noexcept { return &arr[0][0]; }
        inline iter end() noexcept { return &arr[0][0] + N*N; }
        inline citer begin() const noexcept { return &arr[0][0]; }
        inline citer end() const noexcept { return &arr[0][0] + N*N; }
        inline citer cbegin() const noexcept { return &arr[0][0]; }
        inline citer cend() const noexcept { return &arr[0][0] + N*N; }

        inline iter rbegin() noexcept { return &arr[0][0] + N*N - 1; }
        inline iter rend() noexcept { return &arr[0][0] - 1; }
        inline citer rcbegin() const noexcept { return &arr[0][0] + N*N - 1; }
        inline citer rcend() const noexcept { return &arr[0][0] - 1; }

    private:
        elem arr[N][N];
    };

    // ADDITION AND SUBSTRACTION

    template <int N>
    Matrix<N> operator+(const Matrix<N>& m1, const Matrix<N>& m2) {
        Matrix<N> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                result[i][j] = m1[i][j] + m2[i][j];
        return result;
    }

    template <int N>
    Matrix<N> operator-(const Matrix<N>& m1, const Matrix<N>& m2) {
        Matrix<N> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                result[i][j] = m1[i][j] - m2[i][j];
        return result;
    }

    template <int N>
    Vector<N> operator+(const Vector<N>& v1, const Vector<N>& v2) {
        Vector<N> result;
        for (int i = 0; i < N; ++i)
            result[i] = v1[i] + v2[i];
        return result;
    }

    template <int N>
    Vector<N> operator-(const Vector<N>& v1, const Vector<N>& v2) {
        Vector<N> result;
        for (int i = 0; i < N; ++i)
            result[i] = v1[i] - v2[i];
        return result;
    }

    // MULTIPLICATION

    template <int N>
    Matrix<N> operator*(const Matrix<N>& m, float k) {
        Matrix<N> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                result[i][j] = m[i][j] * k;
    }

    template <int N>
    Matrix<N> operator*(float k, const Matrix<N>& m) {
        return m * k;
    }

    template <int N>
    Matrix<N> operator*(const Matrix<N>& m1, const Matrix<N>& m2) {
        Matrix<N> result;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int r = 0; r < N; ++r)
                    result[i][j] += m1[i][r] * m2[r][j];
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

    // OUTPUT

    template <int N>
    std::ostream& operator<<(std::ostream& os, const Matrix<N>& m) {
        os << '[';
        for (int i = 0; i < N; ++i) {
            os << '(';
            for (int j = 0; j < N; ++j)
                os << m[i][j] << ", ";
               os << "\b\b)"; if (i != N - 1) os << '\n';
        }
        return os << ']';
    }

    template <int N>
    std::ostream& operator<<(std::ostream& os, Matrix<N>&& m) {
           os << '[';
           for (int i = 0; i < N; ++i) {
               os << '(';
               for (int j = 0; j < N; ++j)
                   os << m[i][j] << ", ";
               os << "\b\b)"; if (i != N - 1) os << '\n';
           }
           return os << ']';
    }

    template <int N>
    std::ostream& operator<<(std::ostream& os, const Vector<N>& v) {
        os << '(';
        for (int i = 0; i < N; ++i)
            os << v[i] << ", ";
        os << "\b\b)";
        return os;
    }

    template <int N>
    std::ostream& operator<<(std::ostream& os, Vector<N>&& v) {
        os << '(';
        for (int i = 0; i < N; ++i)
            os << v[i] << ", ";
        os << "\b\b)";
        return os;
    }
}
