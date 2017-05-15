#include <thread>
#include <mutex>
#include <iostream>
#include <cstdlib>
#include "InfInt.h"

std::mutex combination_lock;

void Factorial(size_t num, InfInt& result)
{
    result = 1;
    for (size_t i = 1; i <= num; ++i) {
        result *= i;
    }
}

InfInt Combination(size_t n, size_t k)
{
    combination_lock.lock();

    InfInt factorialOne, factorialTwo, factorialThree;

    std::thread threadOne(Factorial, n, std::ref(factorialOne));
    std::thread threadTwo(Factorial, k, std::ref(factorialTwo));
    std::thread threadThree(Factorial, n - k, std::ref(factorialThree));

    threadOne.join();
    threadTwo.join();
    threadThree.join();

    combination_lock.unlock();

    return factorialOne / (factorialTwo * factorialThree);
}

int main()
{
    InfInt comb1, comb2;
    comb1 = Combination(2, 1);
    comb2 = Combination(100, 4);
    std::cout << comb1 << std::endl;
    std::cout << comb2 << std::endl;
    system("pause");
    return 0;
}