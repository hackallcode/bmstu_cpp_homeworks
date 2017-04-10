#include <iostream>
#include <unordered_set>
#include "UnorderedSet.h"

void hasher() {

}

int main() 
{
    std::unordered_set<int> test;
    test.max_load_factor(2);
    for (int i = 0; i < 10; i++) {
        test.insert(i);
        std::cout << test.size() << " " << test.bucket_count() << " " << test.load_factor() << ": ";
        for (size_t j = 0; j < test.bucket_count(); j++) {
            std::cout << test.bucket_size(j) << " ";
        }
        std::cout << std::endl;
    }
    test.max_load_factor(1);
    test.insert(11);
    std::cout << test.size() << " " << test.bucket_count() << " " << test.load_factor() << ": ";
    for (size_t j = 0; j < test.bucket_count(); j++) {
        std::cout << test.bucket_size(j) << " ";
    }
    std::cout << std::endl << std::endl;

    UnorderedSet<int> test_2;
    test_2.MaxLoadFactor(2);
    for (int i = 0; i < 10; i++) {
        test_2.Insert(i);
        std::cout << test_2.Size() << " " << test_2.BucketCount() << " " << test_2.LoadFactor() << ": ";
        for (size_t j = 0; j < test_2.BucketCount(); j++) {
            std::cout << test_2.BucketSize(j) << " ";
        }
        std::cout << std::endl;
    }
    test_2.MaxLoadFactor(1);
    test_2.Insert(11);
    std::cout << test_2.Size() << " " << test_2.BucketCount() << " " << test_2.LoadFactor() << ": ";
    for (size_t j = 0; j < test_2.BucketCount(); j++) {
        std::cout << test_2.BucketSize(j) << " ";
    }
    std::cout << std::endl;

    system("pause");
    return 0;
}