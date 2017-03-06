#include "TGiraffa.h"

TGiraffa::TGiraffa()
	: TArtiodactyla()
{}

TGiraffa::TGiraffa(const std::string & name)
	: TArtiodactyla(name, 10, 20)
{}

TGiraffa * TGiraffa::MakeChild()
{
	TGiraffa * child = new TGiraffa(GiraffaNames[ rand() % ( sizeof(GiraffaNames)/sizeof(GiraffaNames[0]) ) ]);
	return child;
}

void TGiraffa::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (10.f <= time && time <= 12.f || 15.f <= time && time <= 17.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TArtiodactyla::Live(stream, time);
}