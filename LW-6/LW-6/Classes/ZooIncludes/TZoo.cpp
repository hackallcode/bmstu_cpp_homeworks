#include "TZoo.h"

#define HOURS_STEP 1
#define MAX_CHILDREN 2
#define AVR_DAYS_FOR_NEW_CHILD 10

TZoo::~TZoo()
{
	// Освобождаем память
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
	// Функция mod для float
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
			if (Animals[i]->ClassID == Animals[j]->ClassID
				&& Animals[i]->GetChildrenCount() < MAX_CHILDREN
				&& Animals[j]->GetChildrenCount() < MAX_CHILDREN
				&& Animals[i]->ChildPossibility() 
				&& Animals[j]->ChildPossibility() 
				&& rand() % AVR_DAYS_FOR_NEW_CHILD == 0) 
			{
				// Записываем, что добавился один ребенок
				Animals[i]->AddChildrenCount(1);
				Animals[j]->AddChildrenCount(1);

				// Добавляем ребенка в зоопарк
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

			// Заносим в новый массив нужные части старого
			TAnimalPtr * newAnimals = new TAnimalPtr[AnimalsNumber - 1];
			memcpy(newAnimals, Animals, i * sizeof(TAnimalPtr));
			memcpy(newAnimals + i, Animals + i + 1, (AnimalsNumber - i - 1) * sizeof(TAnimalPtr));
			
			// Освобождаем старый, пишем в него новый
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
	// Посчитать время
	bool isNewDay = false;
	Time += HOURS_STEP;
	if (Time >= 24.f) {
		Time -= 24.f;
		isNewDay = true;
	}

	// Вывести время
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_GREEN);
	stream << "Time: " << Time << std::endl;

	// Создать или удалить животных
	size_t newChildsNum = 0;
	if (isNewDay)
		newChildsNum = MakeChildren();
	for (size_t i = 0; i < AnimalsNumber - newChildsNum; i++) {
		if (isNewDay)
			Animals[i]->IncDays();
		if (Animals[i]->GetCorpseAge() > 0) {
			RemoveAnimal(Animals[i]->GetID());
			i--;
			continue;
		}
	}

	// Вывести информацию о животных
	if (AnimalsNumber == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		stream << "YOU HAVEN'T GOT ANY ANIMALS!" << std::endl;
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		stream << "Animals:" << std::endl;
		for (size_t i = 0; i < AnimalsNumber; i++)
			Animals[i]->Live(stream, Time);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void TZoo::AddDays(size_t daysNumber)
{
	// Добавляем дни по одному, чтобы ничего не пропустить
	for (size_t j = 0; j < daysNumber; j++) {
		MakeChildren();
		for (size_t i = 0; i < AnimalsNumber; i++)
			Animals[i]->IncDays();
	}
}

bool ChangeAnimals(TZoo & zoo_1, size_t id_1, TZoo & zoo_2, size_t id_2)
{
	// Ищем животного в певром зоопарке
	size_t num_1 = 0;
	for (; num_1 < zoo_1.AnimalsNumber; num_1++) {
		if (zoo_1.Animals[num_1]->GetID() == id_1)
			break;
	}

	// Ищем животного во втором зоопарке
	size_t num_2 = 0;
	for (; num_2 < zoo_2.AnimalsNumber; num_2++) {
		if (zoo_2.Animals[num_2]->GetID() == id_2)
			break;
	}

	// Если кого-то нет, выходим
	if (num_1 == zoo_1.AnimalsNumber || num_2 == zoo_2.AnimalsNumber)
		return false;

	// Меняемся указателями
	std::swap(zoo_1.Animals[num_1], zoo_2.Animals[num_2]);
}