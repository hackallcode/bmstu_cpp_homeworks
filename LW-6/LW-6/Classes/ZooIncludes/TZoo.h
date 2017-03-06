#pragma once

#include <iostream>
#include <windows.h>
#include "TAnimal.h"

class TZoo
{
private:
	typedef TAnimal * TAnimalPtr;
	
	size_t AnimalsNumber; // Количество зверей в зоопарке	
	TAnimalPtr * Animals; // Звери
	float Time; // Время суток

	// Функция создания детенышей при благоприятных условиях
	size_t MakeChildren();
public:
	// Деструктор
	~TZoo();

	// Конструктор по умолчанию
	TZoo();

	// Получить количество животных
	size_t GetAnimalsNumber() const;

	// Получить время
	float GetTime() const;

	// Задать время
	void SetTime(float time);

	// Функция добавления животного
	bool AddNewAnimal(TAnimal * & newAnimal);
	
	// Убрать животное из зоопарка
	bool RemoveAnimal(size_t ID);

	// Такт жизни
	void Work(std::ostream & stream = std::cout);

	// Добавить дни (ускорить время)
	void AddDays(size_t daysNumber);

	friend bool ChangeAnimals(TZoo & zoo_1, size_t id_1, TZoo & zoo_2, size_t id_2);
};

bool ChangeAnimals(TZoo & zoo_1, size_t id_1, TZoo & zoo_2, size_t id_2);