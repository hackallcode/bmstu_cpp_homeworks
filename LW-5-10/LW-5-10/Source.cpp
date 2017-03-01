#include <iostream>
#include "TTriad.h"
#include "TDate.h"

int main() 
{
	TTriad test(1, 2, 3);
	test.IncFirst();
	test.IncSecond();
	test.IncSecond();
	test.SetThird(0);
	test.IncThird();
	test.Print(std::cout);

	TDate date(2100, 2, 28);
	date.IncDay();
	date.IncMonth();
	date.IncYear();
	date.AddDays(40);
	date.Print(std::cout);

	system("pause");
	return 0;
}