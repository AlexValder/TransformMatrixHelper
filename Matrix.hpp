#pragma once
#include <iostream>
#include <cassert>
#include <cstring>

namespace Module1 {

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
            std::memset(&this->arr[0][0], 0, N*N*sizeof(elem));
        };

        Matrix(std::initializer_list<std::initializer_list<elem>> elems) {
            for (int i = 0; i < N; ++i) {
                auto list = elems.begin() + i;
                for (int j = 0; j < N; ++j) {
                    this->arr[i][j] = *(list->begin() + j);
                }
            }
        }

        explicit Matrix(float arr[N][N]) {
            std::memcpy(&this->arr[0][0], &arr[0][0], N*N*sizeof(elem));
        }

        Matrix(const Matrix& m) {
            std::memcpy(&this->arr[0][0], &arr[0][0], N*N*sizeof(elem));
        }

        Matrix(Matrix&& m) {
            std::memcpy(&this->arr[0][0], &arr[0][0], N*N*sizeof(elem));
        }

        static int dim() noexcept { return N; }

        inline float deter() const {
            return determinantOfMatrix(this->arr, N);
        }

        Matrix adjoint() const {
           Matrix adj;

           if (N == 1) {
              adj[0][0] = 1;
              return adj;
           }

           int s = 1;
           elem t[N][N];

           for (int i = 0; i < N; ++i) {
              for (int j = 0; j < N; ++j) {
                 getCofactor(this->arr, t, i, j, N);
                 s = (i + j) % 2 == 0 ? 1 : -1;
                 adj[j][i] =  s *(determinantOfMatrix(t, N - 1));
              }
           }
           return adj;
        }

        Matrix inverse() const {
            const auto det = this->deter();
            if (det == 0) throw std::runtime_error("Cannot make an inveser matrix: determinant is zero.");

            Matrix inv;

            auto adj = this->adjoint();
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    inv[i][j] = adj[i][j] / det;
            return inv;
        }

        Matrix get_t() const {
            Matrix t;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    t[j][i] = this->arr[i][j];
            return t;
        }

        iter operator[](int i) noexcept {
            assert(i < N);
            return arr[i];
        }

        citer operator[](int i) const noexcept {
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

        static void getCofactor(const elem mat[N][N], elem temp[N][N], int p, int q, int n)
        {
            int i = 0, j = 0;
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != p && col != q) {
                        temp[i][j++] = mat[row][col];
                        if (j == n - 1) {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        static elem determinantOfMatrix(const elem mat[N][N], int n)
        {
            int D{};
            if (n == 1)
                return mat[0][0];

            elem temp[N][N];

            int sign = 1;
            for (int f = 0; f < n; f++) {
                getCofactor(mat, temp, 0, f, n);
                D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
                sign = -sign;
            }

            return D;
        }
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

    // MULTIPLICATION

    template <int N>
    Matrix<N> operator*(const Matrix<N>& m, float k) {
        Matrix<N> result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                result[i][j] = m[i][j] * k;
    }

    template <int N>
    inline Matrix<N> operator*(float k, const Matrix<N>& m) {
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

}
