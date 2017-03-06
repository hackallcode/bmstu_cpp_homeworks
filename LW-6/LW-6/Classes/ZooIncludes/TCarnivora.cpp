#include "TCarnivora.h"

TCarnivora::TCarnivora()
	: TAnimal()
{ }

TCarnivora::TCarnivora(const std::string & name, size_t adultAge, size_t deathAge)
	: TAnimal(name, adultAge, deathAge)
{}

void TCarnivora::Live(std::ostream & stream, float time)
{
	if ( IsAlive && time <= 5.f )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Sleeping" << std::endl;
	else
		TAnimal::Live(stream, time);
}