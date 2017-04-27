#pragma once

#pragma warning(disable:4996)

#include <exception>
#include <string>
#include <vector>
#include <cmath>

class UnknownCharException
    : public std::exception
{};

class DifferentSizeException
    : public std::exception
{};

class IncorrectNumberException
    : public std::exception
{};

class IncorrectLengthException
    : public std::exception
{};

class LogicErrorException
    : public std::exception
{};

class BooleanFunction
{
public:
    using value_type = bool;
    using size_type = size_t;
    using reference = std::vector<value_type>::reference;
    using const_reference = const std::vector<value_type>::const_reference;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    // возвращает функцию которая равна xn с размерностью dimension
    // пример 1
    // n = 0
    // dimension = 3
    // вернется функция "01010101"
    // пример 2
    // n = 1
    // dimension = 4
    // вернется функция "0011001100110011"
    static BooleanFunction var(size_type n, size_type dimension);

    // тождественный ноль "от dimension переменных"
    static BooleanFunction zero(size_type dimension);

    // тождественная единица "от dimension переменных"
    static BooleanFunction one(size_type dimension);

    static BooleanFunction from_anf(std::vector<value_type> v);

    BooleanFunction();

    // задает фунцию тождественного нуля от n переменных
    BooleanFunction(size_type n);

    // задает фунцию от n переменных. значение равно value
    // пример
    // пусть value = 14, т.е. 0...00001110 в двоичной системе
    // а n = 3
    // тогда АНФ BooleanFunction будет равна x + y + xy + zx + zy + zyx
    BooleanFunction(unsigned long long value, size_type n);

    // пусть table = "01110000"
    // тогда АНФ BooleanFunction будет равна x + y + xy + zx + zy + zyx
    BooleanFunction(const std::string& table);

    // пусть table = {true, false, false, true};
    // тогда АНФ BooleanFunction будет равна x + y + 1
    BooleanFunction(const std::vector<value_type>& table);
    BooleanFunction(const std::initializer_list<bool> vars);

    BooleanFunction(const BooleanFunction& table);

    BooleanFunction& operator=(const BooleanFunction& rhs);

    // сложение по модулю 2
    // если разное количество переменных - исключение
    BooleanFunction& operator+=(const BooleanFunction& rhs);

    // конъюнкция
    // если разное количество переменных - исключение
    BooleanFunction& operator*=(const BooleanFunction& rhs);

    // дизъюнкция
    // если разное количество переменных - исключение
    BooleanFunction& operator|=(const BooleanFunction& rhs);

    // побитовое отрицание
    BooleanFunction operator~();

    // true если функции равны
    //  иначе false
    bool operator==(const BooleanFunction& rhs) const;

    // true если одна функция сравнима и больше или равна rhs
    // false если сравнима и меньше rhs
    // logic_error если фунции не сравнимы
    bool operator>=(const BooleanFunction& rhs) const;

    reference operator[](size_type ind);
    const_reference operator[](size_type ind) const;

    reference at(size_type ind);
    const_reference at(size_type ind) const;

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    // длина столбца функции
    size_type size() const throw();

    // количество переменных
    size_type dimension() const throw();

    // возвращает значение функции
    // пусть BooleanFunction задает функцию f(x, y, z)
    // тогда функция вернет f(vars[0], vars[1], vars[2])
    bool operator()(const std::vector<bool>& vars) const;
    bool operator()(const std::initializer_list<bool> vars) const;


    // T(x1, x2, ..., xN) - текущая функция
    // operator вернет новую функцию, которая равна композиции G = T(fs[0], fs[1], ..., fs[N-1])
    BooleanFunction operator()(const std::vector<BooleanFunction>& fs) const;
    BooleanFunction operator()(const std::initializer_list<BooleanFunction> fs) const;

    bool is_monotone() const;
    bool is_symmetric() const;
    bool is_self_dual() const;
    bool is_linear() const;
    bool is_T1() const;
    bool is_T0() const;
    bool is_balanced() const; //равновесная ли
    size_type weight() const;

    bool is_functionally_complete_system() const;

    // Возвращает АНФ функции
    std::vector<value_type> anf() const;

private:
    std::vector<value_type> func_;

    static std::vector<value_type> ReduceFunc_(std::vector<value_type> const& func);
};

// пусть BooleanFunction представляет из себя функцию "01110000"
// тогда get_polynom вернет строку "x0 + x1 + x0x1 + x0x2 + x1x2 + x0x1x2"
std::string get_polynom(const BooleanFunction& rhs);

BooleanFunction operator+(const BooleanFunction& a, const BooleanFunction& b);

BooleanFunction operator*(const BooleanFunction& a, const BooleanFunction& b);

BooleanFunction operator|(const BooleanFunction& a, const BooleanFunction& b);

bool operator!=(const BooleanFunction& a, const BooleanFunction& b);