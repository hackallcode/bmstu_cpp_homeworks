#pragma once

#include "TAnimal.h"

class TCarnivora abstract
	: public TAnimal
{
public:
	const static size_t ClassID = 3; // ID класса

	// Конструктор по умолчанию
	TCarnivora();

	// Пользовательский конструктор
	TCarnivora(const std::string & name, size_t adultAge, size_t deathAge);

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};