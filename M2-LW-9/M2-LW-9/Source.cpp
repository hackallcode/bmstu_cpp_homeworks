#include <iostream>
#include "ScopedPtr.h"

int main() 
{
    ScopedPtr<int> s(new int);
    *s = 5;

    system("pause");
    return 0;
}