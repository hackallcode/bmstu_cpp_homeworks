#include <iostream>
#include <vector>

template<class It, class Cmp>
void qsort(It beg, It end, Cmp cmp)
{
    It left = beg, right = end - 1;
    It middle = beg + (end - beg) / 2;
    while (left <= right)
    {
        while (cmp(*left, *middle)) {
            ++left;
        }
        while (cmp(*middle, *right)) {
            --right;
        }
        if (left <= right) {
            std::swap(*left, *right);
            ++left;
            --right;
        }
    }
    if (beg < right) {
        qsort(beg, right + 1, cmp);
    }
    if (end > left) {
        qsort(left, end, cmp);
    }
}

template<class T>
void print(std::vector<T> vec)
{
    for (T const& el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

template<>
void print<std::string>(std::vector<std::string> vec)
{
    for (std::string& str : vec) {
        std::cout << str.c_str() << " ";
    }
    std::cout << std::endl;
}

template<class T>
bool compare(T a, T b) {
    return a < b;
}

int main() {
    std::vector<std::string> vec{ "5", "3", "4", "1", "2" };
    print(vec);
    qsort(vec.begin(), vec.end(), compare<std::string>);
    print(vec);

    std::vector<int> vec2{ 5, 3, 4, 1, 2 };
    print(vec2);
    qsort(vec2.begin(), vec2.end(), compare<int>);
    print(vec2);

    std::vector<bool> vec3{ 1, 0, 0, 1, 1, 0, 1 };
    print(vec3);
    qsort(vec3.begin(), vec3.end(), compare<bool>);
    print(vec3);

    system("pause");
}