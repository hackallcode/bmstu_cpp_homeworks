#include "Integer.h"

Integer::~Integer() = default;

Integer::Integer()
    : data_(0)
{}

Integer::Integer(int data)
    : data_(data)
{}

Integer::Integer(Integer const& integer)
    : data_(integer.data_)
{}

Integer& Integer::operator=(Integer const& integer)
{
    if (this == &integer) {
        return *this;
    }
    data_ = integer.data_;
    return *this;
}

Integer& Integer::operator+=(Integer const& integer)
{
    if (// Если сумма 2-х положительных больше максимального положительного ИЛИ 
        data_ > 0 && integer.data_ > 0 && (INT_MAX - integer.data_ < data_) ||
        // Если сумма 2-х отрицательных меньше минимального отрицательного
        data_ < 0 && integer.data_ < 0 && (INT_MIN - integer.data_ > data_)) {
        throw IntegerOverflowException();
    }
    data_ += integer.data_;
    return *this;
}

Integer& Integer::operator-=(Integer const& integer)
{
    if (data_ > 0 && integer.data_ < 0 && (INT_MAX + integer.data_ < data_) ||
        data_ < 0 && integer.data_ > 0 && (INT_MIN + integer.data_ > data_)) {
        throw IntegerOverflowException();
    }
    data_ -= integer.data_;
    return *this;
}

Integer& Integer::operator*=(Integer const& integer)
{
    unsigned short a_0 = data_; // Младшие 16 бит первого числа
    unsigned short a_1 = data_ >> 16; // Старшие 16 бит первого числа
    unsigned short b_0 = integer.data_; // Младшие 16 бит второго числа
    unsigned short b_1 = integer.data_ >> 16; // Старшие 16 бит второго числа

    // Умножение чисел выглядит так: 
    // result_1 << 32 + result_2 << 16 + result_3 << 16 + result_4
    unsigned int result_1 = a_1 * b_1;
    unsigned int result_2 = a_1 * b_0;
    unsigned int result_3 = a_0 * b_1;
    unsigned int result_4 = a_0 * b_0;

    // Если выполняется одно из условий, то число точно уйдет за пределы 32 бит
    if (result_1 > 0 || result_2 + result_3 > USHRT_MAX) {
        throw IntegerOverflowException();
    }

    unsigned int result = (result_2 + result_3) << 16;
    // Если добавить int, то можно уйти за 32 бита
    if (UINT_MAX - result_4 < result) {
        throw IntegerOverflowException();
    }
    data_ = result + result_4;

    return *this;
}

Integer& Integer::operator/=(Integer const& integer)
{
    data_ /= integer.data_;
    return *this;
}

Integer& Integer::operator%=(Integer const& integer)
{
    data_ %= integer.data_;
    return *this;
}

Integer& Integer::operator&=(Integer const& integer)
{
    data_ &= integer.data_;
    return *this;
}

Integer& Integer::operator|=(Integer const& integer)
{
    data_ |= integer.data_;
    return *this;
}

Integer& Integer::operator^=(Integer const& integer)
{
    data_ ^= integer.data_;
    return *this;
}

Integer& Integer::operator<<=(int shift)
{
    data_ <<= shift;
    return *this;
}

Integer& Integer::operator>>=(int shift)
{
    data_ >>= shift;
    return *this;
}

Integer& Integer::operator+()
{
    return *this;
}

Integer Integer::operator-()
{
    return Integer(-data_);
}

Integer& Integer::operator++()
{
    data_++;
    return *this;
}

Integer Integer::operator++(int)
{
    Integer oldInteger(*this);
    ++(*this);
    return oldInteger;
}

Integer& Integer::operator--()
{
    data_--;
    return *this;
}

Integer Integer::operator--(int)
{
    Integer oldInteger(*this);
    --(*this);
    return oldInteger;
}

Integer Integer::operator&(Integer const& integer)
{
    Integer result(*this);
    result &= integer;
    return result;
}

Integer Integer::operator|(Integer const& integer)
{
    Integer result(*this);
    result |= integer;
    return result;
}

Integer Integer::operator~()
{
    Integer result(*this);
    result.data_ = ~(result.data_);
    return result;
}

Integer Integer::operator^(Integer const& integer)
{
    Integer result(*this);
    result ^= integer;
    return result;
}

Integer Integer::operator<<(int shift)
{
    Integer result(*this);
    result <<= shift;
    return result;
}

Integer Integer::operator >> (int shift)
{
    Integer result(*this);
    result >>= shift;
    return result;
}

Integer operator+(Integer const& left, Integer const& right)
{
    Integer result(left);
    result += right;
    return result;
}

Integer operator-(Integer const& left, Integer const& right)
{
    Integer result(left);
    result -= right;
    return result;
}

Integer operator*(Integer const& left, Integer const& right)
{
    Integer result(left);
    result *= right;
    return result;
}

Integer operator/(Integer const& left, Integer const& right)
{
    Integer result(left);
    result /= right;
    return result;
}

Integer operator%(Integer const& left, Integer const& right)
{
    Integer result(left);
    result %= right;
    return result;
}

bool operator==(Integer const& left, Integer const& right)
{
    return (left.data_ == right.data_);
}

bool operator!=(Integer const& left, Integer const& right)
{
    return !(left == right);
}

bool operator<(Integer const& left, Integer const& right)
{
    return (left.data_ < right.data_);
}

bool operator>(Integer const& left, Integer const& right)
{
    return (right < left);
}

bool operator<=(Integer const& left, Integer const& right)
{
    return !(left > right);
}

bool operator>=(Integer const& left, Integer const& right)
{
    return !(left < right);
}

std::ostream& operator<<(std::ostream& stream, Integer const& integer)
{
    stream << integer.data_;
    return stream;
}

std::istream& operator >> (std::istream& stream, Integer& integer)
{
    stream >> integer.data_;
    return stream;
}