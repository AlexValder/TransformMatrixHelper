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

            // Looping for each element of the matrix
            for (int row = 0; row < n; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    //  Copying into temporary matrix only those element
                    //  which are not in given row and column
                    if (row != p && col != q)
                    {
                        temp[i][j++] = mat[row][col];

                        // Row is filled, so increase row index and
                        // reset col index
                        if (j == n - 1)
                        {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        static elem determinantOfMatrix(const elem mat[N][N], int n)
        {
            int D = 0; // Initialize result

            //  Base case : if matrix contains single element
            if (n == 1)
                return mat[0][0];

            elem temp[N][N]; // To store cofactors

            int sign = 1;  // To store sign multiplier

             // Iterate for each element of first row
            for (int f = 0; f < n; f++)
            {
                // Getting Cofactor of mat[0][f]
                getCofactor(mat, temp, 0, f, n);
                D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);

                // terms are to be added with alternate sign
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
