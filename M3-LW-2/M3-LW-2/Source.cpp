#include <iostream>
#include <vector>

template<class It, class Cmp>
void qsort(It beg, It end, Cmp cmp)
{
    It left = beg, right = end;
    It middle = beg + (end - beg) / 2;
    while (left <= right)
    {
        while (cmp(*left, *middle) < 0) {
            ++left;
        }
        while (cmp(*right, *middle) > 0) {
            --right;
        }
        if (left <= right) {
            std::swap(*left, *right);
            ++left;
            --right;
        }
    }
    if (beg < right) {
        qsort(beg, right, cmp);
    }
    if (end > left) {
        qsort(left, end, cmp);
    }
}

template<class T>
void print(std::vector<T> vec)
{
    for (T& el : vec) {
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
int Compare(T left, T right)
{
    if (left < right) {
        return -1;
    }
    else if (left > right) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    std::vector<std::string> vec{ "5", "3", "4", "1", "2" };
    print(vec);
    qsort(vec.begin(), --vec.end(), Compare<std::string>);
    print(vec);

    std::vector<int> vec2{ 5, 3, 4, 1, 2 };
    print(vec2);
    qsort(vec2.begin(), --vec2.end(), Compare<int>);
    print(vec2);
    system("pause");
}