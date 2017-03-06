#pragma once

#include "TArtiodactyla.h"

const std::string HippopotamusNames[3] = { "Greg", "Fiona", "Jennifer" };

class THippopotamus
	: public TArtiodactyla
{
public:
	const static size_t ClassID = 12; // ID класса

	// Деструктор
	~THippopotamus() = default;

	// Конструктор по умолчанию
	THippopotamus();

	// Пользовательский консруктор
	THippopotamus(const std::string & name);

	// Пользовательский конструктор
	virtual THippopotamus * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;

};