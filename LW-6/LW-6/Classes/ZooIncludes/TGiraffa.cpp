#include "TGiraffa.h"

#define ADULT_AGE 10
#define DEATH_AGE 20

const std::string TGiraffa::Names[3] = { "Tom", "Billy", "Mark" };

TGiraffa::TGiraffa()
	: TGiraffa(Names[rand() % (sizeof(Names) / sizeof(Names[0]))])
{}

TGiraffa::TGiraffa(const std::string & name)
	: TArtiodactyla(name, ADULT_AGE, DEATH_AGE)
{}

TGiraffa * TGiraffa::MakeChild()
{
	TGiraffa * child = new TGiraffa(Names[rand() % (sizeof(Names) / sizeof(Names[0]))]);
	return child;
}

void TGiraffa::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (10.f <= time && time <= 12.f || 15.f <= time && time <= 17.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TArtiodactyla::Live(stream, time);
}