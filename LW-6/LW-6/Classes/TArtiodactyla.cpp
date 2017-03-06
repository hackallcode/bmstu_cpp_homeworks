#include "TArtiodactyla.h"

TArtiodactyla::TArtiodactyla()
	: TAnimal()
{ }

TArtiodactyla::TArtiodactyla(const std::string & name, size_t adultAge, size_t deathAge)
	: TAnimal(name, adultAge, deathAge)
{}

void TArtiodactyla::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (time <= 6.f || time >= 22.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Sleeping" << std::endl;
	else
		TAnimal::Live(stream, time);
}