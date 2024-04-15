#pragma once
#include <stddef.h>
#include <stdint.h>

// TODO: move

class Multiset
{
    unsigned char *_data = nullptr;
    size_t _n = 0;
    uint8_t _k = 0;

public:
    Multiset(size_t, uint8_t);
    Multiset(const Multiset &);
    Multiset &operator=(const Multiset &);
    ~Multiset();

    void add(size_t n);

private:
    void free();
    void copyFrom(const Multiset &);
    inline size_t getCapacity() const;
    inline size_t getBucketIdxBegin(size_t) const;
    inline size_t getBucketIdxEnd(size_t) const;
};