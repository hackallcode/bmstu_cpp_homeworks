#pragma once

#include <iostream>
#include <string>

class TCar
{
protected:
	std::string Model;
	size_t MaxVelocity;
public:
	// Конструктор по умолчанию
	TCar() : Model(""), MaxVelocity(0) 
	{}

	// Пользовательский консруктор
	TCar(const std::string & model, size_t maxVelocity) : Model(model), MaxVelocity(maxVelocity) 
	{}

	// Функция вывода параметров в поток
	virtual void Print(std::ostream & stream)
	{
		stream << "Model: " << Model << std::endl;
		stream << "Max velocity: " << MaxVelocity << std::endl;
	}
};