#include "TLoxodonta.h"

#define ADULT_AGE 15
#define DEATH_AGE 20

const std::string TLoxodonta::Names[3] = { "Ian", "Luk", "Jace" };

TLoxodonta::TLoxodonta()
	: TLoxodonta(Names[rand() % (sizeof(Names) / sizeof(Names[0]))])
{}

TLoxodonta::TLoxodonta(const std::string & name)
	: TProboscidea(name, ADULT_AGE, DEATH_AGE)
{}

TLoxodonta * TLoxodonta::MakeChild()
{
	TLoxodonta * child = new TLoxodonta(Names[rand() % (sizeof(Names) / sizeof(Names[0]))]);
	return child;
}

void TLoxodonta::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (9.f <= time && time <= 13.f || 16.f <= time && time <= 18.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TProboscidea::Live(stream, time);
}