#ifndef __TSTRING_INCLUDE__
#define __TSTRING_INCLUDE__

#include <iostream>
#include <assert.h>

class TString
{
private:
	size_t Length;
	char * Data;
public:
	// Деструктор
	~TString();

	// Конструктор по умолчанию
	TString();

	// Конструктор копирования
	TString(const TString& rhs);

	// Конструктор, принимающий char *
	TString(const char * const data);

	// Безопасный конструктор, принимающий char *
	TString(const char * const data, const size_t numberOfElements);

	// Оператор присваивания TString
	TString& operator =(const TString& rhs);

	// Оператор присваивания char *
	TString& operator =(const char * const data);

	// Оператор += с TString
	TString& operator +=(const TString& rhs);

	// Оператор += с char *
	TString& operator +=(const char * const rhs);

	// Оператор == с TString
	bool operator ==(const TString& rhs) const;

	// Оператор == с char *
	bool operator ==(const char * const rhs) const;

	// Оператор <
	bool operator <(const TString& rhs) const;
	
	// Функция поиска подстроки
	size_t Find(const TString& substr) const;

	// Функция замены букв
	void Replace(char oldSymbol, char newSymbol);

	// Функция возвращает длину строки
	size_t Size() const;

	// Оператор []
	char operator[](size_t index) const;

	// Оператор []
	char& operator[](size_t index);

	// Функция для определения пуста ли строка
	bool Empty() const;
	
	// Trim символа справа
	void RTrim(char symbol);

	// Trim символа слева
	void LTrim(char symbol);

	friend std::ostream & operator<<(std::ostream &, const TString &);
};

// Оператор +
TString operator+(const TString & a, const TString & b);


// <Оператор !=
bool operator!=(const TString & a, const TString & b);


// Оператор >
bool operator>(const TString & a, const TString & b);

// Оператор вывода
std::ostream & operator<<(std::ostream &out, const TString &str);

#endif // __TSTRING_INCLUDE__