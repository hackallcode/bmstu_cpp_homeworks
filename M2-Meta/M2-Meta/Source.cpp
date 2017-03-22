#include <iostream>

template<size_t N>
void print()
{
    std::cout << N << std::endl;
    print<N + 1>();
}

template<>
void print<100>()
{
    std::cout << 100 << std::endl;
}

int main()
{
    print<0>();
    system("pause");
    return 0;
}