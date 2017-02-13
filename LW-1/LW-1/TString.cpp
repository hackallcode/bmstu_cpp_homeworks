#include "TString.h"

#define LAST_CHAR '\0'


void TString::newData(const char * const data, const size_t len) 
{
	Length = len;
	Data = new char[Length + 1];
	for (int i = 0; i < Length; i++) Data[i] = data[i];
	Data[Length] = LAST_CHAR;
}

void TString::addNewData(const char * const data, const size_t len)
{
	char * newData = new char[Length + len + 1];
	for (int i = 0; i < Length; i++) newData[i] = Data[i];
	for (int i = 0; i < len; i++) newData[Length + i] = data[i];
	newData[Length + len] = LAST_CHAR;
	delete[] Data;
	Length += len;
	Data = newData;
}

TString::~TString()
{
	delete[] Data;
}

TString::TString()
{
	newData(nullptr, 0);
}

TString::TString(const TString& rhs)
{
	newData(rhs.Data, rhs.Length);
}

TString::TString(const char * const data)
{
	size_t len = 0;
	while (data[len] != '\0') len++;
	newData(data, len);
}

TString::TString(const char * const data, const size_t len)
{
	newData(data, len);
}

TString& TString::operator =(const TString& rhs)
{
	if (rhs == *this) return *this;
	delete[] Data;
	newData(rhs.Data, rhs.Length);
	return *this;
}

TString& TString::operator =(const char * const data)
{
	delete[] Data;
	size_t len = 0;
	while (data[len] != '\0') len++;
	newData(data, len);
	return *this;
}

TString& TString::operator +=(const TString& rhs)
{
	addNewData(rhs.Data, rhs.Length);
	return *this;
}

TString& TString::operator +=(const char * const data)
{
	size_t len = 0;
	while (data[len] != '\0') len++;
	addNewData(data, len);
	return *this;
}

bool TString::operator ==(const TString& rhs) const
{
	if (Length != rhs.Length) return false;
	for (int i = 0; i < Length; i++)
		if (Data[i] != rhs.Data[i]) return false;
	return true;
}

bool TString::operator ==(const char * const data) const
{
	size_t len = 0;
	while (data[len] != '\0') len++;
	if (Length != len) return false;
	for (int i = 0; i < Length; i++)
		if (Data[i] != data[i]) return false;
	return true;
}

bool TString::operator <(const TString& rhs) const
{
	for (int i = 0; i < Length + 1 && i < rhs.Length + 1; i++) {
		if (Data[i] < rhs.Data[i])
			return true;
		else if (Data[i] > rhs.Data[i])
			return false;
	}
	return false;
}

size_t TString::Find(const TString& substr) const
{
	for (int i = 0; i < Length; i++) {
		for (int k = 0; k < substr.Length; k++) {
			if (Data[i + k] != substr.Data[k]) break;
			if (k == substr.Length - 1) return i;
		}
	}
	return -1;
}

void TString::Replace(char oldSymbol, char newSymbol) 
{
	for (int i = 0; i < Length; i++)
		if (Data[i] == oldSymbol) Data[i] = newSymbol;
}

size_t TString::Size() const
{
	return Length;
}

char TString::operator[](size_t index) const
{
	return Data[index];
}

char& TString::operator[](size_t index)
{
	return Data[index];
}

bool TString::Empty() const
{
	return (Length == 0);
}

void TString::RTrim(char symbol)
{
	int k = 0;
	while (Length - k > 0 && Data[Length - 1 - k] == symbol) k++;
	if (k == 0) return;
	Length -= k;
	char * newData = new char[Length + 1];
	for (int i = 0; i < Length; i++) newData[i] = Data[i];
	newData[Length] = LAST_CHAR;
	delete[] Data;
	Data = newData;
}

void TString::LTrim(char symbol)
{
	int k = 0;
	while (Length - k > 0 && Data[k] == symbol) k++;
	if (k == 0) return;
	Length -= k;
	char * newData = new char[Length + 1];
	for (int i = 0; i < Length; i++) newData[i] = Data[k + i];
	newData[Length] = LAST_CHAR;
	delete[] Data;
	Data = newData;
}

TString operator+(const TString & a, const TString & b)
{
	TString result(a);
	result += b;
	return result;
}

bool operator!=(const TString & a, const TString & b)
{
	return !(a == b);
}

bool operator>(const TString & a, const TString & b)
{
	return (!(a == b) && !(a < b));
}

std::ostream & operator<<(std::ostream &out, const TString &str)
{
	out << str.Data;
	return out;
}