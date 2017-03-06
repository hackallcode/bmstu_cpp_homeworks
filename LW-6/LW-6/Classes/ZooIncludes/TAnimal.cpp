#include "TAnimal.h"

size_t TAnimal::LastID = 0;

TAnimal::TAnimal()
	: ID(LastID++)
	, Name()
	, Age(0)
	, AdultAge(0)
	, DeathAge(0)
	, CorpseAge(0)
	, ChildrenCount(0)
	, IsAlive(false)
{ }

TAnimal::TAnimal(const std::string & name, size_t adultAge, size_t deathAge)
	: ID(TAnimal::LastID++)
	, Name(name)
	, Age(0)
	, AdultAge(adultAge)
	, DeathAge(deathAge)
	, CorpseAge(0)
	, ChildrenCount(0)
	, IsAlive(true)
{}

size_t TAnimal::GetID() const
{
	return ID;
}

std::string TAnimal::GetName() const
{
	return Name;
}

size_t TAnimal::GetAge() const
{
	return Age;
}

size_t TAnimal::GetCorpseAge() const
{
	return CorpseAge;
}

size_t TAnimal::GetChildrenCount() const
{
	return ChildrenCount;
}

bool TAnimal::ChildPossibility() const
{
	// Если взрослый и ещё не старый
	if (IsAlive && AdultAge <= Age && Age <= DeathAge)
		return true;
	else
		return false;
}

void TAnimal::AddChildrenCount(size_t childrenCount)
{
	ChildrenCount += childrenCount;
}

void TAnimal::IncDays()
{
	// Если жив, то прибавляем возраст, иначе возраст трупа
	if (IsAlive) {
		Age++;
		if (Age >= DeathAge * 2 || Age >= DeathAge && rand() % (int(DeathAge * 2) - Age) == 0) {
			IsAlive = false;
		}
	}
	else {
		CorpseAge++;
	}
}

void TAnimal::Live(std::ostream & stream, float time)
{
	// Живет или мертв
	if (IsAlive)
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Living";
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		stream << ID << ". " << GetName() << " (" << GetAge() << " days old): " << "Died";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	stream << std::endl;
}