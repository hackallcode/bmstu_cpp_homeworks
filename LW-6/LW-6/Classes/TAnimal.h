#pragma once

#include <iostream>
#include <string>

class TAnimal abstract
{
protected:
	static size_t LastID; // ID последнего животного
	size_t ID; // ID животного
	std::string Name; // Имя
	size_t Age; // Возраст
	size_t AdultAge; // Возраст взросления
	size_t DeathAge; // Возможный возраст смерти
	size_t CorpseAge; // Возраст со дня смерти
	size_t ChildrenCount; // Максимальное количество детей
	bool IsAlive; // Флаг: живой или мертвый
public:
	const static size_t ClassID = 0; // ID класса

	// Деструктор
	~TAnimal() = default;
	
	// Конструктор по умолчанию
	TAnimal();

	// Пользовательский конструктор
	TAnimal(const std::string & name, size_t adultAge, size_t deathAge);

	// Родить ребенка
	virtual TAnimal * MakeChild() = 0;
	
	// Получение полей
	size_t GetID() const;
	std::string GetName() const;
	size_t GetAge() const;
	size_t GetCorpseAge() const;
	size_t GetChildrenCount() const;
	bool ChildPossibility() const;

	// Добавить ребенка
	void AddChildrenCount(size_t childrenCount);

	// Добавить дни жизни
	void AddDays(size_t daysNumber);

	// Действие в указанное время
	virtual void Live(std::ostream & stream, float time);
};

