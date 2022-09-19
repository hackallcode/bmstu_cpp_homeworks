// ВАРИАНТ 5

#include <iostream>
#include "Parser.h"

int main() {
    Parser p("test");
    std::cout << p.GetObject("Russia").Get<int>("Area") << std::endl;
    system("pause");
    return 0;
}