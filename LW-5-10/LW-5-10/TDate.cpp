#include "TDate.h"

TDate::TDate()
{
	SetFirst(1900);
	SetSecond(1);
	SetThird(1);
}

TDate::TDate(int year, int month, int day)
{
	SetFirst(year);
	SetSecond(month);
	SetThird(day);
}

void TDate::SetFirst(int value)
{
	First = value;
}

void TDate::SetSecond(int value)
{
	Second = value;
	while (Second < 1) {
		SetFirst(First - 1);
		Second += 12;
	}
	while (Second > 12) {
		SetFirst(First + 1);
		Second -= 12;
	}
}

void TDate::SetThird(int value)
{
	Third = value;
	while (true) {
		if (Second == 1 || Second == 3 || Second == 5 || Second == 7 || Second == 8 || Second == 10 || Second == 12) {
			if (Third < 1) {
				SetSecond(Second - 1);
				Third += 31;
				continue;
			}
			else if (Third > 31) {
				SetSecond(Second + 1);
				Third -= 31;
				continue;
			}
		}
		else if (Second == 4 || Second == 6 || Second == 9 || Second == 11) {
			if (Third < 1) {
				SetSecond(Second - 1);
				Third += 30;
				continue;
			}
			else if (Third > 30) {
				SetSecond(Second + 1);
				Third -= 30;
				continue;
			}
		}
		// In our calendar only 97 from 400 years consist of 366 days
		else if (Second == 2 && (First % 4 == 0 && First % 100 != 0 || First % 400 == 0)) {
			if (Third < 1) {
				SetSecond(Second - 1);
				Third += 29;
				continue;
			}
			else if (Third > 29) {
				SetSecond(Second + 1);
				Third -= 29;
				continue;
			}
		}
		else if (Second == 2) {
			if (Third < 1) {
				SetSecond(Second - 1);
				Third += 28;
				continue;
			}
			else if (Third > 28) {
				SetSecond(Second + 1);
				Third -= 28;
				continue;
			}
		}
		break;
	}		
}

void TDate::IncFirst()
{
	SetFirst(First + 1);
}

void TDate::IncSecond()
{
	SetSecond(Second + 1);
}

void TDate::IncThird()
{
	SetThird(Third + 1);
}

void TDate::SetYear(int value)
{
	SetFirst(value);
}

void TDate::SetMonth(int value)
{
	SetSecond(value);
}

void TDate::SetDay(int value)
{
	SetThird(value);
}

void TDate::IncYear()
{
	IncFirst();
}

void TDate::IncMonth()
{
	IncSecond();
}

void TDate::IncDay()
{
	IncThird();
}

void TDate::AddDays(int days)
{
	SetThird(Third + days);
}

void TDate::Print(std::ostream & stream)
{
	stream << First << "." << Second << "." << Third << std::endl;
}