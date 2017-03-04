#include "simple_memory_leak_detector.h"

const size_t OVERHEAD_SIZE = 10000;
void * POINTERS[OVERHEAD_SIZE];
void * MULTI_POINTERS[OVERHEAD_SIZE];

void * operator new(std::size_t n) throw(std::bad_alloc)
{
	for (void * & ptr : POINTERS) {
		if (ptr != nullptr)
			continue;
		ptr = malloc(n);
		if (ptr == nullptr)
			throw std::bad_alloc();
		return ptr;
	}
	throw std::bad_alloc();
}

void * operator new[](std::size_t n) throw(std::bad_alloc)
{
	for (void * & ptr : MULTI_POINTERS) {
		if (ptr != nullptr)
			continue;
		ptr = malloc(n);
		if (ptr == nullptr)
			throw std::bad_alloc();
		return ptr;
	}
	throw std::bad_alloc();
}

void operator delete(void * p) throw()
{
	if (p == nullptr) {
		throw std::exception("double free");
		return;
	}
	for (void * & ptr : POINTERS) {
		if (ptr == p) {
			free(p);
			ptr = nullptr;
			return;
		}
	}
	throw std::exception("incorrect delete");
}

void operator delete[](void * p) throw()
{
	if (p == nullptr) {
		throw std::exception("double free");
		return;
	}
	for (void * & ptr : MULTI_POINTERS) {
		if (ptr == p) {
			free(p);
			ptr = nullptr;
			return;
		}
	}
	throw std::exception("incorrect delete");
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