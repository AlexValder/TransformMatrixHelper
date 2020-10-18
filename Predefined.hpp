#pragma once
#include "MV.hpp"

#define dTr(deg) static_cast<float>(deg * M_PI / 180.0)
#define rTd(rad) static_cast<float>(rad * 180.0 / M_PI)

namespace Module1 {
    using std::cos, std::sin;

    const auto E3 = Matrix<3>({
                   {1.f, 0.f, 0.f},
                   {0.f, 1.f, 0.f},
                   {0.f, 0.f, 1.f}
                });

    const auto E2 = Matrix<2>({
                   {1.f, 0.f},
                   {0.f, 1.f}
                });

    const auto M_xy = Matrix<3>({
                   { 1.f,  0.f,  0.f},
                   { 0.f,  1.f,  0.f},
                   { 0.f,  0.f, -1.f}
                });

    const auto M_yz = Matrix<3>({
                   {-1.f,  0.f,  0.f},
                   { 0.f,  1.f,  0.f},
                   { 0.f,  0.f,  1.f}
                });

    const auto M_xz = Matrix<3>({
                   { 1.f,  0.f,  0.f},
                   { 0.f, -1.f,  0.f},
                   { 0.f,  0.f,  1.f}
                });

    template <int deg>
    const auto R_x = Matrix<3>({
                   { 1.f,  0.f,  0.f},
                   { 0.f,  cos(dTr(deg)),  sin(dTr(deg))},
                   { 0.f,  -sin(dTr(deg)), cos(dTr(deg))}
                });

    template <int deg>
    const auto R_y = Matrix<3>({
                   { cos(dTr(deg)),  0.f,  -sin(dTr(deg))},
                   { 0.f,  1.f,  0.f},
                   { sin(dTr(deg)), 0.f, cos(dTr(deg))}
                });

    template <int deg>
    const auto R_z = Matrix<3>({
                   {cos(dTr(deg)), sin(dTr(deg)), 0.f},
                   {-sin(dTr(deg)), cos(dTr(deg)), 0.f},
                   {0.f, 0.f, 1.f}
                });
}
