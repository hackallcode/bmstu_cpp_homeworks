#include "TTigris.h"

#define ADULT_AGE 30
#define DEATH_AGE 37

const std::string TTigris::Names[3] = { "Izobel", "Julia", "Ronald" };

TTigris::TTigris()
	: TTigris(Names[rand() % (sizeof(Names) / sizeof(Names[0]))])
{}

TTigris::TTigris(const std::string & name)
	: TCarnivora(name, ADULT_AGE, DEATH_AGE)
{}

TTigris * TTigris::MakeChild()
{
	TTigris * child = new TTigris(Names[ rand() % ( sizeof(Names)/sizeof(Names[0]) ) ]);
	return child;
}

void TTigris::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (8.f <= time && time <= 10.f || 16.f <= time && time <= 17.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TCarnivora::Live(stream, time);
}