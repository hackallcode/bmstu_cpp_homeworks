#include <iostream>
#include "Integer.h"

int main() {
    Integer i;

    i = 10;
    i += 1;
    i -= 1;
    i *= 3;
    i /= 3;
    i %= 3;
    i &= 3;
    i |= 8;
    i = 0;
    i ^= 15;
    i <<= 1;
    i >>= 1;
    i = +i;
    i = -i;
    ++i;
    i++;
    --i;
    i--;
    i = 10;
    i = i + 1;
    i = i - 1;
    i = i * 3;
    i = i / 3;
    i = i % 3;
    i = i & 3;
    i = i | 8;
    i = -1;
    i = ~i;
    i = i ^ 15;
    i = i << 1;
    i = i >> 1;
    bool res = i == 1;
    res = i != 1;
    res = i < 1;
    res = i > 1;
    res = i <= 1;
    res = i >= 1;
    std::cout << i << std::endl << "Check of input: ";
    std::cin >> i;
    i = 0xffffffff;
    i *= 0x1;

    try {
        i = 0xffffffff;
        i *= 0xffffffff;
    }
    catch (IntegerOverflowException& e) {
        std::cout << e.what() << std::endl;
    }
    
    try {
        i = 0xffffffff;
        i *= 0x2;
    }
    catch (IntegerOverflowException& e) {
        std::cout << e.what() << std::endl;
    }

    system("pause");
    return 0;
}