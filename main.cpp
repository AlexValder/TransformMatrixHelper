#include <iostream>
#include "MV.hpp"
#include "Predefined.hpp"

using namespace std;
using namespace Module1;

int main()
{
    Point<2> p = {-3, 2};

    Matrix<2> m = {{-1,-3},{1,2}};

    cout << m << endl;
    cout << p << endl;
    cout << m * p << endl;
    cout << p * m << endl;

    cout << m.inverse() << endl;

    return 0;
}
