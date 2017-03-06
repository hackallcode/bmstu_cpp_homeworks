#pragma once

#include "TProboscidea.h"

const std::string ElephasNames[3] = { "Kate", "Mary", "Anna" };

class TElephas
	: public TProboscidea
{
public:
	const static size_t ClassID = 21; // ID класса

	// Деструктор
	~TElephas() = default;

	// Конструктор по умолчанию
	TElephas();

	// Пользовательский консруктор
	TElephas(const std::string & name);

	// Пользовательский конструктор
	virtual TElephas * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;

};