#pragma once

#include <iostream>

class TVector 
{
private:
	size_t Length;
	double * Data;
public:
	// Деструктор
	~TVector();
	
	// Конструктор по умолчанию
	TVector();

	// Конструктор копирования
	TVector(const TVector & rhs);

	// Пользовательский консруктор
	TVector(const double * const data, const size_t length);

	// Оператор присваивания
	TVector & operator=(const TVector & rhs);

	// Оператор +=
	TVector & operator+=(const double * const data);

	// Оператор []
	double operator[](size_t index) const;
	double& operator[](size_t index);
};

// Оператор +
TVector operator+(const TVector & a, const double * const b);