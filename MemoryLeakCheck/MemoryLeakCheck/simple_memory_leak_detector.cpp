#include "simple_memory_leak_detector.h"

const size_t OVERHEAD_SIZE = 10000;
void * POINTERS[OVERHEAD_SIZE];
void * MULTI_POINTERS[OVERHEAD_SIZE];

void * allocate_memory(std::size_t n, bool isMulti = false) 
{
	void ** arr;
	if (isMulti)
		arr = MULTI_POINTERS;
	else
		arr = POINTERS;
	for (int i = 0; i < OVERHEAD_SIZE; i++) {
		if (arr[i] != nullptr)
			continue;
		arr[i] = malloc(n);
		if (arr[i] == nullptr)
			throw std::bad_alloc();
		return arr[i];
	}
	throw std::bad_alloc();
}

void free_memory(void * p, bool isMulti = false)
{
	if (p == nullptr) {
		throw std::exception("double free");
		return;
	}
	void ** arr;
	if (isMulti)
		arr = MULTI_POINTERS;
	else
		arr = POINTERS;
	for (int i = 0; i < OVERHEAD_SIZE; i++) {
		if (arr[i] == p) {
			free(p);
			arr[i] = nullptr;
			return;
		}
	}
	throw std::exception("incorrect delete");
}

void * operator new(std::size_t n) throw(std::bad_alloc)
{
	return allocate_memory(n);
}

void * operator new[](std::size_t n) throw(std::bad_alloc)
{
	return allocate_memory(n, true);
}

void operator delete(void * p) throw()
{
	free_memory(p);
}

void operator delete[](void * p) throw()
{
	free_memory(p, true);
}

bool memoryLeakExist()
{
	for (void * & ptr : POINTERS) {
		if (ptr != nullptr) 
			return true;
	}
	for (void * & ptr : MULTI_POINTERS) {
		if (ptr != nullptr)
			return true;
	}
	return false;
}