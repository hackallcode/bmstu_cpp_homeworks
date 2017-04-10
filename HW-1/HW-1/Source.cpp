#include <iostream>
#include <unordered_set>
#include "UnorderedSet.h"

void hasher() {

}

int main() 
{
    /* std::unordered_set *
    std::unordered_set<int> test;
    test.max_load_factor(2);
    std::cout << test.empty() << std::endl;
    for (int i = 0; i < 10; i++) {
        test.insert(i);
        std::cout << test.size() << " " << test.bucket_count() << " " << test.load_factor() << ": ";
        for (size_t j = 0; j < test.bucket_count(); j++) {
            std::cout << test.bucket_size(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << *(test.begin(5)) << std::endl;
    std::cout << *(--test.end(6)) << std::endl; 
    test.max_load_factor(1);
    test.insert(3);
    test.insert(11);
    std::cout << test.size() << " " << test.bucket_count() << " " << test.load_factor() << ": ";
    for (size_t j = 0; j < test.bucket_count(); j++) {
        std::cout << test.bucket_size(j) << " ";
    }
    std::cout << std::endl;
    std::cout << *(test.begin()) << std::endl;
    std::cout << *(--test.end()) << std::endl;
    test.erase(2);
    std::cout << test.size() << " " << test.bucket_count() << std::endl;
    std::unordered_set<int> test_copy(test);
    std::cout << test.empty() << std::endl;
    test.clear();
    std::cout << test.empty() << std::endl;
    std::cout << test.size() << " " << test.bucket_count() << std::endl;
    test.swap(test_copy);
    std::cout << test.size() << " " << test.bucket_count() << std::endl;
    test.reserve(100);
    std::cout << test.size() << " " << test.bucket_count() << std::endl;
    test.rehash(100);
    std::cout << test.size() << " " << test.bucket_count() << std::endl << std::endl;
    /**/

    UnorderedSet<int> test_2;
    test_2.MaxLoadFactor(2);
    std::cout << test_2.Empty() << std::endl;
    for (int i = 0; i < 10; i++) {
        test_2.Insert(i);
        std::cout << test_2.Size() << " " << test_2.BucketCount() << " " << test_2.LoadFactor() << ": ";
        for (size_t j = 0; j < test_2.BucketCount(); j++) {
            std::cout << test_2.BucketSize(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << *(test_2.Begin(5)) << std::endl;
    std::cout << *(--test_2.End(6)) << std::endl;
    test_2.MaxLoadFactor(1);
    test_2.Insert(3);
    test_2.Insert(11);
    std::cout << test_2.Size() << " " << test_2.BucketCount() << " " << test_2.LoadFactor() << ": ";
    for (size_t j = 0; j < test_2.BucketCount(); j++) {
        std::cout << test_2.BucketSize(j) << " ";
    }
    std::cout << std::endl;
    std::cout << *(test_2.Begin()) << std::endl;
    std::cout << *(--test_2.End()) << std::endl;
    test_2.Erase(2);
    std::cout << test_2.Size() << " " << test_2.BucketCount() << std::endl;
    UnorderedSet<int> test_2_copy(test_2);
    std::cout << test_2.Empty() << std::endl;
    test_2.Clear();
    std::cout << test_2.Empty() << std::endl;
    std::cout << test_2.Size() << " " << test_2.BucketCount() << std::endl;
    test_2.Swap(test_2_copy);
    std::cout << test_2.Size() << " " << test_2.BucketCount() << std::endl;
    test_2.Reserve(100);
    std::cout << test_2.Size() << " " << test_2.BucketCount() << std::endl;
    test_2.Rehash(100);
    std::cout << test_2.Size() << " " << test_2.BucketCount() << std::endl << std::endl;

    system("pause");
    return 0;
}