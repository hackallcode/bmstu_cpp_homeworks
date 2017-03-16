#ifndef __NOTCOPYABLE_INCLUDED__
#define __NOTCOPYABLE_INCLUDED__

#pragma warning(disable:4996)
#include <exception>
#include <cstdio>
#include <string>

struct FileAlreadyOpened
    : public std::exception
{
    FileAlreadyOpened() = default;
    FileAlreadyOpened(const char* const message)
        : std::exception(message)
    { }
};

class NotCopyable
{
    FILE * Descriptor;

public:
    NotCopyable()
        : Descriptor(nullptr)
    { }

    ~NotCopyable() 
    {
        Close();
    }

    NotCopyable(const NotCopyable&) = delete;
    NotCopyable& operator = (const NotCopyable&) = delete;

    void OpenToWrite(std::string const & fileName)
    {
        if (Descriptor != nullptr)
            throw FileAlreadyOpened();
        Descriptor = fopen(fileName.c_str(), "w");
    }

    void OpenToRead(std::string const & fileName)
    {
        if (Descriptor != nullptr)
            throw FileAlreadyOpened();
        Descriptor = fopen(fileName.c_str(), "r");
    }

    void Close() throw()
    {
        if (Descriptor != nullptr)
        {
            fclose(Descriptor);
            Descriptor = nullptr;
        }
    }

    FILE * Get()
    {
        return Descriptor;
    }
};

#endif // __NOTCOPYABLE_INCLUDED__