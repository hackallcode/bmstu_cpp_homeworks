#include <iostream>
#include "Array.h"

int main()
{
    std::cout << "Array<int, 3> a { {1, 2, 3} };" << std::endl;
    Array<int, 3> a { {1, 2, 3} };
    
    std::cout << "a.at(0): " << a.at(0) << std::endl;
    std::cout << "a[0]: " << a[0] << std::endl;
    std::cout << "a.front(): " << a.front() << std::endl;
    std::cout << "a.back(): " << a.back() << std::endl;
    std::cout << "*a.begin(): " << *a.begin() << std::endl;
    std::cout << "*a.end(): " << *a.end() << std::endl;
    std::cout << "a.empty(): " << a.empty() << std::endl;
    std::cout << "a.size(): " << a.size() << std::endl;

    std::cout << "Array<int, 3> b { {666, 666, 666} };" << std::endl;
    int i = 666;
    Array<int, 3> b;
    b.fill(i);
    std::cout << "b[2]: " << b[2] << std::endl;

    std::cout << "swap(a, b);" << std::endl;
    swap(a, b);

    std::cout << "b[2]: " << b[2] << std::endl;
    std::cout << "b < a: " << (b < a) << std::endl;

    try {
        b.at(5);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    system("pause");
    return 0;
}