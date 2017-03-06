#pragma once

#include "TProboscidea.h"

class TLoxodonta
	: public TProboscidea
{
private:
	static const std::string Names[3];
public:
	const static size_t ClassID = 22; // ID класса

	// Конструктор по умолчанию
	TLoxodonta();

	// Пользовательский консруктор
	TLoxodonta(const std::string & name);

	// Пользовательский конструктор
	virtual TLoxodonta * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};