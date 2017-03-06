#include "THippopotamus.h"

THippopotamus::THippopotamus()
	: TArtiodactyla()
{}

THippopotamus::THippopotamus(const std::string & name)
	: TArtiodactyla(name, 15, 25)
{}

THippopotamus * THippopotamus::MakeChild()
{
	THippopotamus * child = new THippopotamus(HippopotamusNames[ rand() % ( sizeof(HippopotamusNames)/sizeof(HippopotamusNames[0]) ) ]);
	return child;
}

void THippopotamus::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (10.f <= time && time <= 15.f || 17.f <= time && time <= 19.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TArtiodactyla::Live(stream, time);
}