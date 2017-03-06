#pragma once

#include "TCarnivora.h"

class TLeo
	: public TCarnivora
{
private:
	static const std::string Names[3];
public:
	const static size_t ClassID = 31; // ID класса

	// Конструктор по умолчанию
	TLeo();

	// Пользовательский консруктор
	TLeo(const std::string & name);

	// Пользовательский конструктор
	virtual TLeo * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};