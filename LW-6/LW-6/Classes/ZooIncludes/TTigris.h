#pragma once

#include "TCarnivora.h"

class TTigris
	: public TCarnivora
{
private:
	static const std::string Names[3];
public:
	const static size_t ClassID = 32; // ID класса

	// Конструктор по умолчанию
	TTigris();

	// Пользовательский консруктор
	TTigris(const std::string & name);

	// Пользовательский конструктор
	virtual TTigris * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};