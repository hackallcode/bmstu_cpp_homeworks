#pragma once

#include "TCarnivora.h"

const std::string TigrisNames[3] = { "Izobel", "Julia", "Ronald" };

class TTigris
	: public TCarnivora
{
public:
	const static size_t ClassID = 32; // ID класса

	// Деструктор
	~TTigris() = default;

	// Конструктор по умолчанию
	TTigris();

	// Пользовательский консруктор
	TTigris(const std::string & name);

	// Пользовательский конструктор
	virtual TTigris * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;

};