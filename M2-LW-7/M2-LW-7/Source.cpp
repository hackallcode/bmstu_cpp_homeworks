#include "Vector.h"
#include <vector>
#include <iostream>

void printVector(const Vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

int main()
{
    {
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        std::vector<int> vec2(vec);
        vec2.push_back(4);

        std::vector<int> vec3(std::move(vec));
        vec2 = std::move(vec3);

        std::cout << "vec: ";
        for (auto& el : vec) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        std::cout << "vec2: ";
        for (auto& el : vec2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        std::cout << "vec3: ";
        for (auto& el : vec3) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
    {
        Vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        Vector<int> vec2(vec);
        vec2.push_back(4);

        Vector<int> vec3(std::move(vec));
        vec2 = std::move(vec3);

        std::cout << "vec: ";
        for (auto& el : vec) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        std::cout << "vec2: ";
        for (auto& el : vec2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;

        std::cout << "vec3: ";
        for (auto& el : vec3) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
    {
        Vector<int> vec;
        for (int i = 0; i < 32; ++i)
            vec.push_back(i);

        printVector(vec);

        vec.insert(vec.begin() + 10, 1000);
        printVector(vec);

        vec.erase(vec.begin(), vec.begin() + 10);
        printVector(vec);

        vec.erase(vec.begin());
        printVector(vec);

        std::cout << vec.front() << std::endl;
        std::cout << vec.back() << std::endl;

        vec.pop_back();
        std::cout << vec.back() << std::endl;

        size_t oldSize = vec.size();
        vec.resize(44);
        printVector(vec);

        vec.resize(oldSize);
        printVector(vec);

        Vector<int> vec2;
        for (int i = 0; i < 2; ++i)
            vec2.push_back(i);

        vec2.swap(vec);
        printVector(vec2);
        printVector(vec);

        vec2 = vec;
        printVector(vec2);
        printVector(vec);

        try
        {
            Vector<int>::value_type item = vec2.at(1000000);
        }
        catch (const std::exception & e)
        {
            std::cout << e.what() << std::endl;
        }

        try
        {
            vec2.resize(UINT64_MAX);
        }
        catch (const std::exception & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    system("pause");
}