#include "Multiset.h"
#include <stdexcept>
#include "MyString/MyString.h"
#include "Utils.h"

Multiset::Multiset(size_t n, uint8_t k) : _n(n), _k(k)
{
    _data = new unsigned char[getCapacity()]{'\0'};
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

// void Multiset::add(size_t num)
// {
//     if (num > _n)
//         throw std::range_error(*MyString()
//                                     .append("Number ")
//                                     .append(intToChar(num))
//                                     .append(" out of range [0, ")
//                                     .append(intToChar(_n))
//                                     .append("]."));

//     // // if begin == end

//     size_t byteIdxBegin = getBucketIdxBegin(num);
//     size_t bitIdxBegin = getMostSignificantBitIdx(num);

//     // Calculate the value and mask based on _k and bitIdxBegin
//     unsigned char value = (_data[byteIdxBegin] >> (8 - _k - bitIdxBegin)) & ((1 << _k) - 1);
//     unsigned char mask = ((1 << _k) - 1) << (8 - _k - bitIdxBegin);

//     // Increment the value and handle overflow
//     value = (value + 1) % (1 << _k);

//     // Update the _data array
//     _data[byteIdxBegin] = (_data[byteIdxBegin] & ~mask) | (value << (8 - _k - bitIdxBegin));

//     // If _k bits span two bytes, update the second byte
//     if (8 - bitIdxBegin < _k)
//     {
//         size_t bitIdxEnd = _k - (8 - bitIdxBegin);
//         unsigned char value2 = (_data[byteIdxBegin + 1] >> (8 - bitIdxEnd)) & ((1 << bitIdxEnd) - 1);
//         unsigned char mask2 = ((1 << bitIdxEnd) - 1) << (8 - bitIdxEnd);

//         // Handle carry from the first byte
//         if (value == 0)
//         {
//             value2 = (value2 + 1) % (1 << bitIdxEnd);
//         }

//         // Update the second byte
//         _data[byteIdxBegin + 1] = (_data[byteIdxBegin + 1] & ~mask2) | (value2 << (8 - bitIdxEnd));
//     }
// }

void Multiset::add(size_t num)
{
    if (num > _n)
        throw std::range_error(*MyString()
                                    .append("Number ")
                                    .append(intToChar(num))
                                    .append(" out of range [0, ")
                                    .append(intToChar(_n))
                                    .append("]."));

    size_t byteIdxBegin = getBucketIdxBegin(num);
    size_t bitIdxBegin = getMostSignificantBitIdx(num);

    unsigned char value = (_data[byteIdxBegin] >> (8 - _k - bitIdxBegin)) & ((1 << _k) - 1);
    unsigned char mask = ((1 << _k) - 1) << (8 - _k - bitIdxBegin);

    value = (value + 1) % (1 << _k);

    _data[byteIdxBegin] = (_data[byteIdxBegin] & ~mask) | (value << (8 - _k - bitIdxBegin));
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
    return size_t((((_n + 1) * _k) / 8) + 1);
}

inline size_t Multiset::getBucketIdxBegin(size_t num) const
{
    return size_t((num * _k) / 8);
}

inline size_t Multiset::getBucketIdxEnd(size_t num) const
{
    return size_t(((num * _k) + (_k - 1)) / 8);
}

inline size_t Multiset::getMostSignificantBitIdx(size_t num) const
{
    return size_t((num * _k) % 8);
}

inline size_t Multiset::getBucketIdxFromBits(size_t bits) const
{
    return size_t(bits / 8);
}

inline size_t Multiset::getBitIdxInBucketFromBits(size_t bits) const
{
    return size_t();
}
