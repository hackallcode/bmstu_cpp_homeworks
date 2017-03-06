#include "TProboscidea.h"

TProboscidea::TProboscidea()
	: TAnimal()
{ }

TProboscidea::TProboscidea(const std::string & name, size_t adultAge, size_t deathAge)
	: TAnimal(name, adultAge, deathAge)
{}

void TProboscidea::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (time <= 7.f || time >= 23.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Sleeping" << std::endl;
	else
		TAnimal::Live(stream, time);
}