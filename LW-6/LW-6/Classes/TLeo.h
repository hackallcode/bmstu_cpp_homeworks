#pragma once

#include "TCarnivora.h"

const std::string LeoNames[3] = { "Kristofer", "Frenk", "Debby" };

class TLeo
	: public TCarnivora
{
public:
	const static size_t ClassID = 31; // ID класса

	// Деструктор
	~TLeo() = default;

	// Конструктор по умолчанию
	TLeo();

	// Пользовательский консруктор
	TLeo(const std::string & name);

	// Пользовательский конструктор
	virtual TLeo * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;

};