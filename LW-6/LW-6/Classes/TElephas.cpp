#include "TElephas.h"

TElephas::TElephas()
	: TProboscidea()
{}

TElephas::TElephas(const std::string & name)
	: TProboscidea(name, 70, 80)
{}

TElephas * TElephas::MakeChild()
{
	TElephas * child = new TElephas(ElephasNames[ rand() % ( sizeof(ElephasNames)/sizeof(ElephasNames[0]) ) ]);
	return child;
}

void TElephas::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (11.f <= time && time <= 12.f || 17.f <= time && time <= 19.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TProboscidea::Live(stream, time);
}