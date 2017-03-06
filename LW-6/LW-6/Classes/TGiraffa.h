#pragma once

#include "TArtiodactyla.h"

const std::string GiraffaNames[3] = { "Tom", "Billy", "Mark" };

class TGiraffa
	: public TArtiodactyla
{
public:
	const static size_t ClassID = 11; // ID класса

	// Деструктор
	~TGiraffa() = default;

	// Конструктор по умолчанию
	TGiraffa();

	// Пользовательский консруктор
	TGiraffa(const std::string & name);

	// Пользовательский конструктор
	virtual TGiraffa * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;

};