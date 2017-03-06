#include <thread>
#include <iostream>
#include <windows.h>
#include "Classes\ZooIncludes.h"

int main()
{
	// Создаем объекты
	TZoo Zoo_1, Zoo_2;

	TAnimal * Giraf = new TGiraffa("Gir"); // 0
	TAnimal * Girafik = new TGiraffa("Grif"); // 1
	TAnimal * Hippo = new THippopotamus("Hippo"); // 2
	TAnimal * Hippos = new THippopotamus("Happi"); // 3 
	TAnimal * Eleph = new TElephas("Elele"); // 4
	TAnimal * Elephs = new TElephas(); // 5
	TAnimal * Elephsa = new TElephas("Elena"); // 6
	TAnimal * Loxodonti = new TLoxodonta("Loxi"); // 7
	TAnimal * Line = new TLeo("Leo"); // 8
	TAnimal * Lines = new TLeo(); // 9
	TAnimal * Tigr = new TTigris("Tiger"); // 10
	TAnimal * Tigre = new TTigris(); // 11
	
	Zoo_1.AddNewAnimal(Giraf);
	Zoo_1.AddNewAnimal(Girafik);
	Zoo_1.AddNewAnimal(Eleph);
	Zoo_1.AddNewAnimal(Loxodonti);
	Zoo_1.AddNewAnimal(Elephsa);
	Zoo_1.AddNewAnimal(Line);
	Zoo_1.AddNewAnimal(Lines);
	
	Zoo_2.AddNewAnimal(Hippo);
	Zoo_2.AddNewAnimal(Hippos);
	Zoo_2.AddNewAnimal(Elephs);
	Zoo_2.AddNewAnimal(Tigr);
	Zoo_2.AddNewAnimal(Tigre);

	// Демонстрация обмена
	ChangeAnimals(Zoo_1, 7, Zoo_2, 5);

	while(true)
	{
		system("cls");

		// Работа первого зоопарка
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "Inforamtion of Zoo 1:" << std::endl;
		Zoo_1.Work();
		std::cout << std::endl;

		// Работа второго зоопарка
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "Inforamtion of Zoo 2:" << std::endl;
		Zoo_2.Work();
		std::cout << std::endl;
		
		// Если нет животных, тогда выйти из цикла
		if (Zoo_1.GetAnimalsNumber() == 0 && Zoo_2.GetAnimalsNumber() == 0)
			break;

		// Задержка
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	system("pause");
}
