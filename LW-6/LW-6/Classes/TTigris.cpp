#include "TTigris.h"

TTigris::TTigris()
	: TCarnivora()
{}

TTigris::TTigris(const std::string & name)
	: TCarnivora(name, 30, 37)
{}

TTigris * TTigris::MakeChild()
{
	TTigris * child = new TTigris(TigrisNames[ rand() % ( sizeof(TigrisNames)/sizeof(TigrisNames[0]) ) ]);
	return child;
}

void TTigris::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (8.f <= time && time <= 10.f || 16.f <= time && time <= 17.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TCarnivora::Live(stream, time);
}