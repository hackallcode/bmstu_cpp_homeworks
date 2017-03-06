#pragma once

#include "TProboscidea.h"

const std::string LoxodontaNames[3] = { "Ian", "Luk", "Jace" };

class TLoxodonta
	: public TProboscidea
{
public:
	const static size_t ClassID = 22; // ID класса

	// Деструктор
	~TLoxodonta() = default;

	// Конструктор по умолчанию
	TLoxodonta();

	// Пользовательский консруктор
	TLoxodonta(const std::string & name);

	// Пользовательский конструктор
	virtual TLoxodonta * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;

};