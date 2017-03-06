#pragma once

#include "TArtiodactyla.h"

class TGiraffa
	: public TArtiodactyla
{
private:
	static const std::string Names[3];
public:
	static const size_t ClassID = 11; // ID класса

	// Конструктор по умолчанию
	TGiraffa();

	// Пользовательский консруктор
	TGiraffa(const std::string & name);

	// Пользовательский конструктор
	virtual TGiraffa * MakeChild() override;

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time) override;
};