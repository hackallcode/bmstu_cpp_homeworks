#pragma once

#include <iostream>

class TTriad
{
protected:
	int First;
	int Second;
	int Third;
public:
	// Конструктор по умолчанию
	TTriad();

	// Пользовательский конструктор
	TTriad(int first, int second, int third);

	// Получения полей
	int GetFirst();
	int GetSecond();
	int GetThird();

	// Изменение полей
	virtual void SetFirst(int value);
	virtual void SetSecond(int value);
	virtual void SetThird(int value);

	// Приращение полей
	virtual void IncFirst();
	virtual void IncSecond();
	virtual void IncThird();

	// Функция вывода
	virtual void Print(std::ostream & stream);
};