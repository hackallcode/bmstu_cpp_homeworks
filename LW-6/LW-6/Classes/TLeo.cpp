#include "TLeo.h"

TLeo::TLeo()
	: TCarnivora()
{}

TLeo::TLeo(const std::string & name)
	: TCarnivora(name, 5, 25)
{}

TLeo * TLeo::MakeChild()
{
	TLeo * child = new TLeo(LeoNames[ rand() % ( sizeof(LeoNames)/sizeof(LeoNames[0]) ) ]);
	return child;
}

void TLeo::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (13.f <= time && time <= 14.f || 20.f <= time && time <= 21.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TCarnivora::Live(stream, time);
}