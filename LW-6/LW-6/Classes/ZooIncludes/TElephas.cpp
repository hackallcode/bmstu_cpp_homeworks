#include "TElephas.h"

#define ADULT_AGE 60
#define DEATH_AGE 80

const std::string TElephas::Names[3] = { "Kate", "Mary", "Anna" };

TElephas::TElephas()
	: TElephas(Names[rand() % (sizeof(Names) / sizeof(Names[0]))])
{}

TElephas::TElephas(const std::string & name)
	: TProboscidea(name, ADULT_AGE, DEATH_AGE)
{}

TElephas * TElephas::MakeChild()
{
	TElephas * child = new TElephas();
	return child;
}

void TElephas::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (11.f <= time && time <= 12.f || 17.f <= time && time <= 19.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TProboscidea::Live(stream, time);
}