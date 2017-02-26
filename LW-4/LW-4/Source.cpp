#include <cstdlib>
#include <iostream>
#include "TCar.h"
#include "TBus.h"

int main() 
{
	TCar * car = new TCar("Test Model", 100);
	TCar * bus = new TBus("Fast Bus", 180, 10);
	TBus * bus_2 = new TBus("Slow Bus", 10, 3);

	car->Print(std::cout);
	std::cout << std::endl;

	bus->Print(std::cout);
	std::cout << std::endl;

	bus_2->Print(std::cout);
	std::cout << std::endl;

	delete car;
	delete bus;
	delete bus_2;
	system("pause");
	return 0;
}