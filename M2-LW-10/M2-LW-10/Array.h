#pragma once

#include <exception>
#include <initializer_list>

class OutOfRangeException
    : public std::exception
{
public:
    OutOfRangeException()
        : std::exception()
    {}

    OutOfRangeException(char const* const message)
        : std::exception(message)
    {}
};

template <
    class T,
    std::size_t N
>
class Array {
public:
    // Types
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = value_type& const;
    using pointer = T*;
    using const_pointer = T* const;
    using iterator = value_type*;
    using const_iterator = value_type* const;

private:
    // Data
    value_type data_[N];

public:
    // Constructor
    Array()
    {}

    // User constructor
    Array(T data[N])
    {
        memcpy(data_, data, N * sizeof(value_type));
    }

    // User constructor
    Array(std::initializer_list<T> list)
    {
        std::copy(list.begin(), list.end(), data_);
    }

    // Access to items
    reference at(size_type index) 
    {
        if (index >= N) {
            throw OutOfRangeException("out of range");
        }
        return data_[index];
    }

    const_reference at(size_type index) const
    {
        if (index >= N) {
            throw OutOfRangeException("out of range");
        }
        return data_[index];
    }

    reference operator[](size_type index)
    {
        return data_[index];
    }

    const_reference operator[](size_type index) const
    {
        return data_[index];
    }

    reference front()
    {
        return data_[0];
    }

    const_reference front() const
    {
        return data_[0];
    }

    reference back()
    {
        return data_[N - 1];
    }

    const_reference back() const
    {
        return data_[N - 1];
    }

    T* data()
    {
        return data_;
    }

    const T* data() const
    {
        return data_;
    }

    // Iterators
    iterator begin()
    {
        return &data_[0];
    }

    const_iterator begin() const
    {
        return &data_[0];
    }

    const_iterator cbegin() const
    {
        return &data_[0];
    }

    iterator end()
    {
        return &data_[N - 1];
    }

    const_iterator end() const
    {
        return &data_[N - 1];
    }

    const_iterator cend() const
    {
        return &data_[N - 1];
    }

    // Size
    bool empty() const
    {
        return N == 0;
    }

    size_type size() const
    {
        return N;
    }

    size_type max_size() const
    {
        return N;
    }

    // Operations
    void fill(T& const value)
    {
        for (size_type i = 0; i < N; i++) {
            data_[i] = value;
        }
    }

    void swap(Array& other)
    {
        std::swap(data_, other.data_);
    }

    // Friend functions
    template<class T, std::size_t N>
    friend bool operator==(Array<T, N>& lhs, Array<T, N>& rhs);

    template<class T, std::size_t N>
    friend bool operator<(Array<T, N>& lhs, Array<T, N>& rhs);

    template<class T, std::size_t N>
    friend bool operator<=(Array<T, N>& lhs, Array<T, N>& rhs);
};

template<class T, std::size_t N>
bool operator==(Array<T, N>& lhs, Array<T, N>& rhs)
{
    for (size_t i = 0; i < N; i++) {
        if (lhs.data_[i] != rhs.data_[i]) {
            return false;
        }
    }
    return true;
}

template<class T, std::size_t N>
inline bool operator!=(Array<T, N>& lhs, Array<T, N>& rhs)
{
    return !(lhs == rhs)
}

template<class T, std::size_t N>
bool operator<(Array<T, N>& lhs, Array<T, N>& rhs)
{
    for (size_t i = 0; i < N; i++) {
        if (lhs.data_[i] >= rhs.data_[i]) {
            return false;
        }
    }
    return true;
}

template<class T, std::size_t N>
bool operator<=(Array<T, N>& lhs, Array<T, N>& rhs)
{
    for (size_t i = 0; i < N; i++) {
        if (lhs.data_[i] > rhs.data_[i]) {
            return false;
        }
    }
    return true;
}

template<class T, std::size_t N>
inline bool operator>(Array<T, N>& lhs, Array<T, N>& rhs)
{
    return rhs < lhs;
}

template<class T, std::size_t N>
inline bool operator>=(Array<T, N>& lhs, Array<T, N>& rhs)
{
    return rhs <= lhs;
}

template<class T, std::size_t N>
inline T* get(Array<T, N> const & a) throw()
{
    return a.data();
}

template<class T, std::size_t N>
inline void swap(Array<T, N> & lhs, Array<T, N> & rhs) throw()
{
    lhs.swap(rhs);
}