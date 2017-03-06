#include "TZoo.h"

TZoo::~TZoo()
{
	for (size_t i = 0; i < AnimalsNumber; i++)
	{
		delete Animals[i];
	}
	delete[] Animals;
}

TZoo::TZoo()
	: AnimalsNumber(0)
	, Animals(nullptr)
	, Time(0)
{}

size_t TZoo::GetAnimalsNumber() const
{
	return AnimalsNumber;
}

float TZoo::GetTime() const
{
	return Time;
}

void TZoo::SetTime(float time)
{
	float time_mod_24 = time - 24 * int(time / 24);
	if (time_mod_24 < 0)
		time_mod_24 += 24.f;
	Time = time_mod_24;
}

bool TZoo::AddNewAnimal(TAnimal * & newAnimal)
{
	// Проверяем корректность входного параметра
	if (newAnimal == nullptr)
		return false;

	// Увеличиваем счетчик
	AnimalsNumber++;

	// Добавляем зверя в массив
	TAnimalPtr * newAnimals = new TAnimalPtr[AnimalsNumber];
	memcpy(newAnimals, Animals, (AnimalsNumber - 1) * sizeof(TAnimalPtr));
	newAnimals[AnimalsNumber - 1] = newAnimal;
	delete[] Animals;
	Animals = newAnimals;

	// Забираем зверя у старого владельца, чтобы не удалить зверя дважды
	newAnimal = nullptr;

	return true;
}

size_t TZoo::MakeChildren()
{
	size_t number = 0;
	for (size_t i = 0; i < AnimalsNumber; i++) {
		for (size_t j = i + 1; j < AnimalsNumber; j++) {
			if (Animals[i]->GetChildrenCount() < MAX_CHILDREN 
				&& Animals[j]->GetChildrenCount() < MAX_CHILDREN 
				&& Animals[i]->ClassID == Animals[j]->ClassID
				&& Animals[i]->ChildPossibility() 
				&& Animals[j]->ChildPossibility() 
				&& rand() % AVR_DAYS_FOR_NEW_CHILD == 0) 
			{
				Animals[i]->AddChildrenCount(1);
				Animals[j]->AddChildrenCount(1);
				TAnimal * child = Animals[i]->MakeChild();
				AddNewAnimal(child);
				number++;
			}
		}
	}
	return number;
}

bool TZoo::RemoveAnimal(size_t id)
{
	for (size_t i = 0; i < AnimalsNumber; i++) {
		if (Animals[i]->GetID() == id) {
			delete Animals[i];

			TAnimalPtr * newAnimals = new TAnimalPtr[AnimalsNumber - 1];
			memcpy(newAnimals, Animals, i * sizeof(TAnimalPtr));
			memcpy(newAnimals + i, Animals + i + 1, (AnimalsNumber - i - 1) * sizeof(TAnimalPtr));
			
			delete[] Animals;
			Animals = newAnimals;
			AnimalsNumber--;
			return true;
		}
	}
	return false;
}

void TZoo::Work(std::ostream & stream)
{
	bool isNewDay = false;
	Time += STEP;
	if (Time >= 24.f) {
		Time -= 24.f;
		isNewDay = true;
	}
	std::cout << "Time: " << Time << std::endl << std::endl;

	if (AnimalsNumber == 0) {
		std::cout << "YOU HAVEN'T GOT ANY ANIMALS!" << std::endl;
	}
	else {
		std::cout << "Now animals do:" << std::endl;
			size_t newChildsNum = 0;
		if (isNewDay)
			newChildsNum = MakeChildren();
		for (size_t i = 0; i < AnimalsNumber - newChildsNum; i++) {
			if (isNewDay)
				Animals[i]->AddDays(1);
			Animals[i]->Live(stream, Time);
			if (Animals[i]->GetCorpseAge() > 0) {
				RemoveAnimal(Animals[i]->GetID());
				i--;
			}
		}
	}

}

void TZoo::AddDays(size_t daysNumber)
{
	for (size_t i = 0; i < AnimalsNumber; i++)
		Animals[i]->AddDays(daysNumber);
}

bool ChangeAnimals(TZoo & zoo_1, size_t id_1, TZoo & zoo_2, size_t id_2)
{
	size_t num_1 = 0;
	for (; num_1 < zoo_1.AnimalsNumber; num_1++) {
		if (zoo_1.Animals[num_1]->GetID() == id_1)
			break;
	}

	size_t num_2 = 0;
	for (; num_2 < zoo_2.AnimalsNumber; num_2++) {
		if (zoo_2.Animals[num_2]->GetID() == id_2)
			break;
	}

	if (num_1 == zoo_1.AnimalsNumber || num_2 == zoo_2.AnimalsNumber)
		return false;

	std::swap(zoo_1.Animals[num_1], zoo_2.Animals[num_2]);
}