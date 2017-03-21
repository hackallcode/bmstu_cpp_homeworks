#ifndef __SCOPED_PTR__
#define __SCOPED_PTR__

template<class T>
class ScopedPtr
{
private:
    T * ptr_;
public:
	ScopedPtr(ScopedPtr const &) = delete;
	ScopedPtr& operator=(ScopedPtr const &) = delete;
	
	explicit ScopedPtr(T* ptr = nullptr)
        : ptr_(ptr)
    {}

    ~ScopedPtr() {
        delete ptr_;
    };

    void reset(T* ptr = nullptr)
    {
        if (ptr != ptr_)
            delete ptr_;
        ptr_ = ptr;
    }

    T& operator*() const
    {
        return *get();
    }

    T* operator->() const
    {
        return get();
    }

    T* get() const throw()
    {
        return ptr_;
    }

    void swap(ScopedPtr & b) throw()
    {
        std::swap(ptr_, b.ptr_);
    }

    bool operator! () const throw()
    {
        return ptr_ == nullptr;
    }

    explicit operator bool() const throw()
    {
        return ptr_ != nullptr;
    }
};

template<class T> 
inline bool operator==(ScopedPtr<T> const & p, std::nullptr_t) throw()
{
    return !p;
}

template<class T> 
inline bool operator==(std::nullptr_t, ScopedPtr<T> const & p) throw()
{
    return !p;
}

template<class T>
inline bool operator!=(ScopedPtr<T> const & p, std::nullptr_t) throw() 
{
    return p;
}

template<class T> 
inline bool operator!=(std::nullptr_t, ScopedPtr<T> const & p) throw()
{
    return p;
}

template<class T> 
inline void swap(ScopedPtr<T> & a, ScopedPtr<T> & b) throw()
{
    a.swap(b);
}

// get_pointer(p) is a generic way to say p.get()
template<class T> 
inline T* get_pointer(ScopedPtr<T> const & p) throw()
{
    return p.get();
}

#endif // __SCOPED_PTR__