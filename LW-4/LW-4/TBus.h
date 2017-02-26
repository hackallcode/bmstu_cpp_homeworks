#pragma once

#include "TCar.h"

class TBus : public TCar
{
protected:
	size_t MaxPassengers;
public:
	// Конструктор по умолчанию
	TBus() : TCar(), MaxPassengers(0) 
	{}

	// Пользовательский консруктор
	TBus(const std::string & model, size_t maxVelocity, size_t maxPassengers) : TCar(model, maxVelocity), MaxPassengers(maxPassengers) 
	{}

	// Функция вывода параметров в поток
	virtual void Print(std::ostream & stream)
	{
		TCar::Print(stream);
		stream << "Max count of passengers: " << MaxPassengers << std::endl;
	}
};