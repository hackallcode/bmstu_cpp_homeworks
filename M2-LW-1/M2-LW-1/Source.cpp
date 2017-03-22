#include <iostream>
#include <exception>
#include "CastException.h"

char numeralFromChar(char data)
{
	if (48 <= data && data <= 57)
		return data - 48;
	else
		throw UnknownChar();
}

int intFromString(const char * data)
{
	size_t shift = 0;
	bool isMinus = false;
	if (data[0] == '-') {
		isMinus = true;
		shift = 1;
	}
	if (data[0] == '+')
		shift = 1;

	// Подсчет длины без знака и нулей перед числом
	size_t len = 0;
	while (data[len + shift]) {
		if (len == 0 && data[len + shift] == '0')
			shift++;
		else
			len++;
	}

	// 2147483647 - максимум состоит из 10 цифр
	if (len > 10) throw TooBigNumberException();

	/******************************************** РАБОТАЮЩИЙ БЫДЛОКОД ********************************************
	if (len == 10)
		if (data[shift] > '2')
			throw TooBigNumberException();
		else if (data[shift] == '2')
			if (data[shift + 1] > '1')
				throw TooBigNumberException();
			else if (data[shift + 1] == '1')
				if (data[shift + 2] > '4')
					throw TooBigNumberException();
				else if (data[shift + 2] == '4')
					if (data[shift + 3] > '7')
						throw TooBigNumberException();
					else if (data[shift + 3] == '7')
						if (data[shift + 4] > '4')
							throw TooBigNumberException();
						else if (data[shift + 4] == '4')
							if (data[shift + 5] > '8')
								throw TooBigNumberException();
							else if (data[shift + 5] == '8')
								if (data[shift + 6] > '3')
									throw TooBigNumberException();
								else if (data[shift + 6] == '3')
									if (data[shift + 7] > '6')
										throw TooBigNumberException();
									else if (data[shift + 7] == '6')
										if (data[shift + 8] > '4')
											throw TooBigNumberException();
										else if (data[shift + 8] == '4')
											if (data[shift + 9] > '7' && !isMinus || data[shift + 9] > '8' && isMinus)
												throw TooBigNumberException();
	/************************************************************************************************************/

	int result = 0;
	for (size_t i = 0; i < len; i++) {
		if (i == 0 && len == 10 && numeralFromChar(data[shift + i]) > 2) throw TooBigNumberException();
		// Без доп переменной неправильно считает (0 - 9 = -8)
		int plus = pow(10, len - i - 1) * numeralFromChar(data[shift + i]) * (isMinus ? -1 : 1);
		result += plus;
		if (result < 0 && !isMinus || result >= 0 && isMinus) {
			throw TooBigNumberException();
		}
	}
	return result;
}

bool boolFromString(const char * data)
{
	if (strcmp(data, "FALSE") == 0 || strcmp(data, "False") == 0 || strcmp(data, "false") == 0 || strcmp(data, "0") == 0)
		return false;
	else if (strcmp(data, "TRUE") == 0 || (data, "True") == 0 || strcmp(data, "true") == 0 || strcmp(data, "1") == 0)
		return true;
	else
		throw UnknownChar();
}

float floatFromString(const char * data)
{
	size_t shift = 0;
	bool isMinus = false;
	if (data[0] == '-') {
		isMinus = true;
		shift = 1;
	}
	if (data[0] == '+')
		shift = 1;

	// Подсчет длины без знака и нулей перед числом
	size_t int_len = 0;
	while (data[int_len + shift]) {
		if (data[int_len + shift] == ',' || data[int_len + shift] == '.')
			break;
		if (int_len == 0 && data[int_len + shift] == '0')
			shift++;
		else
			int_len++;
	}

	float result = 0;
	for (size_t i = 0; i < int_len; i++) {
		result += pow(10, int_len - i - 1) * numeralFromChar(data[shift + i]) * (isMinus ? -1 : 1);
	}
	for (size_t i = 1; data[shift + int_len + i]; i++) {
		result += 1 / pow(10, i) * numeralFromChar(data[shift + int_len + i]) * (isMinus ? -1 : 1);
	}
	return result;
}

int main() {
	
	intFromString("-00002147483648");
	intFromString("00002147483647");

	try {
		intFromString("-2147483649");
	}
	catch (TooBigNumberException & e) {
		std::cout << "TooBigNumberException!" << std::endl;
	}

	try {
		intFromString("483d649");
	}
	catch (UnknownChar & e) {
		std::cout << "UnknownChar!" << std::endl;
	}

	boolFromString("true");
	boolFromString("1");

	try {
		boolFromString("tru");
	}
	catch (UnknownChar & e) {
		std::cout << "UnknownChar!" << std::endl;
	}

	floatFromString("12345.6789");

	try {
		floatFromString("12345.678w9");
	}
	catch (UnknownChar & e) {
		std::cout << "UnknownChar!" << std::endl;
	}

	system("pause");
}