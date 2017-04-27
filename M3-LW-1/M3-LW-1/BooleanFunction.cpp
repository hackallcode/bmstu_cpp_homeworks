#include "BooleanFunction.h"

BooleanFunction BooleanFunction::var(size_type n, size_type dimension)
{
    if (n >= dimension) {
        throw IncorrectNumberException();
    }

    BooleanFunction result(0, dimension);

    bool sign = true;
    for (size_type i = 0; i < result.size(); ++i) {
        if (i % size_type(pow(2, n)) == 0) {
            sign = !sign;
        }
        result[i] = sign;
    }

    return result;
}

BooleanFunction BooleanFunction::zero(size_type dimension)
{
    return BooleanFunction(0, dimension);
}

BooleanFunction BooleanFunction::one(size_type dimension)
{
    return BooleanFunction(-1, dimension);
}

BooleanFunction BooleanFunction::from_anf(std::vector<value_type> anf)
{
    size_type s = anf.size();

    double dimension = log2(s);
    if (dimension != size_type(dimension)) {
        throw IncorrectLengthException();
    }

    std::vector<value_type> res(s);

    for (size_type i = 0; i < s; ++i) {
        size_type j = s - 1 - i; // Номер с конца
        res[j] = anf[j];
        for (size_type k = j + 1; k < s; ++k) {
            res[k] = res[k - 1] ^ res[k];
        }
    }

    return BooleanFunction(res);
}

BooleanFunction::BooleanFunction()
{}

BooleanFunction::BooleanFunction(size_type n)
    : func_(pow(2, n))
{}

BooleanFunction::BooleanFunction(unsigned long long value, size_type n)
    : func_(pow(2, n), 0)
{
    for (size_type i = 0; i < func_.size() && value != 0; ++i) {
        func_[i] = value % 2;
        value /= 2;
    }
}

BooleanFunction::BooleanFunction(const std::string& table)
{
    double dimension = log2(table.size());
    if (dimension != size_type(dimension)) {
        throw IncorrectLengthException();
    }

    func_ = std::vector<value_type>(table.size());
    for (size_type i = 0; i < table.size(); ++i) {
        func_[i] = table[i] == '1' ? 1 : (table[i] == '0' ? 0 : throw UnknownCharException());
    }
}

BooleanFunction::BooleanFunction(const std::vector<value_type>& table)
{
    double dimension = log2(table.size());
    if (dimension != size_type(dimension)) {
        throw IncorrectLengthException();
    }

    func_ = std::vector<value_type>(table);
}

BooleanFunction::BooleanFunction(const std::initializer_list<bool> vars)
{
    double dimension = log2(vars.size());
    if (dimension != size_type(dimension)) {
        throw IncorrectLengthException();
    }

    func_ = std::vector<value_type>(vars);
}

BooleanFunction::BooleanFunction(const BooleanFunction& table)
    : func_(table.func_)
{}

BooleanFunction& BooleanFunction::operator=(const BooleanFunction& rhs)
{
    func_ = rhs.func_;
    return *this;
}

BooleanFunction& BooleanFunction::operator+=(const BooleanFunction& rhs)
{
    if (func_.size() != rhs.func_.size()) {
        throw DifferentSizeException();
    }
    for (size_type i = 0; i < func_.size(); ++i) {
        func_[i] = func_[i] ^ rhs.func_[i];
    }
    return *this;
}

BooleanFunction& BooleanFunction::operator*=(const BooleanFunction& rhs)
{
    if (func_.size() != rhs.func_.size()) {
        throw DifferentSizeException();
    }
    for (size_type i = 0; i < func_.size(); ++i) {
        func_[i] = func_[i] & rhs.func_[i];
    }
    return *this;
}

BooleanFunction& BooleanFunction::operator|=(const BooleanFunction& rhs)
{
    if (func_.size() != rhs.func_.size()) {
        throw DifferentSizeException();
    }
    for (size_type i = 0; i < func_.size(); ++i) {
        func_[i] = func_[i] | rhs.func_[i];
    }
    return *this;
}

BooleanFunction BooleanFunction::operator~()
{
    for (size_type i = 0; i < func_.size(); ++i) {
        func_[i] = !func_[i];
    }
    return *this;
}

bool BooleanFunction::operator==(const BooleanFunction& rhs) const
{
    std::vector<value_type> anf_1 = anf();
    std::vector<value_type> anf_2 = rhs.anf();
    size_type s = anf_1.size() <= anf_2.size() ? anf_1.size() : anf_2.size();

    for (size_type i = 0; i < s; i++) {
        if (anf_1[i] != anf_2[i]) {
            return false;
        }
    }
    return true;
}

bool BooleanFunction::operator>=(const BooleanFunction& rhs) const
{
    if (func_.size() != rhs.func_.size()) {
        throw DifferentSizeException();
    }
    if (func_.size() == 0) {
        return true;
    }

    bool result = func_[0] >= rhs.func_[0];
    for (size_type i = 1; i < func_.size(); ++i) {
        if ((func_[i] > rhs.func_[i]) && !result || (func_[i] < rhs.func_[i]) && result) {
            throw LogicErrorException();
        }
    }
    return result;
}

BooleanFunction::reference BooleanFunction::operator[](size_type ind)
{
    return func_[ind];
}

BooleanFunction::const_reference BooleanFunction::operator[](size_type ind) const
{
    return func_[ind];
}

BooleanFunction::reference BooleanFunction::at(size_type ind)
{
    return func_.at(ind);
}

BooleanFunction::const_reference BooleanFunction::at(size_type ind) const
{
    return func_.at(ind);
}

BooleanFunction::iterator BooleanFunction::begin()
{
    return func_.begin();
}

BooleanFunction::iterator BooleanFunction::end()
{
    return func_.end();
}

BooleanFunction::const_iterator BooleanFunction::cbegin() const
{
    return func_.cbegin();
}

BooleanFunction::const_iterator BooleanFunction::cend() const
{
    return func_.cend();
}

BooleanFunction::size_type BooleanFunction::size() const throw()
{
    return func_.size();
}

BooleanFunction::size_type BooleanFunction::dimension() const throw()
{
    return log2(func_.size());
}

bool BooleanFunction::operator()(const std::vector<bool>& vars) const
{
    if (vars.size() != dimension()) {
        throw IncorrectLengthException();
    }

    size_type index = 0;

    size_type i = 0;
    for (bool var : vars) {
        index += pow(2, i) * var;
        ++i;
    }
    return func_[index];
}

bool BooleanFunction::operator()(const std::initializer_list<bool> vars) const
{
    if (vars.size() != dimension()) {
        throw IncorrectLengthException();
    }

    size_type index = 0;

    size_type i = 0;
    for (bool var : vars) {
        index += pow(2, i) * var;
        ++i;
    }

    return func_[index];
}

/*/ ВАРИАНТ 1. Функциия от функций с фиктивными переменными на выходе
BooleanFunction BooleanFunction::operator()(const std::vector<BooleanFunction>& fs) const
{
    if (fs.size() != dimension()) {
        throw IncorrectLengthException();
    }
    if (fs.size() == 0) {
        return BooleanFunction();
    }

    size_type d = 0;
    for (BooleanFunction const& f : fs) {
        d += f.dimension();
    }

    BooleanFunction result(d);

    for (size_type i = 0; i < result.func_.size(); ++i) {
        bool value = true;
        size_type index = 0;
        for (BooleanFunction const& f : fs) {
            std::vector<bool> vars;
            for (size_type j = 0; j < f.dimension(); ++j) {
                vars.push_back(i & static_cast<size_t>(pow(2, index)));
                ++index;
            }
            value &= f(vars);
        }
        result.func_[i] = value;
    }

    return result;
}
/**/

// ВАРИАНТ 2. Функция от векторов значений
BooleanFunction BooleanFunction::operator()(const std::vector<BooleanFunction>& fs) const
{
    if (fs.size() != dimension()) {
        throw IncorrectLengthException();
    }
    if (fs.size() == 0) {
        return BooleanFunction();
    }

    size_type d = 0;
    for (BooleanFunction const& f : fs) {
        if (f.dimension() > d) {
            d = f.dimension();
        }
    }

    BooleanFunction result(d);

    for (size_type i = 0; i < result.func_.size(); ++i) {
        std::vector<bool> vars;
        for (BooleanFunction const& f : fs) {
            vars.push_back(f.func_[i % f.size()]);
        }
        result.func_[i] = (*this)(vars);
    }

    result.func_ = ReduceFunc_(result.func_);

    return result;
}
/**/

BooleanFunction BooleanFunction::operator()(const std::initializer_list<BooleanFunction> fs) const
{
    if (fs.size() != dimension()) {
        throw IncorrectLengthException();
    }
    if (fs.size() == 0) {
        return BooleanFunction();
    }

    size_type d = 0;
    for (BooleanFunction const& f : fs) {
        if (f.dimension() > d) {
            d = f.dimension();
        }
    }

    BooleanFunction result(d);

    for (size_type i = 0; i < result.func_.size(); ++i) {
        std::vector<bool> vars;
        for (BooleanFunction const& f : fs) {
            vars.push_back(f.func_[i % f.size()]);
        }
        result.func_[i] = (*this)(vars);
    }

    result.func_ = ReduceFunc_(result.func_);

    return result;
}

bool BooleanFunction::is_monotone() const
{
    for (size_type i = 0; i < func_.size(); ++i) { // для всех наборов
        for (size_type j = 0; j < dimension(); ++j) { // для всех битов в наборе
            if ((i & size_type(pow(2, j))) == 0) { // j-ный бит == 0
                if (func_[i + size_type(pow(2, j))] < func_[i]) { // Если больше следущего набора по одной из переменных
                    return false;
                }
            }
        }
    }
    return true;
}

bool BooleanFunction::is_symmetric() const
{
    size_type d = dimension();
    std::vector<bool> isFirst(d, true);
    std::vector<value_type> values(d);

    for (size_type i = 1; i < func_.size() - 1; ++i) { // для всех наборов
        size_type s = 0;
        for (size_type j = 0; j < d; ++j) { // для всех битов в наборе
            if ((i & size_type(pow(2, j))) != 0) { // j-ный бит == 1
                ++s;
            }
        }
        if (isFirst[s]) {
            isFirst[s] = false;
            values[s] = func_[i];
        }
        else if (values[s] != func_[i]) {
            return false;
        }
    }
    return true;
}

bool BooleanFunction::is_self_dual() const
{
    size_type s = func_.size();
    std::vector<value_type> selfDualFunc(s);
    for (size_type i = 0; i < s; ++i) {
        selfDualFunc[i] = !func_[s - 1 - i];
    }
    return func_ == selfDualFunc;
}

bool BooleanFunction::is_linear() const
{
    std::vector<value_type> anf_ = anf();
    for (size_type i = dimension() + 1; i < anf_.size(); ++i) {
        if (anf_[i]) {
            return false;
        }
    }
    return true;
}

bool BooleanFunction::is_T1() const
{
    return func_.back();
}

bool BooleanFunction::is_T0() const
{
    return !func_.front();
}

bool BooleanFunction::is_balanced() const
{
    return weight() == (size() / 2);
}

BooleanFunction::size_type BooleanFunction::weight() const
{
    size_type result = 0;
    for (bool b : func_) {
        result += b;
    }
    return result;
}

bool BooleanFunction::is_functionally_complete_system() const
{
    return !is_T0() && !is_T1() && !is_linear() && !is_self_dual() && !is_monotone();
}

std::vector<BooleanFunction::value_type> BooleanFunction::anf() const
{
    std::vector<value_type> result(func_.size());

    std::vector<value_type> func_copy(func_);
    for (size_type i = 0; i < func_.size(); ++i) {
        result[i] = func_copy[0];
        for (size_type j = 0; j < func_copy.size() - 1; ++j) {
            func_copy[j] = func_copy[j] ^ func_copy[j + 1];
        }
        func_copy.resize(func_copy.size() - 1);
    }

    return result;
}

std::vector<BooleanFunction::value_type> BooleanFunction::ReduceFunc_(std::vector<value_type> const& func)
{
    size_type dim = static_cast<size_type>(log2(func.size()));

    std::vector<bool> isEssential(dim, false);

    for (size_type j = 0; j < dim; ++j) {
        size_type s = static_cast<size_type>(pow(2, j)); // Размер половины участка
        size_type c = static_cast<size_type>(func.size() / (s * 2)); // Количество пар

        for (size_type k = 0; k < c; ++k) {
            if (isEssential[j]) {
                break;
            }
            for (size_type i = 2 * s * k; i < 2 * s * k + s; ++i) {
                if (func[i] != func[i + s]) {
                    isEssential[j] = true;
                    break;
                }
            }
        }
    }

    size_type newDim = 0;
    for (bool b : isEssential) {
        if (b) {
            ++newDim;
        }
    }

    if (dim != newDim) {
        std::vector<bool> isResValue(func.size(), true);

        for (size_type j = 0; j < dim; ++j) {
            if (!isEssential[j]) {
                size_type s = static_cast<size_type>(pow(2, j)); // Размер половины участка
                size_type c = static_cast<size_type>(func.size() / (s * 2)); // Количество пар

                for (size_type k = 0; k < c; ++k) {
                    for (size_type i = 2 * s * k + s; i < 2 * s * k + 2 * s; ++i) {
                        isResValue[i] = false;
                    }
                }
            }
        }

        std::vector<value_type> result;

        for (size_type i = 0; i < func.size(); ++i) {
            if (isResValue[i]) {
                result.push_back(func[i]);
            }
        }

        return result;
    }
    else {
        return func;
    }

}

std::string get_polynom(const BooleanFunction& rhs)
{
    std::string result;
    std::vector<BooleanFunction::value_type> anf = rhs.anf();
    if (anf[0]) {
        result = "1 + ";
    }
    for (BooleanFunction::size_type i = 1; i < anf.size(); ++i) {
        if (anf[i]) {
            for (BooleanFunction::size_type j = 0; j < rhs.dimension(); ++j) {
                if ((i & BooleanFunction::size_type(pow(2, j))) != 0) { // j-ный бит == 1
                    result += "x";
                    char num[16];
                    itoa(j, num, 10);
                    result += num;
                }
            }
            result += " + ";
        }
    }
    if (result.empty()) {
        result = "0";
    }
    else {
        result.resize(result.size() - 3); // Обрезать " + "
    }
    return result;
}

BooleanFunction operator+(const BooleanFunction& a, const BooleanFunction& b)
{
    BooleanFunction result(a);
    result += b;
    return result;
}

BooleanFunction operator*(const BooleanFunction& a, const BooleanFunction& b)
{
    BooleanFunction result(a);
    result *= b;
    return result;
}

BooleanFunction operator|(const BooleanFunction& a, const BooleanFunction& b)
{
    BooleanFunction result(a);
    result |= b;
    return result;
}

bool operator!=(const BooleanFunction& a, const BooleanFunction& b)
{
    return !(a == b);
}
