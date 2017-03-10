#include "TTriad.h"

TTriad::TTriad() : First(0), Second(0), Third(0) 
{}

TTriad::TTriad(int first, int second, int third) : First(first), Second(second), Third(third) 
{}

int TTriad::GetFirst()
{
	return First;
}

int TTriad::GetSecond()
{
	return Second;
}

int TTriad::GetThird()
{
	return Third;
}

void TTriad::SetFirst(int value)
{
	First = value;
}

void TTriad::SetSecond(int value)
{
	Second = value;
}

void TTriad::SetThird(int value)
{
	Third = value;
}

void TTriad::IncFirst()
{
	First++;
}

void TTriad::IncSecond()
{
	Second++;
}

void TTriad::IncThird()
{
	Third++;
}

void TTriad::Print(std::ostream & stream)
{
	stream << First << " " << Second << " " << Third << std::endl;
}