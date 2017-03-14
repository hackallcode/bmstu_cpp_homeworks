#pragma once

#include <iostream>
#include <exception>

class IntegerOverflowException
    : std::exception
{
public:
    IntegerOverflowException() throw()
        : std::exception("integer overflow")
    {}

    IntegerOverflowException(char const* const message) throw()
        : std::exception(message)
    {}

    virtual char const* what() const override
    {
        return std::exception::what();
    }
};

class Integer
{
private:
    int data_;
public:
    // Деструктор
    ~Integer();

    // Конструктор
    Integer();

    // Пользовательский конструктор
    Integer(int data);

    // Конструктор копирование
    Integer(Integer const& integer);

    // Присваивание
    Integer& operator=(Integer const& integer);

    // Прибавление
    Integer& operator+=(Integer const& integer);

    // Вычитание
    Integer& operator-=(Integer const& integer);

    // Умножение
    Integer& operator*=(Integer const& integer);

    // Деление
    Integer& operator/=(Integer const& integer);

    // Остаток от деления
    Integer& operator%=(Integer const& integer);

    // Побитовое И
    Integer& operator&=(Integer const& integer);

    // Побитовое ИЛИ
    Integer& operator|=(Integer const& integer);

    // Побитовое исключающее ИЛИ
    Integer& operator^=(Integer const& integer);

    // Битовый сдвиг влево
    Integer& operator<<=(int shift);

    // Битовый сдвиг вправо
    Integer& operator>>=(int shift);

    // Унарный +
    Integer& operator+();

    // Унарный -
    Integer operator-();

    // Префиксный ++
    Integer& operator++();

    // Постфиксный ++
    Integer operator++(int);

    // Префиксный --
    Integer& operator--();

    // Постфиксный --
    Integer operator--(int);

    // Побитовое И
    Integer operator&(Integer const& integer);

    // Побитовое ИЛИ
    Integer operator|(Integer const& integer);

    // Побитовая инверсия
    Integer operator~();

    // Побитовое исключающее ИЛИ
    Integer operator^(Integer const& integer);

    // Битовый сдвиг влево
    Integer operator<<(int shift);

    // Битовый сдвиг вправо
    Integer operator >> (int shift);

    // Приведение к bool
    explicit operator bool();

    // Приведение к int
    explicit operator int();

    // Приведение к float
    explicit operator float();

    // Прибавление
    friend Integer operator+(Integer const& left, Integer const& right);

    // Вычитание
    friend Integer operator-(Integer const& left, Integer const& right);

    // Умножение
    friend Integer operator*(Integer const& left, Integer const& right);

    // Деление
    friend Integer operator/(Integer const& left, Integer const& right);

    // Остаток от деления
    friend Integer operator%(Integer const& left, Integer const& right);

    // Оператор ==
    friend bool operator==(Integer const& left, Integer const& right);

    // Оператор <
    friend bool operator<(Integer const& left, Integer const& right);

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& stream, Integer const& integer);

    // Оператор ввода
    friend std::istream& operator >> (std::istream& stream, Integer& integer);
};

Integer operator+(Integer const& left, Integer const& right);

Integer operator-(Integer const& left, Integer const& right);

Integer operator*(Integer const& left, Integer const& right);

Integer operator/(Integer const& left, Integer const& right);

Integer operator%(Integer const& left, Integer const& right);

bool operator==(Integer const& left, Integer const& right);

bool operator!=(Integer const& left, Integer const& right);

bool operator<(Integer const& left, Integer const& right);

bool operator>(Integer const& left, Integer const& right);

bool operator<=(Integer const& left, Integer const& right);

bool operator>=(Integer const& left, Integer const& right);

std::ostream& operator<<(std::ostream& stream, Integer const& integer);

std::istream& operator >> (std::istream& stream, Integer& integer);