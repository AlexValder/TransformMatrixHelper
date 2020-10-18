#include <iostream>
#include "Matrix.hpp"

using namespace std;
using namespace Module1;

int main()
{
    float arr[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    Matrix<3> mtrx(arr);
    Vector<3> vec(arr[0]);

    cout << "M = " << mtrx << endl
           << "V = " << vec << endl;

    cout << "M * M = " << (mtrx * mtrx) << endl;
    cout << "V * M = " << (vec * mtrx) << endl;
    cout << "M * V = " << (mtrx * vec) << endl;

    return 0;
}
