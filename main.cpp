#include <iostream>
#include "MV.hpp"
#include "Predefined.hpp"

using namespace std;
using namespace Module1;

int main()
{
    Point<2> p = {-3, 2};

    Matrix<2> m = {{-1,-3},{1,2}};

    auto m1 = E3 * 2;
    cout << m1 << endl;

    return 0;
}
