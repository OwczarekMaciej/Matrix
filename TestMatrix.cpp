#include <iostream>
#include "Matrix.h"


int main(int argc, char const *argv[])
{
    Matrix mtx1(3,3);
    std::cout << mtx1 << std::endl;
    Matrix mtx2(3,3);
    std::cout << mtx2 << std::endl;

    Matrix mtx3(3,3);
    mtx3 = mtx1 + mtx2;
    std::cout << mtx3 << std::endl;
    // std::cout << std::boolalpha;
    // std::cout << (mtx1 == mtx2) << std::endl;
    // std::cout << (mtx1 != mtx3) << std::endl;
    
    return 0;
}
