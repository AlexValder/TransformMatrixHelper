#include <iostream>
#include "MV.hpp"
#include "Predefined.hpp"

using namespace std;
using namespace Module1;

int main()
{
    Point<2> before[3] = { {-4, 2}, {-3,-1}, {-1,1} };
    Point<2> after[3] = { {2,3}, {4,-1}, {-1,5} };

    auto t = FindTransformMatrix(before, after);
    cout << t << endl;

    system("pause");

    return 0;
}
