#include <cstdlib>
#include <iostream>
#include <vector>

template<class IT>
void sort(IT beg, IT end)
{
    for (IT i = beg; i < end - 1; ++i) {
        for (IT j = i + 1; j < end; ++j) {
            if (*j < *i) {
                std::swap(*i, *j);
            }
        }
    }
}

int main() {
    int arr[] = { 123, 3, 0, 13212, -100 };
    sort(&arr[0], &arr[3]); // arr: 0, 3, 123, 13212, -100
    for (int& i : arr) std::cout << i << " ";
    std::cout << std::endl;
    sort(&arr[2], &arr[5]); // arr: 0, 3, -100, 123, 13212
    for (int& i : arr) std::cout << i << " ";
    std::cout << std::endl;

    std::vector<double> vec = { 123.0, 3.0, 0.0, 13212.0, -100.0 };
    sort(vec.begin(), vec.end()); // vec: -100.0, 0.0, 3.0, 123.0, 13212.0
    for (double& i : vec) std::cout << i << " ";
    std::cout << std::endl;

    system("pause");
    return 0;
}