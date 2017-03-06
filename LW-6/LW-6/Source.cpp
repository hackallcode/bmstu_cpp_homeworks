#include <thread>
#include <iostream>
#include "Classes\TZoo.h"
#include "Classes\TGiraffa.h"
#include "Classes\THippopotamus.h"
#include "Classes\TElephas.h"
#include "Classes\TLoxodonta.h"
#include "Classes\TLeo.h"
#include "Classes\TTigris.h"

int main()
{
	TZoo myZoo, Zoo2;

	TAnimal * Giraf = new TGiraffa("Gir");
	TAnimal * Girafik = new TGiraffa("Grif");
	TAnimal * Hippo = new THippopotamus("Hippo");
	TAnimal * Hippos = new THippopotamus("Happi");
	TAnimal * Eleph = new TElephas("Elele");
	TAnimal * Elephs = new TElephas("Eleleph");
	TAnimal * Elephsa = new TElephas("Elena");
	TAnimal * Loxodonti = new TLoxodonta("Loxi");
	TAnimal * Line = new TLeo("Leo");
	TAnimal * Lines = new TLeo("Leos");
	TAnimal * Tigr = new TTigris("Tiger");
	TAnimal * Tigre = new TTigris("Tigerrrr");
	
	myZoo.AddNewAnimal(Giraf);
	myZoo.AddNewAnimal(Girafik);
	myZoo.AddNewAnimal(Eleph);
	myZoo.AddNewAnimal(Elephs);
	myZoo.AddNewAnimal(Elephsa);
	myZoo.AddNewAnimal(Line);
	myZoo.AddNewAnimal(Lines);
	
	Zoo2.AddNewAnimal(Hippo);
	Zoo2.AddNewAnimal(Hippos);
	Zoo2.AddNewAnimal(Loxodonti);
	Zoo2.AddNewAnimal(Tigr);
	Zoo2.AddNewAnimal(Tigre);

	while(true)
	{
		system("cls");
		myZoo.Work(std::cout);
		std::cout << std::endl << std::endl;
		Zoo2.Work(std::cout);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	system("pause");
}
