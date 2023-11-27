#ifndef __MEMORYALLOCFAILED_H__
#define __MEMORYALLOCFAILED_H__

class MemoryAllocFailed : public std::exception
{
public:
    MemoryAllocFailed() noexcept = default;
    ~MemoryAllocFailed() = default;
    virtual const char *what() const noexcept
    {
        return "Memory allocation failed";
    }
};

#endif