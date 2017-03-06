#include "TLeo.h"

#define ADULT_AGE 5
#define DEATH_AGE 25

const std::string TLeo::Names[3] = { "Kristofer", "Frenk", "Debby" };

TLeo::TLeo()
	: TLeo(Names[rand() % (sizeof(Names) / sizeof(Names[0]))])
{}

TLeo::TLeo(const std::string & name)
	: TCarnivora(name, ADULT_AGE, DEATH_AGE)
{}

TLeo * TLeo::MakeChild()
{
	TLeo * child = new TLeo(Names[rand() % (sizeof(Names) / sizeof(Names[0]))]);
	return child;
}

void TLeo::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (13.f <= time && time <= 14.f || 20.f <= time && time <= 21.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TCarnivora::Live(stream, time);
}