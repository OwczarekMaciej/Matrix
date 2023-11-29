#ifndef __ILLEGALMATRIXDIEMENSIONS_H__
#define __ILLEGALMATRIXDIEMENSIONS_H__

class IllegalMatrixDiemensions : public std::exception
{
public:
    IllegalMatrixDiemensions() noexcept = default;
    ~IllegalMatrixDiemensions() = default;
    virtual const char *what() const noexcept
    {
        return "Dimensions of matrices are different";
    }
};

#endif // __ILLEGALMATRIXDIEMENSIONS_H__