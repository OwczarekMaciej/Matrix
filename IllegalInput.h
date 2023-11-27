#ifndef __ILLEGALINPUT_H__
#define __ILLEGALINPUT_H__

class IllegalInput : public std::exception
{
public:
    IllegalInput() noexcept = default;
    ~IllegalInput() = default;
    virtual const char *what() const noexcept
    {
        return "Illegal type of input";
    }
};

#endif