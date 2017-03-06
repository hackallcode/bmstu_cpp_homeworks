#include "TLoxodonta.h"

TLoxodonta::TLoxodonta()
	: TProboscidea()
{}

TLoxodonta::TLoxodonta(const std::string & name)
	: TProboscidea(name, 15, 20)
{}

TLoxodonta * TLoxodonta::MakeChild()
{
	TLoxodonta * child = new TLoxodonta(LoxodontaNames[ rand() % ( sizeof(LoxodontaNames)/sizeof(LoxodontaNames[0]) ) ]);
	return child;
}

void TLoxodonta::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (9.f <= time && time <= 13.f || 16.f <= time && time <= 18.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TProboscidea::Live(stream, time);
}