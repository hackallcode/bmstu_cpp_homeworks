#include "TVector.h"

TVector::~TVector()
{
	if (Data != nullptr)
		delete[] Data;
}

TVector::TVector()
{
	Length = 0;
	Data = nullptr;
}

TVector::TVector(const TVector & rhs)
{
	Length = rhs.Length;
	Data = new double[Length];
	for (size_t i = 0; i < Length; i++) Data[i] = rhs.Data[i];
}

TVector::TVector(const double * const data, const size_t length)
{
	Length = length;
	Data = new double[Length];
	for (size_t i = 0; i < Length; i++) Data[i] = data[i];
}

TVector & TVector::operator=(const TVector & rhs)
{
	if (&rhs == this) return *this;
	delete[] Data;
	Length = rhs.Length;
	Data = new double[Length];
	for (size_t i = 0; i < Length; i++) Data[i] = rhs.Data[i];
	return *this;
}

TVector & TVector::operator+=(const double * const data)
{
	double * newData = new double[Length * 2];
	for (size_t i = 0; i < Length; i++) {
		newData[i] = Data[i];
		newData[Length + i] = data[i];
	}
	delete[] Data;
	Length *= 2;
	Data = newData;
	return *this;
}

double TVector::operator[](size_t index) const
{
	return Data[index];
}

double& TVector::operator[](size_t index)
{
	return Data[index];
}

TVector operator+(const TVector & a, const double * const b)
{
	TVector result = TVector(a);
	result += b;
	return result;
}