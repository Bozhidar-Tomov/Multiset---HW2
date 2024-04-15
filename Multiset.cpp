#include "Multiset.h"
#include <stdexcept>
#include "MyString/MyString.h"
#include "Utils.h"

Multiset::Multiset(size_t n, uint8_t k) : _n(n), _k(k)
{
    _data = new unsigned char[getCapacity()];
}

Multiset::Multiset(const Multiset &other)
{
    copyFrom(other);
}

Multiset &Multiset::operator=(const Multiset &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Multiset::~Multiset()
{
    free();
}

void Multiset::add(size_t n)
{
    if (n >= _n)
        throw std::range_error(*MyString()
                                    .append("Number ")
                                    .append(intToChar(n))
                                    .append(" out of range [0, ")
                                    .append(intToChar(_n))
                                    .append("]."));
}

void Multiset::free()
{
    delete[] _data;
    _data = nullptr;
    _n = _k = 0;
}

void Multiset::copyFrom(const Multiset &other)
{
    _n = other._n;
    _k = other._k;

    _data = new unsigned char[getCapacity()];

    for (size_t i = 0; i < getCapacity(); ++i)
        _data[i] = other._data[i];
}

inline size_t Multiset::getCapacity() const
{
    return size_t((_n * _k) / 8);
}

inline size_t Multiset::getBucketIdxBegin(size_t num) const
{
    return size_t(num * _k / 8);
}

inline size_t Multiset::getBucketIdxEnd(size_t num) const
{
    return size_t(((num * _k) + (_k - 1)) / 8);
}
