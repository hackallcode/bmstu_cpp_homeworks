#include "THippopotamus.h"

#define ADULT_AGE 15
#define DEATH_AGE 25

const std::string THippopotamus::Names[3] = { "Greg", "Fiona", "Jennifer" };

THippopotamus::THippopotamus()
	: THippopotamus(Names[rand() % (sizeof(Names) / sizeof(Names[0]))])
{}

THippopotamus::THippopotamus(const std::string & name)
	: TArtiodactyla(name, ADULT_AGE, DEATH_AGE)
{}

THippopotamus * THippopotamus::MakeChild()
{
	THippopotamus * child = new THippopotamus(Names[rand() % (sizeof(Names) / sizeof(Names[0]))]);
	return child;
}

void THippopotamus::Live(std::ostream & stream, float time)
{
	if ( IsAlive && (10.f <= time && time <= 15.f || 17.f <= time && time <= 19.f) )
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Eating" << std::endl;
	else
		TArtiodactyla::Live(stream, time);
}