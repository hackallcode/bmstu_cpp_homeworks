#pragma once

#include "TAnimal.h"

class TProboscidea abstract
	: public TAnimal
{
public:
	const static size_t ClassID = 2; // ID класса

	// Деструктор
	~TProboscidea() = default;

	// Конструктор по умолчанию
	TProboscidea();

	// Пользовательский конструктор
	TProboscidea(const std::string & name, size_t adultAge, size_t deathAge);

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};