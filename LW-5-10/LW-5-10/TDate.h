#pragma once

#include "TTriad.h"

class TDate : public TTriad
{
private:
	// Изменение полей
	virtual void SetFirst(int value);
	virtual void SetSecond(int value);
	virtual void SetThird(int value);

	// Приращение полей
	virtual void IncFirst();
	virtual void IncSecond();
	virtual void IncThird();
public:
	// Конструктор по умолчанию
	TDate();

	// Пользовательский конструктор
	TDate(int year, int month, int day);

	// Изменение полей
	void SetYear(int value);
	void SetMonth(int value);
	void SetDay(int value);

	// Приращение полей
	void IncYear();
	void IncMonth();
	void IncDay();

	// Добавить дни
	void AddDays(int days);

	// Вывод
	virtual void Print(std::ostream & stream);
};