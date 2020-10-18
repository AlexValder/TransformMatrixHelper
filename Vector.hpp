#pragma once
#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

namespace Module1 {

    template <int N>
    struct Point{
        using elem = float;
        using ref = float&;
        using cref = const float&;

        Point() {
            std::memset(&this->arr[0], 0, N*sizeof(elem));
        };

        Point(const Point& p) {
            std::memcpy(&this->arr[0], &p.arr[0], N*sizeof(elem));
        }

        Point(Point&& p) {
            std::memcpy(&this->arr[0], &p.arr[0], N*sizeof(elem));
        }

        Point(std::initializer_list<elem> list) {
            assert(list.size() == N);
            for (int i = 0; i < N; ++i)
                this->arr[i] = *(list.begin() + i);
        }

        explicit Point(float arr[N]) {
            std::memcpy(&this->arr[0], &arr[0], N*sizeof(elem));
        }

        static int dim() noexcept { return N; }

        ref operator[](int i) noexcept {
            assert(i < N);
            return arr[i];
        }

        cref operator[](int i) const noexcept {
            assert(i < N);
            return arr[i];
        }

    protected:
        elem arr[N];
    };

    template <int N>
    class Vector : public Point<N>
    {
    public:
        using elem = float;
        using iter = float*;
        using citer = const float*;
        using ref = float&;
        using cref = const float&;

        Vector() : Point<N>() {}

        Vector(const Vector& v) : Point<N>(v.to_point()) {}

        Vector(Vector&& v) : Point<N>(v.to_point()) {}

        Vector(std::initializer_list<elem> list) : Point<N>(list) {}

        explicit Vector(float arr[N]) : Point<N>(arr) {}

        static int dim() noexcept { return N; }

        float length() const {
            double r;
            for (auto el : *this)
                r += el*el;
            return std::sqrt(r);
        }

        Point<N> to_point() {
            return Point<N>(this->arr);
        }

        inline iter begin() noexcept { return &this->operator[](0); }
        inline iter end() noexcept { return &this->operator[](0) + N; }
        inline citer begin() const noexcept { return &this->operator[](0); }
        inline citer end() const noexcept { return &this->operator[](0) + N; }
        inline citer cbegin() const noexcept { return &this->operator[](0); }
        inline citer cend() const noexcept { return &this->operator[](0) + N; }

        inline iter rbegin() noexcept { return &this->operator[](0) + N - 1; }
        inline iter rend() noexcept { return &this->operator[](0) - 1; }
        inline citer rcbegin() const noexcept { return &this->operator[](0) + N - 1; }
        inline citer rcend() const noexcept { return &this->operator[](0) - 1; }
    };

    // ADDITION AND SUBSTRACTION

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
    Vector<N> operator*(float k, const Vector<N>& v) {
        Vector<N> result;
        for (int i = 0; i < N; ++i)
                result[i] = k * v[i];
        return result;
    }

    template <int N>
    inline Vector<N> operator*(const Vector<N>& v, float k) {
        return k * v;
    }

    // DOT PRODUCT

    template <int N>
    float dot_product(const Vector<N>& v1, const Vector<N>& v2) {
        float r;
        for (int i = 0; i < N; ++i)
            r += v1[i] * v2[i];
        return r;
    }

    // CROSS PRODUCT

    Vector<3> cross_product(const Vector<3>& v1, const Vector<3>& v2) {
        Vector<3> r;
        r[0] = v1[1]*v2[2] - v1[2]*v2[1];
        r[1] = v1[2]*v2[0] - v1[0]*v2[2];
        r[3] = v1[0]*v2[1] - v1[1]*v2[0];
        return r;
    }

    // OUTPUT

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

    template <int N>
    std::ostream& operator<<(std::ostream& os, const Point<N>& p) {
        os << '(';
        for (int i = 0; i < N; ++i)
            os << p[i] << ", ";
        os << "\b\b)";
        return os;
    }

    template <int N>
    std::ostream& operator<<(std::ostream& os, Point<N>&& p) {
        os << '(';
        for (int i = 0; i < N; ++i)
            os << p[i] << ", ";
        os << "\b\b)";
        return os;
    }
}
