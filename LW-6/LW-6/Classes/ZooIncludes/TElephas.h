#pragma once

#include "TProboscidea.h"

class TElephas
	: public TProboscidea
{
private:
	static const std::string Names[3];
public:
	static const size_t ClassID = 21; // ID класса

	// Конструктор по умолчанию
	TElephas();

	// Пользовательский консруктор
	TElephas(const std::string & name);

	// Пользовательский конструктор
	virtual TElephas * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};