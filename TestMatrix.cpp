#include <iostream>
#include "Matrix.h"
#include <fstream>

void assign_and_create_form_file()
{
    Matrix a, b(2, 2);
    std::ifstream file1("mtx1.txt");
    file1 >> a;

    b(0, 0) = 1;
    b(0, 1) = 2;
    b(1, 0) = 3;
    b(1, 1) = 4;

    std::cout << "b(1,1): " << b(1, 1) << std::endl;

    Matrix c(a);

    std::cout << "a: " << std::endl
              << a << std::endl;
    std::cout << "b: " << std::endl
              << b << std::endl;
    std::cout << "c: " << std::endl
              << b << std::endl;
    std::cout << "=========================" << std::endl;

    file1.close();
}

void addition()
{
    std::ifstream file1("mtx1.txt");
    Matrix a;
    file1 >> a;
    std::ifstream file2("mtx4.txt");
    Matrix b;
    file2 >> b;

    Matrix c(2, 2);
    c = b + a;
    a += b;
    std::cout << "a: " << std::endl
              << a << std::endl;
    std::cout << "b: " << std::endl
              << b << std::endl;
    std::cout << "c: " << std::endl
              << c << std::endl;

    std::cout << "=========================" << std::endl;

    file1.close();
    file2.close();
}

void substraction()
{
    std::ifstream file1("mtx1.txt");
    Matrix a;
    file1 >> a;
    std::ifstream file2("mtx4.txt");
    Matrix b;
    file2 >> b;

    Matrix c(2, 2);
    c = a - b;
    a -= b;
    std::cout << "a: " << std::endl
              << a << std::endl;
    std::cout << "b: " << std::endl
              << b << std::endl;
    std::cout << "c: " << std::endl
              << c << std::endl;

    std::cout << "=========================" << std::endl;

    file1.close();
    file2.close();
}

void multiplication()
{
    std::ifstream file1("mtx2.txt");
    Matrix a;
    file1 >> a;
    std::ifstream file2("mtx3.txt");
    Matrix b;
    file2 >> b;

    Matrix c(2, 2), d(a);
    c = a * b;
    d *= b;

    std::cout << "a: " << std::endl
              << a << std::endl;
    std::cout << "b: " << std::endl
              << b << std::endl;
    std::cout << "c: " << std::endl
              << c << std::endl;
    std::cout << "d: " << std::endl
              << d << std::endl;

    std::cout << "=========================" << std::endl;

    file1.close();
    file2.close();
}

void comp_test()
{
    std::ifstream file1("mtx1.txt");
    Matrix a;
    file1 >> a;
    std::ifstream file2("mtx4.txt");
    Matrix b;
    file2 >> b;
    Matrix c(a);

    std::cout << std::boolalpha;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;
    std::cout << "a == c: " << (a == c) << std::endl;
}

void show_exceptons()
{
    try
    {
        std::ifstream file1("mtx5.txt");
        Matrix a(2,2);
        file1 >> a;
        std::cout << a;
    }
    catch (const IllegalInput &e)
    {
        std::cerr << "1: " << e.what() << std::endl;
    }
    try
    {
        std::ifstream file1("mtx1.txt");
        Matrix a;
        file1 >> a;
        std::ifstream file2("mtx2.txt");
        Matrix b;
        file2 >> b;

        b -= a;
    }
    catch (const IllegalMatrixDiemensions &e)
    {
        std::cerr << "2: " << e.what() << '\n';
    }

    try
    {
        std::ifstream file2("mtx2.txt");
        Matrix b;
        file2 >> b;
        b(4,3) = 8;
    }
    catch (const IllegalMatrixDiemensions &e)
    {
        std::cerr << "3: " << e.what() << '\n';
    }
}

int main()
{
    assign_and_create_form_file();
    addition();
    substraction();
    multiplication();
    comp_test();
    show_exceptons();

    return 0;
}
