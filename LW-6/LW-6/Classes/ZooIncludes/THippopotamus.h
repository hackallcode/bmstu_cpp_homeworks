#pragma once

#include "TArtiodactyla.h"

class THippopotamus
	: public TArtiodactyla
{
private:
	static const std::string Names[3];
public:
	static const size_t ClassID = 12; // ID класса

	// Конструктор по умолчанию
	THippopotamus();

	// Пользовательский консруктор
	THippopotamus(const std::string & name);

	// Пользовательский конструктор
	virtual THippopotamus * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};