#ifndef __TVECTOR_INCLUDED__
#define __TVECTOR_INCLUDED__

#include <memory>
#include <exception>

class OutOfRangeException
    : std::exception
{
public:
    OutOfRangeException() throw()
        : std::exception("out of range")
    {}

    OutOfRangeException(char const* const message) throw()
        : std::exception(message)
    {}

    virtual char const* what() const override
    {
        return std::exception::what();
    }
};

class Vector
{
public:
    using value_type = int;
    using size_type = size_t;
    using iterator = value_type *;
    using reference = value_type&;
    using const_reference = const value_type&;

private:
    value_type * ptr_;
    size_type size_;
    size_type internalCapacity_;
public:
    Vector()
        : ptr_(nullptr)
        , size_(0)
        , internalCapacity_(0)
    { }

    Vector(size_type _capacity)
        : size_(0)
        , internalCapacity_(_capacity)
    {
        ptr_ = new value_type[sizeof(value_type) * internalCapacity_];
    }

    ~Vector()
    {
        delete[] ptr_;
    }

    bool empty() const throw()
    {
        return size() == 0;
    }

    size_type size() const throw()
    {
        return size_;
    }

    size_type capacity() const throw()
    {
        return internalCapacity_;
    }

    iterator begin() const throw()
    {
        return ptr_;
    }

    iterator end() const throw()
    {
        return ptr_ + size_;
    }

    void reserve(size_type _count)
    {
        if (_count <= internalCapacity_) {
            return;
        }

        internalCapacity_ = _count;
        value_type * newPtr = new value_type[sizeof(value_type) * internalCapacity_];
        memcpy(newPtr, ptr_, sizeof(value_type) * size_);
        delete[] ptr_;
        ptr_ = newPtr;
    }

    Vector(const Vector& _rhs)
        : internalCapacity_(_rhs.internalCapacity_)
        , size_(_rhs.size_)
    {
        ptr_ = new value_type[sizeof(value_type) * internalCapacity_];
        for (size_t i = 0; i < internalCapacity_; i++) {
            ptr_[i] = _rhs.ptr_[i];
        }
    }

    Vector& operator=(const Vector& _rhs)
    {
        if (internalCapacity_ != _rhs.internalCapacity_) {
            delete[] ptr_;
            internalCapacity_ = _rhs.internalCapacity_;
            ptr_ = new value_type[sizeof(value_type) * internalCapacity_];
        }
        size_ = _rhs.size_;
        memcpy(ptr_, _rhs.ptr_, sizeof(value_type) * internalCapacity_);
        return *this;
    }

    void push_back(const value_type& _value)
    {
        if (size_ == internalCapacity_) {
            internalCapacity_ == 0 ? reserve(1) : reserve(internalCapacity_ * 2);
        }
        ptr_[size_] = _value;
        size_++;
    }

    reference at(size_type _index)
    {
        if (_index < 0 || _index > size_ - 1) {
            throw OutOfRangeException();
        }
        return ptr_[_index];
    }

    value_type at(size_type _index) const
    {
        if (_index < 0 || _index > size_ - 1) {
            throw OutOfRangeException();
        }
        return ptr_[_index];
    }

    reference operator[](size_type _index)
    {
        return ptr_[_index];
    }

    const_reference operator[](size_type _index) const
    {
        return ptr_[_index];
    }

    reference front()
    {
        if (size_ == 0) {
            throw OutOfRangeException();
        }
        return ptr_[0];
    }

    const_reference front() const
    {
        if (size_ == 0) {
            throw OutOfRangeException();
        }
        return ptr_[0];
    }

    reference back()
    {
        if (size_ == 0) {
            throw OutOfRangeException();
        }
        return ptr_[size_ - 1];
    }

    const_reference back() const
    {
        if (size_ == 0) {
            throw OutOfRangeException();
        }
        return ptr_[size_ - 1];
    }

    void clear()
    {
        size_ = 0;
    }

    void pop_back()
    {
        if (size_ > 0) {
            size_--;
        }
    }

    void swap(Vector& _other) throw()
    {
        std::swap(ptr_, _other.ptr_);
        std::swap(size_, _other.size_);
        std::swap(internalCapacity_, _other.internalCapacity_);
    }

    void resize(size_type _size, value_type _value = value_type())
    {
        if (_size == size_) {
            return;
        }
        if (_size > internalCapacity_) {
            reserve(_size);
        }
        for (int i = size_; i < _size; i++) {
            ptr_[i] = _value;
        }
        size_ = _size;
    }

    iterator insert(iterator _pos, const value_type& _value)
    {
        if (_pos < ptr_ || _pos > ptr_ + size_ - 1) {
            throw OutOfRangeException();
        }
        if (size_ == internalCapacity_) {
            value_type * oldPtr = ptr_;
            reserve(internalCapacity_ * 2);
            _pos += ptr_ - oldPtr;
        }
        size_++;
        for (iterator curPtr = ptr_ + size_ - 1; curPtr > _pos; curPtr--) {
            *curPtr = *(curPtr - 1);
        }
        *_pos = _value;
    }

    void insert(iterator _pos, size_type _count, const value_type& _value)
    {
        if (_pos < ptr_ || _pos > ptr_ + size_ - 1) {
            throw OutOfRangeException();
        }
        if (internalCapacity_ + _count > internalCapacity_) {
            value_type * oldPtr = ptr_;
            reserve(internalCapacity_ + _count);
            _pos += ptr_ - oldPtr;
        }
        size_ += _count;
        for (iterator curPtr = ptr_ + size_ - 1; curPtr > _pos + _count - 1; curPtr--) {
            *curPtr = *(curPtr - _count);
        }
        *_pos = _value;
    }

    iterator erase(iterator _pos)
    {
        if (_pos < ptr_ || _pos > ptr_ + size_ - 1) {
            throw OutOfRangeException();
        }
        size_--;
        for (iterator curPtr = _pos; curPtr < ptr_ + size_; curPtr++) {
            *curPtr = *(curPtr + 1);
        }
    }
    
    iterator erase(iterator _first, iterator _last)
    {
        if (_first < ptr_ || _first > ptr_ + size_ - 1 || _last < ptr_ || _last > ptr_ + size_ - 1 || _first > _last) {
            throw OutOfRangeException();
        }
        size_type count = _last - _first + 1;
        size_ -= count;
        for (iterator curPtr = _first; curPtr < ptr_ + size_; curPtr++) {
            *curPtr = *(curPtr + count);
        }
    }
};


#endif // __TVECTOR_INCLUDED__